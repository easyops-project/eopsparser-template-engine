#if !defined(AZURE_RESOURCE_TEMPLATE)
#define AZURE_RESOURCE_TEMPLATE

#include "../Generics/GenericTemplate.hpp"
#include "GenericAzureResource.hpp"
#include <string>

namespace EOPSTemplateEngine::Azure {
    class AzureResourceManagerTemplate : public EOPSTemplateEngine::Generics::GenericTemplate {
    private:
        std::string $schema;
        std::string contentVersion;

        std::vector<GenericAzureResource *> resources;
    public:
        explicit AzureResourceManagerTemplate();

        void AddResource(EOPSNativeLib::Models::Resource *resource) override;

        void AddResource(GenericAzureResource *resource);

        Json ToJson() override;
    };
}

#endif