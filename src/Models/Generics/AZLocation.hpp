#if !defined(AZ_LOCATION_HEADER) 
#define AZ_LOCATION_HEADER

#include <string>
#include <nlohmann/json.hpp>
#include <vector>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Generics {
    struct AZLocation {
        std::string zone;
        double lat;
        double lon;
        std::vector<std::string> availableResources;
        std::optional<std::vector<std::string>> enabledVMSizes;
    };

    void from_json(const Json &j, AZLocation &a);
}

#endif