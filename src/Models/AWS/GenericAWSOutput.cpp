#include "./GenericAWSOutput.hpp"

namespace EOPSTemplateEngine::AWS {
    Json GenericAWSOutput::ToJson() {
        Json j;
        j["Description"] = this->Description;
        j["Value"] = this->Value;

        return j;
    }
}