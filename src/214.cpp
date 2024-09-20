#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
    vector<int> kmp(string s) {
        vector<int> retVal;

        int sSize = s.size();

        retVal.resize(sSize, 0);
        int length = 0;
        for (int i = 1; i < sSize; i++) {
            while ((length > 0) && (s[i] != s[length])) {
                length = retVal[length - 1];
            }

            if (s[i] == s[length]) {
                length++;
            }

            retVal[i] = length;
        }

        return retVal;
    }

   public:
    string shortestPalindrome(string s) {
        string retVal = s;

        string reversedString = string(s.rbegin(), s.rend());
        string combinedString = s + "#" + reversedString;

        vector<int> prefixTable = kmp(combinedString);
        int palindromeLength = prefixTable[combinedString.length() - 1];

        string suffix = reversedString.substr(0, s.length() - palindromeLength);
        retVal = suffix + s;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aacecaaa"}, {"abcd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aacecaaa"
     *  Output: "aaacecaaa"
     *
     *  Input: s = "abcd"
     *  Output: "dcbabcd"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.shortestPalindrome(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
