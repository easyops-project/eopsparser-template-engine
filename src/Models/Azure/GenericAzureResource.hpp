#if !defined(AZURE_GENERIC_RESOURCE)
#define AZURE_GENERIC_RESOURCE

#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <EOPSNativeLib/Models/resourceType.hpp>
#include <string>

namespace EOPSTemplateEngine::Azure {
    class GenericAzureResource : public EOPSNativeLib::Helpers::ISerializable {
    private:
        std::string name;
        std::string type;
        std::string apiVersion;
        std::string location;

        void setLocation(std::string &location);

        void setType(std::string &resourceType);

    public:
        explicit GenericAzureResource(std::string &name, std::string &resourceType, std::string &location);

        Json ToJson() override;
    };
}

#endif