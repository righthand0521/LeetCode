#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestPalindromeSubseq(string s) {
        int retVal = 0;

        /* dp[i][j]: the longest palindromic subsequence's length of substring(i, j)
         *  +-----------------------+   +-------------------+
         *  |   | b | b | b | a | b |   |   | c | b | b | d |
         *  |---+---+---+---+---+---|   |---+---+---+---+---|
         *  | b | 1 | 2 | 3 | 3 |[4]|   | c | 1 | 1 | 2 |[2]|
         *  |---+---+---+---+---+---|   |---+---+---+---+---|
         *  | b | 0 | 1 | 2 | 2 | 3 |   | b | 0 | 1 | 2 | 2 |
         *  |---+---+---+---+---+---|   |---+---+---+---+---|
         *  | b | 0 | 0 | 1 | 1 | 3 |   | b | 0 | 0 | 1 | 1 |
         *  |---+---+---+---+---+---|   |---+---+---+---+---|
         *  | a | 0 | 0 | 0 | 1 | 1 |   | d | 0 | 0 | 0 | 1 |
         *  |---+---+---+---+---+---|   +-------------------+
         *  | b | 0 | 0 | 0 | 0 | 1 |
         *  +-----------------------+
         */
        int sSize = s.size();
        vector<vector<int>> dp(sSize, vector<int>(sSize));
        for (int i = sSize - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < sSize; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        retVal = dp[0][sSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"bbbab"}, {"cbbd"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "bbbab"
     *  Output: 4
     *
     *  Input: s = "cbbd"
     *  Output: 2
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.longestPalindromeSubseq(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
