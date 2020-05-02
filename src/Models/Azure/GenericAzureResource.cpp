#include "GenericAzureResource.hpp"
#include "../../Helpers/helperFunctions.hpp"
#include "../../Helpers/Http/OpenMapAPI.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Azure {
    Json GenericAzureResource::ToJson() {
        Json j = Json::object();

        j["name"] = this->name;
        j["type"] = this->type;
        j["apiVersion"] = this->apiVersion;
        j["location"] = this->location;

        return j;
    }

    void GenericAzureResource::setLocation(std::string &location) {
        std::string loc = this->getAvailabilityZoneFromString(location, this->type);
        this->location = loc;
    }

    GenericAzureResource::GenericAzureResource(std::string &name, std::string &resourceType) {
        this->name = name;
        this->setType(resourceType);
    }

    std::string GenericAzureResource::getType() {
        return this->type;
    }


    void GenericAzureResource::setType(std::string &resourceType) {
        if (resourceType == "Virtual_Machine") {
            this->type = "Microsoft.Compute/virtualMachines";
            this->apiVersion = "2019-07-01";
        }
    }

    std::vector<Generics::AZLocation> GenericAzureResource::getAZs() {
        std::vector<Generics::AZLocation> azLocations;
        std::ifstream jsonFile;
        jsonFile.open(AZURE_AVAILABILITY_ZONES);

        if(jsonFile.is_open()) {
            std::vector<Generics::AZLocation> azLocations = Json::parse(jsonFile);
            jsonFile.close();

            for(auto it = azLocations.begin(); it != azLocations.end(); ++it){
                std::vector<std::string> v = it->availableResources;
                if(std::find(v.begin(), v.end(), this->getType()) == v.end()) {
                    it = azLocations.erase(it);
                    --it;
                }
            }
        }
        return azLocations;
    }

    std::string GenericAzureResource::getLocation() {
        return this->location;
    }

    std::string GenericAzureResource::getAvailabilityZoneFromString(std::string zone, std::string currentType) {
        std::vector<Generics::AZLocation> azLocations = this->getAZs();
        if(azLocations.empty()) {
            std::cout << "No locations found for your required position... Setting your setup to defaults" << std::endl;
            return "DEFAULT_OVERRIDE";
        } else {
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
}