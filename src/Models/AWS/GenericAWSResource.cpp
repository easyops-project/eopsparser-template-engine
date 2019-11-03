#include "./GenericAWSResource.hpp"

namespace EOPSTemplateEngine {
namespace AWS {
GenericAWSResource::GenericAWSResource(std::string type) { this->Type = type; };
GenericAWSResource::GenericAWSResource(){};

void GenericAWSResource::AddDependency(std::string resourceName) {
  this->DependsOn.push_back(resourceName);
}
} // namespace AWS
} // namespace EOPSTemplateEngine