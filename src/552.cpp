#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int checkRecord(int n) {
        int retVal = 0;

        vector<vector<vector<int>>> dp = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        // Base case: there is 1 string of length 0 with zero 'A' and zero 'L'.
        dp[0][0][0] = 1;

        // Iterate on smaller sub-problems and use the current smaller sub-problem
        // to generate results for bigger sub-problems.
        for (int len = 0; len < n; ++len) {
            for (int totalAbsences = 0; totalAbsences <= 1; ++totalAbsences) {
                for (int consecutiveLates = 0; consecutiveLates <= 2; ++consecutiveLates) {
                    // Store the count when 'P' is chosen.
                    dp[len + 1][totalAbsences][0] =
                        (dp[len + 1][totalAbsences][0] + dp[len][totalAbsences][consecutiveLates]) % MODULO;

                    // Store the count when 'A' is chosen.
                    if (totalAbsences < 1) {
                        dp[len + 1][totalAbsences + 1][0] =
                            (dp[len + 1][totalAbsences + 1][0] + dp[len][totalAbsences][consecutiveLates]) % MODULO;
                    }

                    // Store the count when 'L' is chosen.
                    if (consecutiveLates < 2) {
                        dp[len + 1][totalAbsences][consecutiveLates + 1] =
                            (dp[len + 1][totalAbsences][consecutiveLates + 1] +
                             dp[len][totalAbsences][consecutiveLates]) %
                            MODULO;
                    }
                }
            }
        }

        // Sum up the counts for all combinations of length 'n' with different absent and late counts.
        for (int totalAbsences = 0; totalAbsences <= 1; ++totalAbsences) {
            for (int consecutiveLates = 0; consecutiveLates <= 2; ++consecutiveLates) {
                retVal = (retVal + dp[n][totalAbsences][consecutiveLates]) % MODULO;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {1}, {10101}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: 8
     *
     *  Input: n = 1
     *  Output: 3
     *
     *  Input: n = 10101
     *  Output: 183236316
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.checkRecord(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
