#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numDecodings(string s) {
        int retVal = 0;

        int sSize = s.size();

        /* dp(i): s[1:i]
         *  dp(i) = dp(i-1), s[i-1] != 0
         *  dp(i) = dp(i-2), s[i-2] != 0, 10*s[i-2] + s[i-1] <= 26.
         *  dp(0) = 1
         *
         *  f1 = dp[i], f2 = dp[i-1], f3 = dp[i-2]
         */
        int f1 = 0;
        int f2 = 1;
        int f3 = 0;
        for (int i = 1; i <= sSize; ++i) {
            f3 = 0;
            if (s[i - 1] != '0') {
                f3 += f2;
            }
            if ((i > 1) && (s[i - 2] != '0') && (10 * (s[i - 2] - '0') + (s[i - 1] - '0') <= 26)) {
                f3 += f1;
            }
            f1 = f2;
            f2 = f3;
        }
        retVal = f3;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"12"}, {"226"}, {"06"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "12"
     *  Output: 2
     *
     *  Input: s = "226"
     *  Output: 3
     *
     *  Input: s = "06"
     *  Output: 0
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.numDecodings(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
