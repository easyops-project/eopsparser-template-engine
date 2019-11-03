#if !defined(GENERIC_TEMPLATE_HEADER)
#define GENERIC_TEMPLATE_HEADER

#include <EOPSNativeLib/Models/resourceType.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine {
namespace Generics {
class GenericTemplate {
public:
  Json &CreateFromParserOutput(
      std::vector<EOPSNativeLib::Models::Resource *> parsedResources);
};
} // namespace Generics
} // namespace EOPSTemplateEngine

#endif // GENERIC_TEMPLATE_HEADER