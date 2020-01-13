#if !defined(HELPER_FUNCTIONS_HEADER)
#define HELPER_FUNCTIONS_HEADER

#include <string>
#include <vector>

namespace EOPSNativeLib::Helpers {
    class HelperFunctions {
    public:
        static int DamerauLevenshtein(const char A[2000], const char B[2000], int m, int n);

        static int
        returnIndexOfClosestString(std::string &stringToMatchAgainst, std::vector<std::string> &possibleValues);

        static std::vector<std::string> splitStringByDelimiter(const std::string &s, char delimiter);

        static int returnIndexOfClosestVersion(std::string &requiredVersion, std::vector<std::string> &allVersions);
    };
};

#endif // HELPER_FUNCTIONS_HEADER
