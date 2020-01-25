#if !defined(GENERIC_AZURE_OUTPUT_HEADER)
#define GENERIC_AZURE_OUTPUT_HEADER

#include <string>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Azure {
    class GenericAzureOutput {
    public:
        std::string value;

        Json ToJson();
    };
}

#endif