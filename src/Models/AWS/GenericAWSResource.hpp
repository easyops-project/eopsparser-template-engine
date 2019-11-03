#if !defined(GENERIC_RESOURCE_HEADER)
#define GENERIC_RESOURCE_HEADER

#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using Json = nlohmann::json;

namespace EOPSTemplateEngine {
namespace AWS {
struct Tag {
  std::string Key;
  std::string Value;
};

class GenericAWSResource : public EOPSNativeLib::Helpers::ISerializable {
private:
  std::string Type = "";
  std::vector<std::string> DependsOn;

public:
  GenericAWSResource();
  GenericAWSResource(std::string type);
  void AddDependency(std::string resourceName);
  Json ToJson() override;
  virtual ~GenericAWSResource();
  virtual void setFromParsedResource(
      EOPSNativeLib::Models::Resource
          res); // not setting this as virtual as it should be overridable
};
} // namespace AWS
} // namespace EOPSTemplateEngine

#endif // GENERIC_RESOURCE_HEADER