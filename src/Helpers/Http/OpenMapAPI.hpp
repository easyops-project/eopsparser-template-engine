#if !defined(HTTP_REQUESTS_HEADER) 
#define HTTP_REQUESTS_HEADER

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace EOPSTemplateEngine::Helpers::HTTP {
    struct GetCoordsFromQueryResponse {
        std::string display_name;
        double lat;
        double lon;
    };

    void from_json(const Json &j, GetCoordsFromQueryResponse &r);

    class OpenMapsAPI {
    public:
        GetCoordsFromQueryResponse &getCoordsFromQuery(std::string query);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    };
};

#endif