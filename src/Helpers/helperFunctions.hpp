#if !defined(HELPER_FUNCTIONS_HEADER)
#define HELPER_FUNCTIONS_HEADER

#include <string>
#include <vector>

namespace EOPSTemplateEngine::Helpers {
    class HelperFunctions {
    private:
        static double degreeToRadians(double degrees);
    public:
        static int DamerauLevenshtein(const char A[2000], const char B[2000], int m, int n);

        static int
        returnIndexOfClosestString(std::string &stringToMatchAgainst, std::vector<std::string> &possibleValues);

        static std::vector<std::string> splitStringByDelimiter(const std::string &s, char delimiter);

        static int returnIndexOfClosestVersion(std::string &requiredVersion, std::vector<std::string> &allVersions);
        static int getClosestRegionPerCoordinates(double lat, double lon, std::vector<std::pair<double, double>> availableCoordinates);
    };
};

#endif // HELPER_FUNCTIONS_HEADER
