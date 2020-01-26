#include "OpenMapAPI.hpp"
#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT  

#include <http/http.h>
namespace EOPSTemplateEngine::Helpers::HTTP {
    void from_json(const Json &j, GetCoordsFromQueryResponse &r) {
        r.display_name = j.at("display_name");
        r.lat = std::stod(j["lat"].get<nlohmann::json::string_t>());
        r.lon = std::stod(j["lon"].get<nlohmann::json::string_t>());
    }

    size_t OpenMapsAPI::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    GetCoordsFromQueryResponse &OpenMapsAPI::getCoordsFromQuery(std::string query) {
        const std::string url("nominatim.openstreetmap.org"); 
        httplib::SSLClient cli(url);
        
        std::string path = "/search?format=json&q=" + query;
        const char *newPath = path.c_str();
        auto res = cli.Get(newPath);

        if(res->status == 200) {
            std::vector<GetCoordsFromQueryResponse> foundCoords = Json::parse(res->body);
            GetCoordsFromQueryResponse *r = new GetCoordsFromQueryResponse();
            r->lat = foundCoords[0].lat;
            r->lon = foundCoords[0].lon;
            r->display_name = foundCoords[0].display_name;
            return *r;
        } else {
            GetCoordsFromQueryResponse *g = new GetCoordsFromQueryResponse();
            g->display_name = "Failed...";

            return *g;
        }
    }
}