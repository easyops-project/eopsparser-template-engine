#include "InstanceType.hpp"

namespace EOPSTemplateEngine::AWS::EC2 {
    void from_json(const Json &j, InstanceType &s) {
        s.cpu = j.at("cpu");
        s.ram = j.at("ram");
        s.name = j.at("name");
    };

    bool sortByCpuAndRam(const InstanceType &a, const InstanceType &b) {
        if (a.cpu < b.cpu) {
            return true;
        } else if (b.cpu < a.cpu) {
            return false;
        } else if (a.ram < b.ram) {
            return true;
        } else if (b.ram < a.ram) {
            return false;
        } else {
            return false;
        }
    };
} // namespace EOPSTemplateEngine::AWS::EC2