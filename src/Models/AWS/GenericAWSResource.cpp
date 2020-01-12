#include <iostream>
#include <utility>
#include "./GenericAWSResource.hpp"
#include <nlohmann/json.hpp>

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
        if (zone == "europe") {
            return "eu-west-1";
        } else if (zone == "america") {
            return "us-east-1";
        } else if (zone == "asia") {
            return "ap-northeast-1";
        } else if (zone == "china") {
            return "cn-north-1";
        } else {
            std::cout << "Zone not found. Assuming europe" << std::endl;
            return "eu-west-1";
        }
    }
} // namespace EOPSTemplateEngine::AWS