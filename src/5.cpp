#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string longestPalindrome(string s) {
        string retVal;

        /* Example: Input: s = "babad"
         *      0 1 2 3 4 |     0 1 2 3 4 |     0 1 2 3 4
         *      b a b a d |     b a b a d |     b a b a d
         *  0 b T         | 0 b T F       | 0 b T F T F F
         *  1 a   T       | 1 a   T F     | 1 a   T F T F
         *  2 b     T     | 2 b     T F   | 2 b     T F F
         *  3 a       T   | 3 a       T F | 3 a       T F
         *  4 d         T | 4 d         T | 4 d         T
         *
         * Example: Input: s = "cbbd"
         *      0 1 2 3 |     0 1 2 3 |     0 1 2 3
         *      c b b d |     c b b d |     c b b d
         *  0 c T       | 0 c T F     | 0 c T F F F
         *  1 b   T     | 1 b   T T   | 1 b   T T F
         *  2 b     T   | 2 b     T F | 2 b     T F
         *  3 d       T | 3 d       T | 3 d       T
         */
        int sSize = s.size();
        int dpSize = sSize;
        vector<vector<int>> dp(dpSize, vector<int>(dpSize, false));
        //
        for (int i = 0; i < dpSize; ++i) {
            dp[i][i] = true;
            retVal = s.substr(i, i - i + 1);
        }
        //
        for (int i = 0; i < sSize - 1; ++i) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                retVal = s.substr(i, (i + 1) - i + 1);
            }
        }
        //
        for (int diff = 2; diff < sSize; ++diff) {
            for (int i = 0; i < sSize - diff; ++i) {
                int j = i + diff;
                if ((s[i] == s[j]) && (dp[i + 1][j - 1] == true)) {
                    dp[i][j] = true;
                    retVal = s.substr(i, j - i + 1);
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"babad"}, {"cbbd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "babad"
     *  Output: "bab"
     *
     *  Input: s = "cbbd"
     *  Output: "bb"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: \"" << testData[i].s << "\"\n";

        answer = cSolution.longestPalindrome(testData[i].s);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
