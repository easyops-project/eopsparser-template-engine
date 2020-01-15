#include "OpenMapAPI.hpp"
#include <curl/curl.h>
#include <iostream>

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
        const std::string url("https://nominatim.openstreetmap.org/search?format=json&q=" + query);
        long httpCode(0);
        std::string data;
        CURL *curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "EasyOPS Template Engine");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OpenMapsAPI::WriteCallback);
        
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        if(httpCode == 200) {
            std::vector<GetCoordsFromQueryResponse> foundCoords = Json::parse(data);
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