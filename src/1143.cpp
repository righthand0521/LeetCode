#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        int retVal = 0;

        // 712. Minimum ASCII Delete Sum for Two Strings:
        // https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
        int s1Size = text1.length();
        int s2Size = text2.length();

        /* https://pic.leetcode-cn.com/1617411822-KhEKGw-image.png
         *      0 1 2 3 4 5
         *      - a b c d e
         *  0 - 0 0 0 0 0 0
         *  1 a 0 1 1 1 1 1
         *  2 c 0 1 1 2 2 2
         *  3 e 0 1 1 2 2 3
         */
        vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1));
        int idx1, idx2;
        for (idx1 = 1; idx1 <= s1Size; ++idx1) {
            for (idx2 = 1; idx2 <= s2Size; ++idx2) {
                if (text1[idx1 - 1] == text2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + 1;
                } else {
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
                }
            }
        }
        retVal = dp[s1Size][s2Size];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string text1;
        string text2;
    };
    vector<subject> testData{{"abcde", "ace"}, {"abc", "abc"}, {"abc", "def"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: text1 = "abcde", text2 = "ace"
     *  Output: 3
     *
     *  Input: text1 = "abc", text2 = "abc"
     *  Output: 3
     *
     *  Input: text1 = "abc", text2 = "def"
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: text1 = \"" << testData[i].text1 << "\", text2 = \"" << testData[i].text2 << "\"\n";

        answer = cSolution.longestCommonSubsequence(testData[i].text1, testData[i].text2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
