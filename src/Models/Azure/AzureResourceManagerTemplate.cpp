#include "AzureResourceManagerTemplate.hpp"
#include "Compute/VirtualMachine.hpp"

namespace EOPSTemplateEngine::Azure {
    AzureResourceManagerTemplate::AzureResourceManagerTemplate() {
        this->$schema = "https://schema.management.azure.com/schemas/2015-01-01/deploymentTemplate.json#";
        this->contentVersion = "1.0.0.0";
    }

    void AzureResourceManagerTemplate::AddResource(EOPSNativeLib::Models::Resource *resource) {
        if (resource->Type == "Virtual_Machine") {
            auto *vm = new Compute::VirtualMachine(resource->Name, resource->Type, resource->Location);
            vm->setFromParsedResource(dynamic_cast<EOPSNativeLib::Models::VirtualMachine *>(resource));
            this->AddResource(vm);
        }
    }

    void AzureResourceManagerTemplate::AddResource(GenericAzureResource *resource) {
        this->resources.push_back(resource);
    }

    Json AzureResourceManagerTemplate::ToJson() {
        Json j = Json::object();
        j["$schema"] = this->$schema;
        j["contentVersion"] = this->contentVersion;

        Json resources = Json::array();
        for (const auto &resource: this->resources) {
            resources.push_back(resource->ToJson());
        }
        j["resources"] = resources;

        return j;
    }
}