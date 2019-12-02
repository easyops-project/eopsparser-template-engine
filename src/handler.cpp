#include "main.hpp"
#include <napi.h>

// Initialize node module
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    EOPSTemplateEngine::Init(env, exports);
    return exports;
}

// Register the module as node module
NODE_API_MODULE(eopstemplateengine, InitAll
);