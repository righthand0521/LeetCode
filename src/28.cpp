#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int KMP_START_IDX = -1;

   public:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    void kmp(vector<int>& next, string pattern) {
        int patternSize = pattern.size();

        int j = KMP_START_IDX;
        next[0] = j;
        for (int i = 1; i < patternSize; ++i) {
            while ((j >= 0) && (pattern[i] != pattern[j + 1])) {
                j = next[j];
            }

            if (pattern[i] == pattern[j + 1]) {
                j++;
            }

            next[i] = j;
        }
    }
    int strStr(string haystack, string needle) {
        int retVal = -1;

        int needleSize = needle.size();
        if (needleSize == 0) {
            retVal = 0;
            return retVal;
        }
        vector<int> next(needleSize, 0);
        kmp(next, needle);

        int haystackSize = haystack.size();
        int needleIdx = KMP_START_IDX;
        for (int haystackIdx = 0; haystackIdx < haystackSize; ++haystackIdx) {
            while ((needleIdx >= 0) && (haystack[haystackIdx] != needle[needleIdx + 1])) {
                needleIdx = next[needleIdx];
            }

            if (haystack[haystackIdx] == needle[needleIdx + 1]) {
                ++needleIdx;
            }

            if (needleIdx == needleSize - 1) {
                retVal = haystackIdx - needleSize + 1;
                break;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string haystack;
        string needle;
    };
    vector<subject> testData{{"sadbutsad", "sad"}, {"leetcode", "leeto"}, {"mississippi", "issip"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: haystack = "sadbutsad", needle = "sad"
     *  Output: 0
     *
     *  Input: haystack = "leetcode", needle = "leeto"
     *  Output: -1
     *
     *  Input: haystack = "mississippi", needle = "issip"
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: haystack = \"" << testData[i].haystack << "\", needle = \"" << testData[i].needle << "\"\n";

        answer = cSolution.strStr(testData[i].haystack, testData[i].needle);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
