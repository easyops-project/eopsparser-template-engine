#if !defined(GENERIC_RESOURCE_HEADER)
#define GENERIC_RESOURCE_HEADER

#include <EOPSNativeLib/Lib/ISerializable.hpp>
#include <EOPSNativeLib/Models/resourceType.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::AWS {
    struct Tag {
        std::string Key;
        std::string Value;
    };

    class GenericAWSResource : public EOPSNativeLib::Lib::ISerializable {
    private:
        std::string Type = "";
        std::vector<std::string> DependsOn;


    public:
        GenericAWSResource();

        explicit GenericAWSResource(std::string type);

        void AddDependencies(std::vector<std::string> &resources);

        Json ToJson() override;

        virtual ~GenericAWSResource();

        std::string getAvailabilityZoneFromString(std::string zone);
    };
} // namespace EOPSTemplateEngine::AWS

#endif // GENERIC_RESOURCE_HEADER