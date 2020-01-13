#include "StorageProfile.hpp"

namespace EOPSTemplateEngine::Azure::Compute {
// Image reference
    void to_json(Json &j, const ImageReference &p) {
        !p.offer.empty() ? j["offer"] = p.offer : "";
        !p.publisher.empty() ? j["publisher"] = p.publisher : "";
        !p.version.empty() ? j["version"] = p.version : "";
        !p.sku.empty() ? j["sku"] = p.sku : "";
    }

    void from_json(const Json &j, ImageReference &s) {
        s.offer = j.at("offer");
        s.publisher = j.at("publisher");
        s.sku = j.at("sku");
        s.version = j.at("version");
    }

// storage profile
    Json StorageProfile::ToJson() {
        Json j = Json::object();

        j["imageReference"] = this->imageReference;

        return j;
    }

    void StorageProfile::setImageReference(
            ImageReference &ref) {
        this->imageReference = ref;
    }
}
