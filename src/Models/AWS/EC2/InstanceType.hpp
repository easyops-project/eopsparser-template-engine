#if !defined(INSTANCE_TYPE_HEADER)
#define INSTANCE_TYPE_HEADER

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::AWS::EC2 {
struct InstanceType {
  std::string name;
  float cpu;
  float ram;
};

void from_json(const Json &j, InstanceType &s);
bool sortByCpuAndRam(const InstanceType &a, const InstanceType &b);
} // namespace EOPSTemplateEngine::AWS::EC2

#endif // INSTANCE_TYPE_HEADER