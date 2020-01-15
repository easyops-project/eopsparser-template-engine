#include "EC2.hpp"
#include "../../Generics/InstanceType.hpp"
#include <fstream>
#include <iostream>

namespace EOPSTemplateEngine::AWS::EC2 {
    Instance::Instance(std::string &name) : GenericAWSResource("AWS::EC2::Instance") {
        this->CpuOptions = *new CpuOption();
        Tag t;
        t.Key = "Name";
        t.Value = name;

        this->Tags.push_back(t);
    }

    void Instance::setAvailabilityZoneFromString(std::string zone) {
        std::string aZone = this->getAvailabilityZoneFromString(zone);

        this->AvailabilityZone = aZone;
    }

    void Instance::setGpuFromSpecification(int vram) {
        ElasticGPUAccelerator gpu;

        if (vram != 1 && vram != 2 && vram != 4 && vram != 8) {
           std::cout << "Your GPU VRAM value is invalid. Will match to the closest value..." << std::endl;
        }

        if (vram <= 1) gpu.Type = "eg1.medium";
        else if (vram <= 2) gpu.Type = "eg1.large";
        else if (vram <= 4) gpu.Type = "eg1.xlarge";
        else gpu.Type = "eg1.2xlarge";

        this->ElasticGpuSpecifications.push_back(gpu);
    }

    void Instance::setImageIdFromOsName(std::string osName) {
//        Aws::EC2::EC2Client ec2;


    }

    void Instance::setInstanceTypeFromSpec(int cores, float ram,
                                           const std::string &optimisation, bool needsGPU) {
        // TODO: Consider how to pick most cost effective instances etc. May need
        // extra fields for internet etc.
        std::ifstream jsonFile;
        jsonFile.open(AWS_INSTANCES);
        auto *chosenInstance = new Generics::InstanceType();
        bool isFound = false;

        if (jsonFile.is_open()) {
            Json j = Json::parse(jsonFile);
            jsonFile.close(); // closing the file straight away

            std::vector<Generics::InstanceType> instanceTypes = j.at(optimisation);
            std::sort(instanceTypes.begin(), instanceTypes.end(), Generics::sortByCpuAndRam);

            for (struct Generics::InstanceType &instance : instanceTypes) {
                if (needsGPU && !instance.isGPUEnabled) {
                    continue;
                }
                if (instance.cpu >= float(cores) && instance.ram >= ram) {
                    chosenInstance->cpu = instance.cpu;
                    chosenInstance->ram = instance.ram;
                    chosenInstance->name = instance.name;
                    isFound = true;
                    break;
                }
            }

            if (!isFound) {
                std::cout << "Did not find a match...";
                std::cout << "Using: " << instanceTypes[0].name << std::endl;
                chosenInstance->cpu = instanceTypes[0].cpu;
                chosenInstance->ram = instanceTypes[0].ram;
                chosenInstance->name = instanceTypes[0].name;
            } else {
                std::cout << "Chosen type: \n- " << chosenInstance->name << " \n- "
                          << chosenInstance->cpu << " cpus \n- " << chosenInstance->ram
                          << " GB Ram " << std::endl;
            }
        } else {
            std::cout << "Error opening the json file. Creating t2.micro instance."
                      << std::endl;
            auto *errorInstance = new Generics::InstanceType();
            errorInstance->name = "t2.micro";
            chosenInstance = errorInstance;
        }

        this->InstanceType = chosenInstance->name;

        if (chosenInstance->cpu > cores) {
            auto *c = new CpuOption();
            c->CoreCount = cores;
            c->ThreadsPerCore = 1;

            this->CpuOptions = *c;
        }
    }

    void Instance::setFromParsedResource(
            EOPSNativeLib::Models::VirtualMachine *res) {
        this->setAvailabilityZoneFromString(res->Location);
        this->setImageIdFromOsName(res->OS);
        this->setInstanceTypeFromSpec(res->Cores, float(res->Ram), res->Optimisation, !res->GPUs.empty());
        this->AddDependencies(res->DependsOn);
        for (auto const &gpu: res->GPUs) {
            for (int i = 0; i < gpu.amount; ++i) {
                this->setGpuFromSpecification(gpu.vram);
            }
        }
    }

    Json Instance::ToJson() {
        Json j = GenericAWSResource::ToJson();
        Json properties = Json::object();

        if (this->CpuOptions.CoreCount != 0 || this->CpuOptions.ThreadsPerCore != 0) {
            properties["CPUOptions"] = this->CpuOptions.ToJson();
        }

        if (!this->ElasticGpuSpecifications.empty()) {
            Json gpus = Json::array();
            for (auto const &gpu: this->ElasticGpuSpecifications) {
                Json j;
                j["Type"] = gpu.Type;
                gpus.push_back(j);
            }
            properties["ElasticGpuSpecifications"] = gpus;
        }
//        j["ImageId"] = this->ImageId;
        properties["InstanceType"] = this->InstanceType;
//        j["KeyName"] = this->KeyName;
        properties["Monitoring"] = this->Monitoring;
        properties["AvailabilityZone"] = this->AvailabilityZone;
//        j["SubnetId"] = this->SubnetId;
        //        j["Tags"] = tags;
//        j["UserData"] = this->UserData;
        //        j["Volumes"] = volumes;
        j["Properties"] = properties;
        return j;
    }

    Json CpuOption::ToJson() {
        Json j = Json::object();
        j["ThreadsPerCore"] = this->ThreadsPerCore;
        j["CoreCount"] = this->CoreCount;

        return j;
    }
} // namespace EOPSTemplateEngine::AWS::EC2