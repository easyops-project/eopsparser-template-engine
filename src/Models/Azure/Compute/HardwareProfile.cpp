
#include "HardwareProfile.hpp"

#include <utility>

Json EOPSTemplateEngine::Azure::Compute::HardwareProfile::ToJson() {
    Json j = Json::object();

    j["vmSize"] = this->vmSize;

    return j;
}

void EOPSTemplateEngine::Azure::Compute::HardwareProfile::setVMSize(std::string size) {
    this->vmSize = std::move(size);
}

