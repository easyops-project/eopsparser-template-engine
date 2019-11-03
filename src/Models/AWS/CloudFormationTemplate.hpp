#if !defined(CLOUD_FORMATION_TEMPLATE_HEADER)
#define CLOUD_FORMATION_TEMPLATE_HEADER

#include "../Generics/GenericTemplate.hpp"
#include "GenericAWSResource.hpp"
#include <map>
#include <string>

namespace EOPSTemplateEngine {
namespace AWS {
class CloudFormationTemplate
    : public EOPSTemplateEngine::Generics::GenericTemplate {
private:
  std::string AWSTemplateFormatVersion = "2010-09-09";
  std::string Description = "";
  std::map<std::string, GenericAWSResource *> Resources;

public:
  Json ToJson();
  void AddDescription(std::string description);
  void AddResource(std::string name, GenericAWSResource *resource);
};
} // namespace AWS
} // namespace EOPSTemplateEngine

#endif // MACRO