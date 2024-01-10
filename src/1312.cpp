#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minInsertions(string s) {
        int retVal = 0;

        int sSize = s.size();
        vector<vector<int>> dp(sSize + 1, vector<int>(sSize + 1));

        string sReverse(s.rbegin(), s.rend());
        for (int i = 1; i <= sSize; ++i) {
            for (int j = 1; j <= sSize; ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if (s[i - 1] == sReverse[j - 1]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }
        retVal = sSize - dp[sSize][sSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"zzazz"}, {"mbadm"}, {"leetcode"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "zzazz"
     *  Output: 0
     *
     *  Input: s = "mbadm"
     *  Output: 2
     *
     *  Input: s = "leetcode"
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minInsertions(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
