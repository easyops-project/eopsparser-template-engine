#if !defined(AZURE_HARDWARE_PROFILE)
#define AZURE_HARDWARE_PROFILE

#include <EOPSNativeLib/Helpers/ISerializable.hpp>
#include <string>

namespace EOPSTemplateEngine::Azure::Compute {
    class HardwareProfile : public EOPSNativeLib::Helpers::ISerializable {
    private:
        std::string vmSize;
    public:
        Json ToJson() override;

        void setVMSize(std::string size);
    };
}

#endif