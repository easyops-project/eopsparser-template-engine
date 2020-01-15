#if !defined(AZURE_VIRTUAL_MACHINE)
#define AZURE_VIRTUAL_MACHINE

#include <EOPSNativeLib/Models/Resources/virtualMachine.hpp>
#include "../GenericAzureResource.hpp"
#include "StorageProfile.hpp"
#include "HardwareProfile.hpp"
#include <string>

namespace EOPSTemplateEngine::Azure::Compute {
    class VirtualMachine : public EOPSTemplateEngine::Azure::GenericAzureResource {
    private:
        HardwareProfile *hardwareProfile;
        StorageProfile *storageProfile;

        void setInstanceType(std::string &os, float cpu, float ram, std::string &optimisation);

        void setOs(std::string &os);
        std::vector<Generics::AZLocation> getAZs() override;
    public:
        explicit VirtualMachine(std::string &name, std::string &resourceType, std::string &location);

        void setFromParsedResource(
                EOPSNativeLib::Models::VirtualMachine *res);

        std::string getAvailabilityZoneFromString(std::string zone, std::string currentType);
        Json ToJson() override;
    };
}

#endif