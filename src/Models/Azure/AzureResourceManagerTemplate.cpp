#include "AzureResourceManagerTemplate.hpp"
#include "Compute/VirtualMachine.hpp"

namespace EOPSTemplateEngine::Azure {
    AzureResourceManagerTemplate::AzureResourceManagerTemplate() {
        this->$schema = "https://schema.management.azure.com/schemas/2015-01-01/deploymentTemplate.json#";
        this->contentVersion = "1.0.0.0";
    }

    void AzureResourceManagerTemplate::AddResource(EOPSNativeLib::Models::Resource *resource) {
        if (resource->Type == "Virtual_Machine") {
            auto *vm = new Compute::VirtualMachine(resource->Name, resource->Type);
            vm->setFromParsedResource(dynamic_cast<EOPSNativeLib::Models::VirtualMachine *>(resource));
            this->AddResource(vm);

            GenericAzureOutput *output = new GenericAzureOutput();
            output->value = "[reference('" + resource->Name + "').ipAddress]";

            this->AddOutput(resource->Name + "-ip", output);
        }
    }

    void AzureResourceManagerTemplate::AddResource(GenericAzureResource *resource) {
        this->resources.push_back(resource);
    }

    void AzureResourceManagerTemplate::AddOutput(std::string name, GenericAzureOutput *g){
        this->outputs.insert(std::pair<std::string, GenericAzureOutput *>(name, g));
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
       
        Json outputs = Json::object();
        for (const auto &[name, output]: this->outputs) {
            outputs[name] = output->ToJson();
        }
        j["outputs"] = outputs;

        return j;
    }
}