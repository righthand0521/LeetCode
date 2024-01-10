#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDistance(string word1, string word2) {
        // 72. Edit Distance: https://leetcode.com/problems/edit-distance/
        int retVal = 0;

        int len1 = word1.length();
        int len2 = word2.length();
        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

        /* Example: Input: word1 = "sea", word2 = "eat"
         *      e a t
         *    0 1 2 3
         *  s 1 2 3 4
         *  e 2 1 2 3
         *  a 3 2 1 2
         */
        for (int idx1 = 0; idx1 <= len1; ++idx1) {
            dp[idx1][0] = idx1;
        }
        for (int idx2 = 0; idx2 <= len2; ++idx2) {
            dp[0][idx2] = idx2;
        }
        for (int idx1 = 1; idx1 <= len1; ++idx1) {
            for (int idx2 = 1; idx2 <= len2; ++idx2) {
                if (word1[idx1 - 1] == word2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1];
                } else {
                    dp[idx1][idx2] = 1 + min(dp[idx1][idx2 - 1], dp[idx1 - 1][idx2]);
                }
            }
        }
        retVal = dp[len1][len2];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string word1;
        string word2;
    };
    vector<subject> testData{{"sea", "eat"}, {"leetcode", "etco"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: word1 = "sea", word2 = "eat"
     *  Output: 2
     *
     *  Input: word1 = "leetcode", word2 = "etco"
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: word1 = \"" << testData[i].word1 << "\", word2 = \"" << testData[i].word2 << "\"\n";

        answer = cSolution.minDistance(testData[i].word1, testData[i].word2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
