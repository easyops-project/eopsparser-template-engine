#include "GenericAzureResource.hpp"

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

    }

    GenericAzureResource::GenericAzureResource(std::string &name, std::string &resourceType, std::string &location) {
        this->name = name;
        this->setType(resourceType);
        this->setLocation(location);
    }

    void GenericAzureResource::setType(std::string &resourceType) {
        if (resourceType == "Virtual_Machine") {
            this->type = "Microsoft.Compute/virtualMachines";
            this->apiVersion = "2019-07-01";
        }
    }
}