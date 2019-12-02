#include "main.hpp"
#include "Models/AWS/EC2/EC2.hpp"
#include "Models/EOPSTemplate.hpp"
#include <EOPSNativeLib/Models/resourceType.hpp>
#include <EOPSNativeLib/Models/Resources/virtualMachine.hpp>
#include <iostream>

namespace EOPSTemplateEngine {
    std::string CreateTemplates(std::string resourceArray) {
        std::vector<EOPSNativeLib::Models::Resource *> resourcesArr;

        Json resources = Json::parse(resourceArray);
        int i = 0;
        for (Json &resource : resources) {
            i = i + 1;

            auto type = resource.at("type").get<std::string>();

            if (type == "Virtual_Machine") {
                auto *res = new EOPSNativeLib::Models::VirtualMachine();
                res->FromJson(resource);
                resourcesArr.push_back(res);
            }
        }

        auto eopsTemplate = EOPSTemplateEngine::Models::EOPSTemplate(resourcesArr);
        Json returnJson = eopsTemplate.ToJson();
        return returnJson.dump();
    };

    Napi::String CreateTemplatesWrapped(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        auto jsonEnv = info[0].ToString();
        Napi::String templatesJsonified =
                Napi::String::New(env, CreateTemplates(jsonEnv));

        return templatesJsonified;
    };

    Napi::Object Init(Napi::Env env, Napi::Object exports) {
        exports.Set(
                "CreateTemplate",
                Napi::Function::New(env, EOPSTemplateEngine::CreateTemplatesWrapped));
        return exports;
    };
} // namespace EOPSTemplateEngine