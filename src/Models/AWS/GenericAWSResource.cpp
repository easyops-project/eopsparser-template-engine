#include <iostream>
#include "./GenericAWSResource.hpp"

namespace EOPSTemplateEngine::AWS {
    GenericAWSResource::GenericAWSResource(std::string type) {
        this->Type = type;
    };

    GenericAWSResource::GenericAWSResource() {};

    Json GenericAWSResource::ToJson() {
        Json returnJson = Json::object();
        returnJson["Type"] = this->Type;
        return returnJson;
    }

    void GenericAWSResource::AddDependency(std::string resourceName) {
        this->DependsOn.push_back(resourceName);
    }

    void GenericAWSResource::setFromParsedResource(
            EOPSNativeLib::Models::Resource *res) {
        // uninstanciated as it's an interface but should be still invokable
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