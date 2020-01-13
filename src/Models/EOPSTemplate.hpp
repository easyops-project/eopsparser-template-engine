#if !defined(EOPSTemplate_HEADER)
#define EOPSTemplate_HEADER

#include "AWS/CloudFormationTemplate.hpp"
#include <EOPSNativeLib/Lib/ISerializable.hpp>
#include "Azure/AzureResourceManagerTemplate.hpp"
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Models {
    class EOPSTemplate {
    private:
        EOPSTemplateEngine::AWS::CloudFormationTemplate AWS;
        EOPSTemplateEngine::Azure::AzureResourceManagerTemplate Azure;

    public:
        EOPSTemplate();

        explicit EOPSTemplate(const std::vector<EOPSNativeLib::Models::Resource *> &resourcesToBeParsed);

        Json ToJson();
    };
} // namespace EOPSTemplateEngine::Models

#endif // EOPSTemplate_HEADER
