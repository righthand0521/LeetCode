#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    void kmp(vector<int>& next, string pattern) {
        int patternSize = pattern.size();

        int j = 0;
        for (int i = 1; i < patternSize; ++i) {
            while ((j > 0) && (pattern[i] != pattern[j])) {
                j = next[j - 1];
            }

            if (pattern[i] == pattern[j]) {
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
        int haystackIdx = 0;
        int needleIdx = 0;
        while (haystackIdx - needleIdx < haystackSize) {
            while ((needleIdx > 0) && (haystack[haystackIdx % haystackSize] != needle[needleIdx])) {
                needleIdx = next[needleIdx - 1];
            }

            if (haystack[haystackIdx % haystackSize] == needle[needleIdx]) {
                ++needleIdx;
            }

            if (needleIdx == needleSize) {
                retVal = haystackIdx - needleSize + 1;
                break;
            }

            ++haystackIdx;
        }

        return retVal;
    }
    int repeatedStringMatch(string a, string b) {
        int retVal = -1;

        int aSize = a.size();
        int bSize = b.size();
        int index = strStr(a, b);
        if (index == -1) {
            retVal = -1;
        } else if (aSize - index >= bSize) {
            retVal = 1;
        } else {
            retVal = (bSize + index - aSize - 1) / aSize + 2;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string a;
        string b;
    };
    vector<subject> testData{{"abcd", "cdabcdab"}, {"a", "aa"}, {"aaac", "aac"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: a = "abcd", b = "cdabcdab"
     *  Output: 3
     *
     *  Input: a = "a", b = "aa"
     *  Output: 2
     *
     *  Input: a = "aaac", b = "aac"
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: a = \"" << testData[i].a << "\", b = \"" << testData[i].b << "\"\n";

        answer = cSolution.repeatedStringMatch(testData[i].a, testData[i].b);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
