#if !defined(AZURE_HARDWARE_PROFILE)
#define AZURE_HARDWARE_PROFILE

#include <EOPSNativeLib/Lib/ISerializable.hpp>
#include <string>

namespace EOPSTemplateEngine::Azure::Compute {
    class HardwareProfile : public EOPSNativeLib::Lib::ISerializable {
    private:
        std::string vmSize;
    public:
        Json ToJson() override;

        void setVMSize(std::string size);
    };
}

#endif