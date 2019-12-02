#include "EOPSTemplate.hpp"
#include <iostream>

namespace EOPSTemplateEngine::Models {
    Json EOPSTemplate::ToJson() {
        Json result = Json::object();
        Json aws = this->AWS.ToJson();
        result["AWS"] = aws;
        return result;
    }

    EOPSTemplate::EOPSTemplate(std::vector<EOPSNativeLib::Models::Resource *> resourcesToBeParsed) {
        for (EOPSNativeLib::Models::Resource *resource : resourcesToBeParsed) {
            if (resource->Provider == "aws") {
                this->AWS.AddResource(resource);
            }
        }
    }
} // namespace EOPSTemplateEngine::Models