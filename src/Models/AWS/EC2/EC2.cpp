#include "EC2.hpp"

namespace EOPSTemplateEngine {
namespace AWS {
namespace EC2 {
Instance::Instance(std::string name) {
  GenericAWSResource("AWS::EC2::Instance");

  Tag t;
  t.Key = "Name";
  t.Value = name;

  this->Tags.push_back(t);
}
} // namespace EC2
} // namespace AWS
} // namespace EOPSTemplateEngine