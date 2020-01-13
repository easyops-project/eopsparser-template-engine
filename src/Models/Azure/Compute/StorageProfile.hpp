#if !defined(AZURE_STORAGE_PROFILE)
#define AZURE_STORAGE_PROFILE

#include <EOPSNativeLib/Lib/ISerializable.hpp>
#include <string>

namespace EOPSTemplateEngine::Azure::Compute {
//    class ImageReference : public EOPSNativeLib::Lib::ISerializable {
//    public:
//
//        Json ToJson() override;
//
//        std::string getVersion();
//
//        std::string getOffer();
//
//        std::string getSku();
//
//        void setDefault();
//    };
//
    struct ImageReference {
        std::string publisher;
        std::string offer;
        std::string sku;
        std::string version;
    };

    void from_json(const Json &j, ImageReference &s);

    class StorageProfile : public EOPSNativeLib::Lib::ISerializable {
    private:
        ImageReference imageReference;
    public:
        Json ToJson() override;

        void setImageReference(ImageReference &ref);
    };
}

#endif