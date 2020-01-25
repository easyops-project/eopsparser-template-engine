#if !defined(AZURE_RESOURCE_TEMPLATE)
#define AZURE_RESOURCE_TEMPLATE

#include "../Generics/GenericTemplate.hpp"
#include "GenericAzureResource.hpp"
#include "GenericAzureOutput.hpp"
#include <string>
#include <map>

namespace EOPSTemplateEngine::Azure {
    class AzureResourceManagerTemplate : public EOPSTemplateEngine::Generics::GenericTemplate {
    private:
        std::string $schema;
        std::string contentVersion;

        std::vector<GenericAzureResource *> resources;
        std::map<std::string, GenericAzureOutput *> outputs;
    public:
        explicit AzureResourceManagerTemplate();

        void AddResource(EOPSNativeLib::Models::Resource *resource) override;

        void AddResource(GenericAzureResource *resource);

        void AddOutput(std::string name, GenericAzureOutput *g);

        Json ToJson() override;
    };
}

#endif