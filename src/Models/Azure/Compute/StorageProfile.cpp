#include "StorageProfile.hpp"

// Image reference
Json EOPSTemplateEngine::Azure::Compute::ImageReference::ToJson() {
    Json j = Json::object();

    !this->id.empty() ? j["id"] = this->id : "";
    !this->offer.empty() ? j["offer"] = this->id : "";
    !this->publisher.empty() ? j["publisher"] = this->id : "";
    !this->version.empty() ? j["version"] = this->id : "";
    !this->sku.empty() ? j["sku"] = this->id : "";

    return j;
}

void from_json(const Json &j, EOPSTemplateEngine::Azure::Compute::ImageReference &s) {
    s.id = j.at("id");
    s.offer = j.at("offer");
    s.publisher = j.at("publisher");
    s.sku = j.at("sku");
    s.version = j.at("version");
}

std::string EOPSTemplateEngine::Azure::Compute::ImageReference::getVersion() {
    return this->version;
}

std::string EOPSTemplateEngine::Azure::Compute::ImageReference::getSku() {
    return this->sku;
}

std::string EOPSTemplateEngine::Azure::Compute::ImageReference::getOffer() {
    return this->offer;
}

void EOPSTemplateEngine::Azure::Compute::ImageReference::setDefault() {
    this->offer = "UbuntuServer";
    this->publisher = "Canonical";
    this->version = "latest";
}

// storage profile
Json EOPSTemplateEngine::Azure::Compute::StorageProfile::ToJson() {
    Json j = Json::object();

    j["imageReference"] = this->imageReference.ToJson();

    return j;
}

void EOPSTemplateEngine::Azure::Compute::StorageProfile::setImageReference(
        EOPSTemplateEngine::Azure::Compute::ImageReference &ref) {
    this->imageReference = ref;
}
