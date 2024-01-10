#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double soupServings(int n) {
        double retVal = 1;

        /* Answers within 10 ^ -5 of the actual answer will be accepted.
         *  E(A) = (4 + 3 + 2 + 1) x 0.25 = 2.5
         *  E(B) = (0 + 1 + 2 + 3) x 0.25 = 1.5
         *
         *  n = 4475, p ≈ 0.999990211307
         *  n = 4476, p ≈ 0.999990468596
         *
         *  n ≥ 179 x 25
         */
        n = ceil((double)n / 25);
        if (n >= 179) {
            return retVal;
        }

        // https://leetcode.cn/problems/soup-servings/solutions/1982919/by-joneli-ts7a/
        vector<vector<double>> dp(n + 1, vector<double>(n + 1));
        dp[0][0] = 0.5;
        for (int i = 1; i <= n; i++) {
            dp[0][i] = 1.0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                double sum = 0;
                sum += dp[max(0, i - 4)][j];
                sum += dp[max(0, i - 3)][max(0, j - 1)];
                sum += dp[max(0, i - 2)][max(0, j - 2)];
                sum += dp[max(0, i - 1)][max(0, j - 3)];
                dp[i][j] = sum / 4.0;
            }
        }
        retVal = dp[n][n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{50}, {100}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 50
     *  Output: 0.62500
     *
     *  Input: n = 100
     *  Output: 0.71875
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.soupServings(testData[i].n);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
