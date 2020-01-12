#if !defined(AZURE_STORAGE_PROFILE)
#define AZURE_STORAGE_PROFILE

#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <string>

namespace EOPSTemplateEngine::Azure::Compute {
    class ImageReference : public EOPSNativeLib::Helpers::ISerializable {
    public:
        std::string id;
        std::string publisher;
        std::string offer;
        std::string sku;
        std::string version;

        Json ToJson() override;

        std::string getVersion();

        std::string getOffer();

        std::string getSku();

        void setDefault();
    };

    void from_json(const Json &j, ImageReference &s);

    class StorageProfile : public EOPSNativeLib::Helpers::ISerializable {
    private:
        ImageReference imageReference;
    public:
        Json ToJson() override;

        void setImageReference(ImageReference &ref);
    };
}

#endif