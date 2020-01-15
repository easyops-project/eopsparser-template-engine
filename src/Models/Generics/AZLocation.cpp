#include "AZLocation.hpp"

namespace EOPSTemplateEngine::Generics {
    void from_json(const Json &j, AZLocation &a) {
        a.zone = j.at("zone");
        a.lat = j.at("lat");
        a.lon = j.at("lon");
        j.at("availableResources").get_to<std::vector<std::string>>(a.availableResources);

        if(j.count("enabledVMSizes") != 0) {
            std::vector<std::string> s;
            j.at("enabledVMSizes").get_to<std::vector<std::string>>(s);

            a.enabledVMSizes = s;
        }
    }
}