#if !defined(CLOUD_FORMATION_TEMPLATE_HEADER)
#define CLOUD_FORMATION_TEMPLATE_HEADER

#include "../Generics/GenericTemplate.hpp"
#include "GenericAWSResource.hpp"
#include <map>
#include <string>
#include "GenericAWSOutput.hpp"

namespace EOPSTemplateEngine::AWS {
    class CloudFormationTemplate
            : public EOPSTemplateEngine::Generics::GenericTemplate {
    private:
        std::string AWSTemplateFormatVersion = "2010-09-09";
        std::string Description = "";
        std::map<std::string, GenericAWSResource *> Resources;
        std::map<std::string, GenericAWSOutput *> Outputs;

    public:
        Json ToJson() override;

        void AddDescription(std::string description);

        void AddResource(std::string name, GenericAWSResource *resource);

        void AddResource(EOPSNativeLib::Models::Resource *resource) override;

        void AddOutput(std::string name, GenericAWSOutput *g);
    };
} // namespace EOPSTemplateEngine::AWS

#endif // MACRO