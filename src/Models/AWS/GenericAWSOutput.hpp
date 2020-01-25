#if !defined(GENERIC_AWS_OUTPUT)
#define GENERIC_AWS_OUTPUT

#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::AWS
{
    class GenericAWSOutput {
    public:
        std::string Description;
        std::string Value;

        Json ToJson();
    };
} // namespace EOPSTemplateEngine::AWS

#endif