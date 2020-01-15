#if !defined(AZURE_GENERIC_RESOURCE)
#define AZURE_GENERIC_RESOURCE

#include <EOPSNativeLib/Lib/ISerializable.hpp>
#include <EOPSNativeLib/Models/resourceType.hpp>
#include <string>
#include "vector"
#include "../Generics/AZLocation.hpp"

namespace EOPSTemplateEngine::Azure {
    class GenericAzureResource : public EOPSNativeLib::Lib::ISerializable {
    private:
        std::string name;
        std::string type;
        std::string apiVersion;
        std::string location;

        void setLocation(std::string &location);

        void setType(std::string &resourceType);
        virtual std::vector<Generics::AZLocation> getAZs();
    public:
        std::string getLocation();
        std::string getType();
        explicit GenericAzureResource(std::string &name, std::string &resourceType, std::string &location);
        std::string getAvailabilityZoneFromString(std::string zone, std::string currentType);
        Json ToJson() override;
    };
}

#endif