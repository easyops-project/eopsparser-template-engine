#include "helperFunctions.hpp"
#include <iostream>
#include <sstream>

namespace EOPSNativeLib::Helpers {
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
        std::cout << requiredVersion << std::endl;
        char reqArr[requiredVersion.size() + 1];
        requiredVersion.copy(reqArr, requiredVersion.size() + 1);
        reqArr[requiredVersion.size()] = '\0';

        int bestIndex = 0;
        int currentIndex = 0;
        int bestCurrentValue = 0;
        std::string bestVal;

        for (auto &version: allVersions) {
            std::cout << "best currentValue " << bestIndex << std::endl;
            std::cout << "best currentString " << bestVal << std::endl;
            int currentValue = 0;

            char newVersion[version.size() + 1];
            version.copy(newVersion, version.size() + 1);
            newVersion[version.size()] = '\0';

            for (size_t i = 0; i < strlen(reqArr); ++i) {
                if (i > strlen(newVersion) - 1) {
                    break;
                }

                std::cout << reqArr[i] << newVersion[i] << std::endl;
                if (reqArr[i] == newVersion[i]) {
                    currentValue += 1;
                }
            }

            if (currentValue > bestCurrentValue) {
                bestIndex = currentIndex;
                bestVal = version;
                bestCurrentValue = currentValue;
            }

            std::cout << "best currentValue after " << bestIndex << std::endl;
            std::cout << "best currentString after " << bestVal << std::endl;
            std::cout << "=======" << std::endl;
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
            std::cout << "Doing " << str << std::endl;
            char sStr[str.size() + 1];
            str.copy(sStr, str.size() + 1);
            sStr[str.size()] = '\0';

            int val = DamerauLevenshtein(fStr, sStr, stringToMatchAgainst.size(), str.size());
            std::cout << val << ' ' << bestCurrentValue << " " << std::endl;
            if (val < bestCurrentValue) {
                bestIndex = currentIndex;
                bestString = str;
                bestCurrentValue = val;
            }
            currentIndex += 1;

            std::cout << "Best string so far: " << bestString << "." << std::endl;
            std::cout << "======" << std::endl;
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
} // namespace EOPSNativeLib::Lib