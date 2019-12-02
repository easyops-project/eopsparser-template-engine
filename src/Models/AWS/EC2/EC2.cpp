#include "EC2.hpp"
#include "InstanceType.hpp"
#include <fstream>
#include <iostream>

namespace EOPSTemplateEngine::AWS::EC2 {
    Instance::Instance(std::string name) : GenericAWSResource("AWS::EC2::Instance") {
        Tag t;
        t.Key = "Name";
        t.Value = name;

        this->Tags.push_back(t);
    }

    void Instance::setAvailabilityZoneFromString(std::string zone) {
        std::string aZone = this->getAvailabilityZoneFromString(zone);
        this->AvailabilityZone = aZone;
    }

    void Instance::setGpuFromSpecification(int vram) {}

    void Instance::setImageIdFromOsName(std::string osName) {}

    void Instance::setInstanceTypeFromSpec(int cores, float ram,
                                           const std::string &optimisation) {
//TODO: Consider how to pick most cost effective instances etc. May need extra fields for internet etc.
        std::ifstream jsonFile;
        jsonFile.open(PATH_TO_JSON);
        EC2::InstanceType *chosenInstance;
        bool isFound = false;

        if (jsonFile.is_open()) {
            Json j = Json::parse(jsonFile);
            jsonFile.close(); // closing the file straight away

            std::vector<EC2::InstanceType> instanceTypes = j.at(optimisation);
            std::sort(instanceTypes.begin(), instanceTypes.end(), sortByCpuAndRam);
            for (struct InstanceType &instance: instanceTypes) {
                if (instance.cpu >= float(cores) && instance.ram >= ram) {
                    chosenInstance = &instance;
                    isFound = true;
                    break;
                }
            }

            if (!isFound) {
                std::cout << "Did not find a match...";
                std::cout << "Using: " << instanceTypes[0].name << std::endl;
                chosenInstance = &instanceTypes[0];
            } else {
                std::cout << "Chosen type: \n- " << chosenInstance->name << " \n- " << chosenInstance->cpu
                          << " cpus \n- "
                          << chosenInstance->ram << " GB Ram "
                          << std::endl;
            }
        } else {
            std::cout << "Error opening the json file. Creating t2.micro instance." << std::endl;
            EC2::InstanceType *instance;
            instance->name = "t2.micro";
            chosenInstance = instance;
        }

        this->InstanceType = chosenInstance->name;
        std::cout << chosenInstance->name << std::endl;
        std::cout << this->InstanceType << std::endl;

        if (chosenInstance->cpu > cores) {
            CpuOption c;
            c.CoreCount = cores;
            c.ThreadsPerCore = 1;

            this->CpuOptions = c;
        }
    }

    void Instance::setFromParsedResource(EOPSNativeLib::Models::VirtualMachine *res) {
        this->setAvailabilityZoneFromString(res->Location);
        this->setImageIdFromOsName(res->OS);
        this->setInstanceTypeFromSpec(res->Cores, float(res->Ram), res->Optimisation);
    }

    Json Instance::ToJson() {
        Json j = GenericAWSResource::ToJson();
        if (this->CpuOptions.CoreCount != 0 || this->CpuOptions.ThreadsPerCore != 0) {
            j["CPUOptions"] = this->CpuOptions.ToJson();
        }

        j["EbsOptimised"] = this->EbsOptimisied;
//        j["ElasticGpuSpecifications"] = elasticGPUs;
        j["ImageId"] = this->ImageId;
        j["InstanceType"] = this->InstanceType;
        j["KeyName"] = this->KeyName;
        j["Monitoring"] = this->Monitoring;
//        j["SecurityGroupIds"] = securityGroupIds;
        j["SubnetId"] = this->SubnetId;
//        j["Tags"] = tags;
        j["UserData"] = this->UserData;
//        j["Volumes"] = volumes;

        return j;
    }

    void Instance::setSecurityGroupFromRequirements(std::vector<std::string> &allowed_in,
                                                    std::vector<std::string> &allowed_out) {

    }

    Json CpuOption::ToJson() {
        Json j = Json::object();
        j["ThreadsPerCore"] = this->ThreadsPerCore;
        j["CoreCount"] = this->CoreCount;

        return j;
    }
} // namespace EOPSTemplateEngine::AWS::EC2