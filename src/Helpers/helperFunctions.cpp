#include "helperFunctions.hpp"
#include <iostream>
#include <sstream>
#include <math.h>
#include <cstring>

namespace EOPSTemplateEngine::Helpers {
    int HelperFunctions::DamerauLevenshtein(const char A[2000], const char B[2000], int m, int n) {
        int table[m + 1][n + 1];

        int cost;
        int counter = 0;

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                table[i][j] = 0;
            }
        }
        for (int i = 0; i <= m; i++) {
            table[i][0] = i;
        }
        for (int j = 0; j <= n; j++) {
            table[0][j] = j;
        }

        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= m; i++) {
                counter++;

                if (A[i - 1] == B[j - 1]) {
                    cost = 0;
                } else {
                    cost = 1;
                }

                int minimum, deletion, substitution, insertion;

                deletion = table[i - 1][j] + 1;
                insertion = table[i][j - 1] + 1;
                substitution = table[i - 1][j - 1] + cost;

                minimum = deletion;
                if (insertion < minimum) {
                    minimum = insertion;
                } else if (substitution < minimum) {
                    minimum = substitution;
                }

                table[i][j] = minimum;

                if ((i > 1 and j > 1)) {
                    if ((A[i - 1] == B[j - 2]) and (A[i - 2] == B[j - 1])) {

                        int transposition = table[i - 2][j - 2] + cost;

                        if (table[i][j] > transposition) {
                            table[i][j] = transposition;
                        }
                    }
                }
            }
        }

        return table[m][n];
    }

    int
    HelperFunctions::returnIndexOfClosestVersion(std::string &requiredVersion, std::vector<std::string> &allVersions) {
        char reqArr[requiredVersion.size() + 1];
        requiredVersion.copy(reqArr, requiredVersion.size() + 1);
        reqArr[requiredVersion.size()] = '\0';

        int bestIndex = 0;
        int currentIndex = 0;
        int bestCurrentValue = 0;
        std::string bestVal;

        for (auto &version: allVersions) {
            int currentValue = 0;

            char newVersion[version.size() + 1];
            version.copy(newVersion, version.size() + 1);
            newVersion[version.size()] = '\0';

            for (size_t i = 0; i < strlen(reqArr); ++i) {
                if (i > strlen(newVersion) - 1) {
                    break;
                }

                if (reqArr[i] == newVersion[i]) {
                    currentValue += 1;
                }
            }

            if (currentValue > bestCurrentValue) {
                bestIndex = currentIndex;
                bestVal = version;
                bestCurrentValue = currentValue;
            }

            currentIndex += 1;
        }

        return bestIndex;
    }

    int HelperFunctions::returnIndexOfClosestString(std::string &stringToMatchAgainst,
                                                    std::vector<std::string> &possibleValues) {
        int bestIndex = 0;
        std::string bestString;
        int currentIndex = 0;
        int bestCurrentValue = 99999; //setting it high because we want lowest distance

        char fStr[stringToMatchAgainst.size() + 1];
        stringToMatchAgainst.copy(fStr, stringToMatchAgainst.size() + 1);
        fStr[stringToMatchAgainst.size()] = '\0';

        for (auto &str: possibleValues) {
            char sStr[str.size() + 1];
            str.copy(sStr, str.size() + 1);
            sStr[str.size()] = '\0';

            int val = DamerauLevenshtein(fStr, sStr, stringToMatchAgainst.size(), str.size());
            if (val < bestCurrentValue) {
                bestIndex = currentIndex;
                bestString = str;
                bestCurrentValue = val;
            }
            currentIndex += 1;
        }

//        auto pair = new std::pair<std::string, int>(bestString, bestIndex);
        return bestIndex;
    }

    std::vector<std::string> HelperFunctions::splitStringByDelimiter(const std::string &s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    double HelperFunctions::degreeToRadians(double degrees) {
       return degrees * (M_PI / 180);
    }

// HAVERSINE FORMULA assuming Earth is a perfect sphere
/*
https://community.esri.com/servlet/JiveServlet/downloadImage/38-57595-375715/Circle-trig6_svg.png
a = sin²(φB - φA/2) + cos φA * cos φB * sin²(λB - λA/2)
c = 2 * atan2( √a, √(1−a) )
d = R ⋅ c
*/
    int HelperFunctions::getClosestRegionPerCoordinates(double lat, double lon, std::vector<std::pair<double, double>> availableCoordinates) {
        int bestIndex = -1;
        int currentIndex = 0;
        double currentBestDistance = 9999999;

        for(auto const &[latitude, longitude]: availableCoordinates) {
            double lat1InRad = degreeToRadians(lat);
            double lat2InRad = degreeToRadians(latitude);

            double differenceLat = (latitude - lat) * 
                            M_PI / 180.0; 
            double differenceLon = (longitude - lon) *  
                            M_PI / 180.0; 

            double a = pow(sin(differenceLat / 2), 2) +  
                   (pow(sin(differenceLon / 2), 2) *  
                   cos(lat1InRad) * cos(lat2InRad)); 

            double rad = 6371; 
            double c = 2 * asin(sqrt(a)); 
            double distance = rad * c; 

            if(currentBestDistance > distance) {
                currentBestDistance = distance;
                bestIndex = currentIndex;
            }

            currentIndex += 1;
        }

        return bestIndex;
    }
} // namespace EOPSNativeLib::Lib