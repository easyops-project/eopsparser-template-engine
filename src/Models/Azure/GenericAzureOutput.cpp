#include "GenericAzureOutput.hpp"

namespace EOPSTemplateEngine::Azure {
    Json GenericAzureOutput::ToJson() {
        Json j;

        j["value"] = this->value;
        j["type"] = "string";

        return j;
    }
}