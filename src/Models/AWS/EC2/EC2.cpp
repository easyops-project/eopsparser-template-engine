#include "EC2.hpp"
#include "../../Generics/InstanceType.hpp"
#include <fstream>
#include <iostream>
#include "../../../Helpers/helperFunctions.hpp"

namespace EOPSTemplateEngine::AWS::EC2 {
    Instance::Instance(std::string &name) : GenericAWSResource("AWS::EC2::Instance") {
        Tag t;
        t.Key = "Name";
        t.Value = name;

        this->Tags.push_back(t);

        this->CpuOptions = new CpuOption();
        this->CpuOptions->ThreadsPerCore = 0;
        this->CpuOptions->CoreCount = 0;
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
        std::ifstream file;
        file.open(AWS_OS_AMI_CACHE);

        if(file.is_open()) {
            Json j = Json::parse(file);
            file.close();
            std::transform(osName.begin(), osName.end(), osName.begin(), ::tolower);

            if(osName.find("ubuntu") != std::string::npos) {
                if(osName.find('@')) {
                    std::vector<std::string> split = Helpers::HelperFunctions::splitStringByDelimiter(osName, '@');

                    std::string version = split[1];
                    if (version.rfind("19", 0) == 0) {
                        this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                    } else if (version.rfind("18", 0) == 0) {
                        this->ImageId = j.at("ubuntu1804").at(this->AvailabilityZone);
                    } else if (version.rfind("16", 0) == 0) {
                        this->ImageId = j.at("ubuntu1604").at(this->AvailabilityZone);
                    } else if (version.rfind("14", 0) == 0) {
                        this->ImageId = j.at("ubuntu1404").at(this->AvailabilityZone);  
                    } else if (version.rfind("12", 0) == 0) {
                        this->ImageId = j.at("ubuntu1204").at(this->AvailabilityZone);
                    } else {
                        this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                    }

                    if(this->ImageId == "") {
                        std::cout << "Ubuntu " << version << " is not available in this region. Setting to 18.04..." << std::endl;
                        this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                    }
                } else {
                    this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                }
            } else if(osName.find("rhel") != std::string::npos) {
                this->ImageId = j.at("rhel").at(this->AvailabilityZone);
            } else if(osName.find("freebsd") != std::string::npos) {
                this->ImageId = j.at("freebsd11").at(this->AvailabilityZone);

                if(this->ImageId == "") {
                    std::cout << "FreeBSD is not available in this region. Setting to amazon os..." << std::endl;
                    this->ImageId = j.at("amazon2").at(this->AvailabilityZone);
                }
            } else if(osName.find("centos") != std::string::npos) {
                if(osName.find('@')) {
                    std::vector<std::string> split = Helpers::HelperFunctions::splitStringByDelimiter(osName, '@');

                    std::string version = split[1];
                    if (version.rfind("7", 0) == 0) {
                        this->ImageId = j.at("centos7").at(this->AvailabilityZone);
                    } else if (version.rfind("6", 0) == 0) {
                        this->ImageId = j.at("centos6").at(this->AvailabilityZone);
                    } else {
                        this->ImageId = j.at("centos7").at(this->AvailabilityZone);
                    }

                    if(this->ImageId == "") {
                        std::cout << "CentOS " << version << " is not available in this region. Setting to Amazon Linux..." << std::endl;
                        this->ImageId = j.at("amazon").at(this->AvailabilityZone);
                    }
                } else {
                    this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                }
            } else if(osName.find("amazon2") != std::string::npos) {
                this->ImageId = j.at("amazon2").at(this->AvailabilityZone);
            } else if(osName.find("amazon") != std::string::npos) {
                this->ImageId = j.at("amazon").at(this->AvailabilityZone);
            } else if(osName.find("windows") != std::string::npos) {
                if(osName.find('@')) {
                    std::vector<std::string> split = Helpers::HelperFunctions::splitStringByDelimiter(osName, '@');

                    std::string version = split[1];
                    if (version.rfind("2019", 0) == 0 || version.rfind("19", 0) == 0) {
                        this->ImageId = j.at("windows2019").at(this->AvailabilityZone);
                    } else if (version.rfind("2016", 0) == 0 || version.rfind("16", 0) == 0) {
                        this->ImageId = j.at("windows2016").at(this->AvailabilityZone);
                    } else if (version.rfind("2012r2", 0) == 0 || version.rfind("12r2", 0) == 0 || version.rfind("2012 r2", 0) == 0 || version.rfind("12 r2", 0) == 0) {
                        this->ImageId = j.at("windows2012R2").at(this->AvailabilityZone);
                    } else if (version.rfind("2012", 0) == 0 || version.rfind("12", 0) == 0) {
                        this->ImageId = j.at("windows2012").at(this->AvailabilityZone);
                    } else {
                        this->ImageId = j.at("windows2019").at(this->AvailabilityZone);
                    }

                    if(this->ImageId == "") {
                        std::cout << "Windows " << version << " is not available in this region. Setting to Windows Server 2019..." << std::endl;
                        this->ImageId = j.at("windows2019").at(this->AvailabilityZone);
                    }
                } else {
                    this->ImageId = j.at("ubuntu1904").at(this->AvailabilityZone);
                }
            } else {
                this->ImageId = "ami-071f4ce599deff521";
            }
        }
    }

    void Instance::setInstanceTypeFromSpec(float cores, float ram,
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

            this->CpuOptions = c;
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

        if (this->CpuOptions->CoreCount != 0 && this->CpuOptions->ThreadsPerCore != 0) {
            properties["CPUOptions"] = this->CpuOptions->ToJson();
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
        properties["ImageId"] = this->ImageId;
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