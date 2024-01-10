#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isInterleave(string s1, string s2, string s3) {
        bool retVal = false;

        int s1Size = s1.size();
        int s2Size = s2.size();
        int s3Size = s3.size();
        if (s1Size + s2Size != s3Size) {
            return retVal;
        }

        /* dp[i,j]: s1[0:i] + s2[0:j] = s3[0:(i+j)]
         * dp[i,j] = (dp[i-1,j] and s1[0:i-1] = s3[0:i+j-1]) or (dp[i,j-1] and s2[0:j-1] = s3[0:i+j-1]), dp[0,0] = true.
         */
        vector<vector<int>> dp(s1Size + 1, vector<int>(s2Size + 1, false));
        dp[0][0] = true;
        for (int s1Idx = 0; s1Idx <= s1Size; ++s1Idx) {
            for (int s2Idx = 0; s2Idx <= s2Size; ++s2Idx) {
                int s3Idx = s1Idx + s2Idx - 1;
                if (s1Idx > 0) {
                    dp[s1Idx][s2Idx] |= (dp[s1Idx - 1][s2Idx] && s1[s1Idx - 1] == s3[s3Idx]);
                }
                if (s2Idx > 0) {
                    dp[s1Idx][s2Idx] |= (dp[s1Idx][s2Idx - 1] && s2[s2Idx - 1] == s3[s3Idx]);
                }
            }
        }
        retVal = dp[s1Size][s2Size];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s1;
        string s2;
        string s3;
    };
    vector<subject> testData{{"aabcc", "dbbca", "aadbbcbcac"}, {"aabcc", "dbbca", "aadbbbaccc"}, {"", "", ""}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
     *  Output: true
     *
     *  Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
     *  Output: false
     *
     *  Input: s1 = "", s2 = "", s3 = ""
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s1 << "\"";
        cout << ", s2 = \"" << testData[i].s2 << "\"";
        cout << ", s3 = \"" << testData[i].s3 << "\"\n";

        answer = cSolution.isInterleave(testData[i].s1, testData[i].s2, testData[i].s3);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
