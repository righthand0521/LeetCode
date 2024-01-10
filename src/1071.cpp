#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    string gcdOfStrings(string str1, string str2) {
        string retVal = "";

        /* Math: Greatest Common Divisor
         *  if str1 and str2 have Greatest Common Divisor of Strings
         *  let str1 = m * (substr), str2 = n * (substr)
         *  => str1 + str2 = m * (substr) + n * (substr) = (m + n)(substr)
         *  => str2 + str1 = n * (substr) + m * (substr) = (n + m)(substr)
         *  => str1 + str2 = str2 + str1
         *  let lenStr1 = m * lenSubstr, lenStr2 = n * lenSubstr
         *  => gcd(lenStr1, lenStr2) = lenSubstr
         *  Hence, str1 and str2 Greatest Common Divisor of Strings is str1[0:lenSubstr] or str2[0:lenSubstr]
         */
        if (str1 + str2 != str2 + str1) {
            return retVal;
        }

        int gcdLength = gcd(str1.size(), str2.size());
        retVal = str1.substr(0, gcdLength);

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string str1;
        string str2;
    };
    vector<subject> testData{{"ABCABC", "ABC"},
                             {"ABABAB", "ABAB"},
                             {"LEET", "CODE"},
                             {"TAUXXTAUXXTAUXXTAUXXTAUXX", "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"},
                             {"ABABCCABAB", "ABAB"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: str1 = "ABCABC", str2 = "ABC"
     *  Output: "ABC"
     *
     *  Input: str1 = "ABABAB", str2 = "ABAB"
     *  Output: "AB"
     *
     *  Input: str1 = "LEET", str2 = "CODE"
     *  Output: ""
     *
     *  Input: str1 = "TAUXXTAUXXTAUXXTAUXXTAUXX", str2 = "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX"
     *  Output: "TAUXX"
     *
     *  Input: str1 = "ABABCCABAB", str2 = "ABAB"
     *  Output: ""
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: str1 = \"" << testData[i].str1 << "\"";
        cout << ", str2 = \"" << testData[i].str2 << "\"\n";

        answer = cSolution.gcdOfStrings(testData[i].str1, testData[i].str2);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
