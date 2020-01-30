#include "CloudFormationTemplate.hpp"
#include "../Generics/InstanceType.hpp"
#include "EC2/EC2.hpp"
#include <iostream>

namespace EOPSTemplateEngine::AWS {
// CloudFormationTemplate::CreateFromParserOutput() {}
void CloudFormationTemplate::AddDescription(std::string description) {
  this->Description = description;
}

void CloudFormationTemplate::AddResource(std::string name,
                                         GenericAWSResource *resource) {
  this->Resources.insert(
      std::pair<std::string, GenericAWSResource *>(name, resource));
}

Json CloudFormationTemplate::ToJson() {
  Json returnObject = Json::object();

  returnObject["Description"] = this->Description;
  returnObject["AWSTemplateFormatVersion"] = this->AWSTemplateFormatVersion;
  Json resources = Json::object();
  for (const auto &[name, resource] : this->Resources) {
    Json newObj =
        resource->ToJson(); // storing as pointers to objects THEREFORE get
    // the value from pointer (*resource) and apply to
    // JSON method on that entire object in mem
    resources[name] = newObj;
  }
  returnObject["Resources"] = resources;

  Json outputs = Json::object();
  for (const auto &[name, output] : this->Outputs) {
    Json newObj =
        output->ToJson(); // storing as pointers to objects THEREFORE get
    // the value from pointer (*resource) and apply to
    // JSON method on that entire object in mem
    outputs[name] = newObj;
  }
  returnObject["Outputs"] = outputs;

  return returnObject;
}

void CloudFormationTemplate::AddResource(
    EOPSNativeLib::Models::Resource *resource) {
  if (resource->Type == "Virtual_Machine") {
    auto *resourceToBeAdded = new EC2::Instance(resource->Name);
    resourceToBeAdded->setFromParsedResource(
        dynamic_cast<EOPSNativeLib::Models::VirtualMachine *>(resource));
    this->AddResource(resource->Name, resourceToBeAdded);

    GenericAWSOutput *g = new GenericAWSOutput();
    g->Description = "IP Address of " + resource->Name;
    g->Value = "!GetAtt " + resource->Name + ".PublicIp";

    this->AddOutput(resource->Name + "ip", g);
  }
}

void CloudFormationTemplate::AddOutput(std::string name, GenericAWSOutput *g) {
  this->Outputs.insert(std::pair<std::string, GenericAWSOutput *>(name, g));
}
} // namespace EOPSTemplateEngine::AWS