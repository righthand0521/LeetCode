#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define KMP (1)  // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
#define STRING_CONCATENATION (1)
   public:
    Solution() {
#if (KMP)
        cout << "Knuth-Morris-Pratt Algorithm\n\n";
#elif (STRING_CONCATENATION)
        cout << "String Concatenation\n\n";
#endif
    }
    bool repeatedSubstringPattern(string s) {
        bool retVal = false;

#if (KMP)
        int sSize = s.size();
        vector<int> next(sSize, 0);

        int j = -1;
        next[0] = j;
        int i;
        for (i = 1; i < sSize; ++i) {
            while ((j >= 0) && (s[i] != s[j + 1])) {
                j = next[j];
            }

            if (s[i] == s[j + 1]) {
                ++j;
            }

            next[i] = j;
        }

        if ((next[sSize - 1] != -1) && (sSize % (sSize - next[sSize - 1] - 1) == 0)) {
            retVal = true;
        }
#elif (STRING_CONCATENATION)
        if ((s + s).find(s, 1) != s.size()) {
            retVal = true;
        }
#endif

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"abab"}, {"aba"}, {"abcabcabcabc"}, {"abac"}, {"bb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "abab"
     *  Output: true
     *
     *  Input: s = "aba"
     *  Output: false
     *
     *  Input: s = "abcabcabcabc"
     *  Output: true
     *
     *  Input: s = "abac"
     *  Output: false
     *
     *  Input: s = "bb"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.repeatedSubstringPattern(testData[i].s);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
