#if !defined(AZURE_VIRTUAL_MACHINE)
#define AZURE_VIRTUAL_MACHINE

#include <EOPSNativeLib/Models/Resources/virtualMachine.hpp>
#include "../GenericAzureResource.hpp"
#include "StorageProfile.hpp"
#include "HardwareProfile.hpp"

namespace EOPSTemplateEngine::Azure::Compute {
    class VirtualMachine : public EOPSTemplateEngine::Azure::GenericAzureResource {
    private:
        HardwareProfile *hardwareProfile;
        StorageProfile *storageProfile;

        void setInstanceType(std::string &os, float cpu, float ram, std::string &optimisation);

        void setOs(std::string &os);

    public:
        explicit VirtualMachine(std::string &name, std::string &resourceType, std::string &location);

        void setFromParsedResource(
                EOPSNativeLib::Models::VirtualMachine *res);

        Json ToJson() override;
    };
}

#endif