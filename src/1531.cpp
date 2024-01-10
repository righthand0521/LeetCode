#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int calc(int x) {
        int retVal = 4;

        if (x == 1) {
            retVal = 1;
        } else if (x < 10) {
            retVal = 2;
        } else if (x < 100) {
            retVal = 3;
        }

        return retVal;
    }
    int getLengthOfOptimalCompression(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        vector<vector<int>> dp(sSize + 1, vector<int>(k + 1, numeric_limits<int>::max() >> 1));
        dp[0][0] = 0;
        for (int x = 1; x <= sSize; ++x) {
            for (int y = 0; y <= k && y <= x; ++y) {
                if (y > 0) {
                    dp[x][y] = dp[x - 1][y - 1];
                }

                int same = 0;
                int diff = 0;
                for (int z = x; (z >= 1 && diff <= y); --z) {
                    if (s[z - 1] == s[x - 1]) {
                        ++same;
                        dp[x][y] = min(dp[x][y], dp[z - 1][y - diff] + calc(same));
                    } else {
                        ++diff;
                    }
                }
            }
        }
        retVal = dp[sSize][k];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"aaabcccd", 2}, {"aabbaa", 2}, {"aaaaaaaaaaa", 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aaabcccd", k = 2
     *  Output: 4
     *
     *  Input: s = "aabbaa", k = 2
     *  Output: 2
     *
     *  Input: s = "aaaaaaaaaaa", k = 0
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int x = 0; x < numberOfTestCase; ++x) {
        cout << "Input: s = \"" << testData[x].s << "\", k = " << testData[x].k << "\n";

        answer = cSolution.getLengthOfOptimalCompression(testData[x].s, testData[x].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
