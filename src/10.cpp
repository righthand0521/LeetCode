#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool matches(string s, string p, int i, int j) {
        bool retVal = false;

        if (i == 0) {
            retVal = false;
        } else if (p[j - 1] == '.') {
            retVal = true;
        } else {
            retVal = (s[i - 1] == p[j - 1]);
        }

        return retVal;
    };

   public:
    bool isMatch(string s, string p) {
        bool retVal = false;

        int sSize = s.size();
        int pSize = p.size();
        vector<vector<int>> dp(sSize + 1, vector<int>(pSize + 1));
        dp[0][0] = true;
        for (int i = 0; i <= sSize; ++i) {
            for (int j = 1; j <= pSize; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] |= dp[i][j - 2];
                    if (matches(s, p, i, j - 1) == true) {
                        dp[i][j] |= dp[i - 1][j];
                    }
                } else {
                    if (matches(s, p, i, j) == true) {
                        dp[i][j] |= dp[i - 1][j - 1];
                    }
                }
            }
        }
        retVal = dp[sSize][pSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        string p;
    };
    vector<subject> testData{{"aa", "a"}, {"aa", "a*"}, {"ab", ".*"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aa", p = "a"
     *  Output: false
     *
     *  Input: s = "aa", p = "a*"
     *  Output: true
     *
     *  Input: s = "ab", p = ".*"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", p = \"" << testData[i].p << "\"\n";

        answer = cSolution.isMatch(testData[i].s, testData[i].p);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
