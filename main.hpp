#if !defined(MAIN_FUNCTIONS)
#define MAIN_FUNCTIONS

#include <napi.h>
#include <string>

namespace EOPSTemplateEngine {
std::string CreateTemplates(std::string resourceArray);
Napi::String CreateTemplatesWrapped(const Napi::CallbackInfo &info);
Napi::Object Init(Napi::Env env, Napi::Object exports);
} // namespace EOPSTemplateEngine

#endif // MAIN_FUNCTIONS