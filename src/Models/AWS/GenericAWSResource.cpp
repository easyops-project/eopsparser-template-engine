#include <iostream>
#include <utility>
#include "./GenericAWSResource.hpp"
#include <nlohmann/json.hpp>
#include "../../Helpers/Http/OpenMapAPI.hpp"
#include <fstream>
#include "../Generics/AZLocation.hpp"
#include "../../Helpers/helperFunctions.hpp"
#include <algorithm>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::AWS {
    GenericAWSResource::GenericAWSResource(std::string type) {
        this->Type = std::move(type);
    };

    GenericAWSResource::GenericAWSResource() {};

    Json GenericAWSResource::ToJson() {
        Json returnJson = Json::object();
        returnJson["Type"] = this->Type;

        if (!this->DependsOn.empty()) {
            Json dependencies = Json::array();
            for (auto const &str: this->DependsOn) {
                dependencies.push_back(str);
            }
            returnJson["DependsOn"] = dependencies;
        }
        return returnJson;
    }

    void GenericAWSResource::AddDependencies(std::vector<std::string> &resources) {
        for (const auto &res: resources) {
            this->DependsOn.push_back(res);
        }
    }

    GenericAWSResource::~GenericAWSResource() {
        // empty destructor
    }

    std::string GenericAWSResource::getAvailabilityZoneFromString(std::string zone) {
        std::ifstream jsonFile;
        jsonFile.open(AWS_AVAILABILITY_ZONES);

        if(jsonFile.is_open()) {
            std::vector<Generics::AZLocation> azLocations = Json::parse(jsonFile);
            jsonFile.close();

            std::string currentType = this->Type;
            for(auto it = azLocations.begin(); it != azLocations.end(); ++it){
                std::vector<std::string> v = it->availableResources;
                if(std::find(v.begin(), v.end(), currentType) == v.end()) {
                    it = azLocations.erase(it);
                    --it;
                }
            }
         
            auto *oma = new EOPSTemplateEngine::Helpers::HTTP::OpenMapsAPI();
            EOPSTemplateEngine::Helpers::HTTP::GetCoordsFromQueryResponse res = oma->getCoordsFromQuery(zone);
            
            std::vector<std::pair<double, double>> latLongs;
            for (const auto &az: azLocations) {
                std::pair<double, double> pair(az.lat, az.lon);

                latLongs.push_back(pair);
            }

            int index = Helpers::HelperFunctions::getClosestRegionPerCoordinates(res.lat, res.lon, latLongs);
            std::string returnString = azLocations[index].zone;
            return returnString;
        }
    }
} // namespace EOPSTemplateEngine::AWS