#if !defined(EOPSTemplate_HEADER)
#define EOPSTemplate_HEADER

#include "AWS/CloudFormationTemplate.hpp"
#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Models {
    class EOPSTemplate {
    private:
        EOPSTemplateEngine::AWS::CloudFormationTemplate AWS;

    public:
        EOPSTemplate();

        explicit EOPSTemplate(std::vector<EOPSNativeLib::Models::Resource *> resourcesToBeParsed);

        Json ToJson();
    };
} // namespace EOPSTemplateEngine::Models

#endif // EOPSTemplate_HEADER
