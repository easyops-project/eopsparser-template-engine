#if !defined(EOPSTemplate)
#define EOPSTemplate

#include "AWS/CloudFormationTemplate.hpp"
#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine {
namespace Models {
class EOPSTemplate {
private:
  EOPSTemplateEngine::AWS::CloudFormationTemplate AWS;

public:
  Json ToJson();
};
} // namespace Models
} // namespace EOPSTemplateEngine

#endif // EOPSTemplate
