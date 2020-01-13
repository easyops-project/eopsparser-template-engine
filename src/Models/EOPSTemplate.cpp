#include "EOPSTemplate.hpp"
#include <iostream>

namespace EOPSTemplateEngine::Models {
    Json EOPSTemplate::ToJson() {
        Json result = Json::object();
        Json aws = this->AWS.ToJson();
        Json azure = this->Azure.ToJson();
        result["AWS"] = aws;
        result["Azure"] = azure;
        return result;
    }

    EOPSTemplate::EOPSTemplate(const std::vector<EOPSNativeLib::Models::Resource *> &resourcesToBeParsed) {
        for (EOPSNativeLib::Models::Resource *resource : resourcesToBeParsed) {
            if (resource->Provider == "aws") {
                this->AWS.AddResource(resource);
            } else if (resource->Provider == "azure") {
                this->Azure.AddResource(resource);
            }
        }
    }

    EOPSTemplate::EOPSTemplate() = default;
} // namespace EOPSTemplateEngine::Models