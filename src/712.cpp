#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumDeleteSum(string s1, string s2) {
        int retVal = 0;

        // 1143. Longest Common Subsequence: https://leetcode.com/problems/longest-common-subsequence/
        int s1Size = s1.length();
        int s2Size = s2.length();
        int idx1, idx2;

        int sum = 0;
        for (idx1 = 0; idx1 < s1Size; ++idx1) {
            sum += s1[idx1];
        }
        for (idx2 = 0; idx2 < s2Size; ++idx2) {
            sum += s2[idx2];
        }

        vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1));
        for (idx1 = 1; idx1 <= s1Size; ++idx1) {
            for (idx2 = 1; idx2 <= s2Size; ++idx2) {
                if (s1[idx1 - 1] == s2[idx2 - 1]) {
                    dp[idx1][idx2] = dp[idx1 - 1][idx2 - 1] + s1[idx1 - 1];
                } else {
                    dp[idx1][idx2] = max(dp[idx1 - 1][idx2], dp[idx1][idx2 - 1]);
                }
            }
        }
        retVal = sum - (2 * dp[s1Size][s2Size]);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s1;
        string s2;
    };
    vector<subject> testData{{"sea", "eat"}, {"delete", "leet"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "sea", s2 = "eat"
     *  Output: 231
     *
     *  Input: s1 = "delete", s2 = "leet"
     *  Output: 403
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s1 = \"" << testData[i].s1 << "\", s2 = \"" << testData[i].s2 << "\"\n";

        answer = cSolution.minimumDeleteSum(testData[i].s1, testData[i].s2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
