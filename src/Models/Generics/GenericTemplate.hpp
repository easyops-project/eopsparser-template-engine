#if !defined(GENERIC_TEMPLATE_HEADER)
#define GENERIC_TEMPLATE_HEADER

#include <EOPSNativeLib/Models/resourceType.hpp>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Generics {
    class GenericTemplate {
    public:
        virtual void AddResource(EOPSNativeLib::Models::Resource *resource) = 0;
    };
} // namespace EOPSTemplateEngine

#endif // GENERIC_TEMPLATE_HEADER