#include "CloudFormationTemplate.hpp"

namespace EOPSTemplateEngine {
namespace AWS {
// CloudFormationTemplate::CreateFromParserOutput() {}
void CloudFormationTemplate::AddDescription(std::string description) {
  this->Description = description;
}

void CloudFormationTemplate::AddResource(std::string name,
                                         GenericAWSResource *resource) {
  this->Resources[name] = resource;
}

Json CloudFormationTemplate::ToJson() {
  Json returnObject = Json::object();
  Json resources = Json::object();

  returnObject["Description"] = this->Description;
  returnObject["AWSTemplateFormatVersion"] = this->AWSTemplateFormatVersion;

  for (const auto &[name, resource] : this->Resources) {
    Json newObj =
        (*resource).ToJson(); // storing as pointers to objects THEREFORE get
                              // the value from pointer (*resource) and apply to
                              // JSON method on that entire object in mem
    returnObject[name] = newObj;
  }

  return returnObject;
}
} // namespace AWS
} // namespace EOPSTemplateEngine