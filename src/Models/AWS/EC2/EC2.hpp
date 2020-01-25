#if !defined(EC2_HEADER)
#define EC2_HEADER

#include "../GenericAWSResource.hpp"
#include <EOPSNativeLib/Models/Resources/virtualMachine.hpp>
#include "./ElasticGPUAccelerator.hpp"

namespace EOPSTemplateEngine::AWS::EC2 {
    class CpuOption {
    public:
        int CoreCount;
        int ThreadsPerCore;

        Json ToJson();
    };

    class ElasticVolume {
    private:
        std::string Device;
        std::string VolumeId;
    };

    class Instance : public GenericAWSResource {
    private:
        /*
              "AvailabilityZone" : String,
              "CpuOptions" : CpuOptions,
              "EbsOptimized" : ALWAYS_TRUE_EOPS,
              "ElasticGpuSpecifications" : [ ElasticGpuSpecification, ... ],
              "ImageId" : String,
              "InstanceType" : String,
              "KeyName" : String,
              "Monitoring" : ALWAYS_TRUE_EOPS,
              "SecurityGroupIds" : [ String, ... ],
              "SubnetId" : String,
              "Tags" : [ Tag, ... ],
              "UserData" : String - AVAILABLE_LTR,
              "Volumes" : [ Volume, ... ]
          */

        std::string AvailabilityZone; // check based on allowed values is needed here
        CpuOption *CpuOptions;
        std::vector<ElasticGPUAccelerator> ElasticGpuSpecifications;
        std::string ImageId; // need to do a check. look that bad boy up.
        std::string
                InstanceType;
        std::string
                KeyName; // Requires a key pair to be created. Look that bad boy up.
        const bool Monitoring = true;
        std::vector<std::string> SecurityGroupIds; // requires a security group to be
        // created. Look that bad boy up.
        std::string SubnetId;
        std::vector<Tag> Tags;
        const std::string UserData = ""; // will be used later to bootstrap machines.
        std::vector<ElasticVolume> Volumes; // REQUIRES An EBS Volume. This will be difficult as need to
        // create one and mount it properly. Add if statement to that bad
        // boy to change drive id depending on what has to be done.

        void setAvailabilityZoneFromString(std::string zone);

        void setGpuFromSpecification(int vram);

        void setImageIdFromOsName(std::string osName);

        void setInstanceTypeFromSpec(float cores, float ram, const std::string &optimisation, bool needsGPU);

    public:
        explicit Instance(std::string &name);

        void setFromParsedResource(EOPSNativeLib::Models::VirtualMachine *res);

        Json ToJson() override;
    };
} // namespace EOPSTemplateEngine::AWS::EC2

#endif // EC2_HEADER