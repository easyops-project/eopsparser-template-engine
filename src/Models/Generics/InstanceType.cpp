#include "InstanceType.hpp"

namespace EOPSTemplateEngine::Generics {
    void from_json(const Json &j, InstanceType &s) {
        s.cpu = j.at("cpu");
        s.ram = j.at("ram");
        s.name = j.at("name");

        if (s.isGPUEnabled != std::nullopt) s.isGPUEnabled = j.at("isGPUEnabled");
    };

    bool sortByCpuAndRam(const InstanceType &a, const InstanceType &b) {
        if (a.cpu < b.cpu) {
            return true;
        } else if (b.cpu < a.cpu) {
            return false;
        } else return a.ram < b.ram;
    };
} // namespace EOPSTemplateEngine::AWS::EC2