#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int strangePrinter(string s) {
        int retVal = 0;

        /* https://leetcode.cn/problems/strange-printer/solutions/792309/xin-shou-pian-cong-xiao-wen-ti-zai-dao-q-qifh/
         *  s[i] == s[i]: dp[i][j] = dp[i][j-1]
         *  s[i] != s[j]: dp[i][j] = min(dp[i][i] + dp[i+1][j], dp[i][i+1] + dp[i+1][j], ..., dp[i][j-1] + dp[j-1][j])
         *
         *  Example: Input: s = "abab", Output: 3.
         *      0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3 |   0 1 2 3
         *      a b a b |   a b a b |   a b a b |   a b a b |   a b a b    dp[0][0] + dp[1][3] = 1 + 2 = 3
         *  0 a 0 0 0 0 | a 1 0 0 0 | a 1 2 0 0 | a 1 2 2 0 | a 1 2 2 3 -> dp[0][1] + dp[2][3] = 2 + 2 = 4
         *  1 b 0 0 0 0 | b 0 1 0 0 | b 0 1 2 0 | b 0 1 2 2 | b 0 1 2 2    dp[0][2] + dp[3][3] = 2 + 1 = 3
         *  2 a 0 0 0 0 | a 0 0 1 0 | a 0 0 1 2 | a 0 0 1 2 | a 0 0 1 2
         *  3 b 0 0 0 0 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1 | b 0 0 0 1
         */
        int sSize = s.size();
        vector<vector<int>> dp(sSize, vector<int>(sSize, 0));

        for (int i = sSize - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < sSize; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    int minValue = numeric_limits<int>::max();
                    for (int k = i; k < j; ++k) {
                        minValue = min(minValue, dp[i][k] + dp[k + 1][j]);
                    }
                    dp[i][j] = minValue;
                }
            }
        }
#if (0)
        for (int i = 0; i < sSize; ++i) {
            for (int j = 0; j < sSize; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
#endif
        retVal = dp[0][sSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aaabbb"}, {"aba"}, {"abab"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaabbb"
     *  Output: 2
     *
     *  Input: s = "aba"
     *  Output: 2
     *
     *  Input: s = "abab"
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.strangePrinter(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
