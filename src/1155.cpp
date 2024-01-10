#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
#define MODULO (int)(1e9 + 7)
    int numRollsToTarget(int n, int k, int target) {
        int retVal = 0;

        /* dp[n][target] = dp[n-1][target-x], x = 1, .., k
         *    0 1 2 3 4 5 6 7
         *  0 1 0 0 0 0 0 0 0
         *  1 0 1 1 1 1 1 1 0
         *  2 0 0 1 2 3 4 5 6
         */
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i < (n + 1); ++i) {
            for (int j = 1; j < (target + 1); ++j) {
                for (int x = 1; x < (k + 1); ++x) {
                    if (j - x >= 0) {
                        long long sum = dp[i][j] + dp[i - 1][j - x];
                        dp[i][j] = sum % MODULO;
                    }
                }
            }
        }
        retVal = dp[n][target];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
        int target;
    };
    vector<subject> testData{{1, 6, 3}, {2, 6, 7}, {30, 30, 500}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1, k = 6, target = 3
     *  Output: 1
     *
     *  Input: n = 2, k = 6, target = 7
     *  Output: 6
     *
     *  Input: n = 30, k = 30, target = 500
     *  Output: 222616187
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].n;
        cout << ", k = " << testData[i].k;
        cout << ", target = " << testData[i].target << "\n";

        answer = cSolution.numRollsToTarget(testData[i].n, testData[i].k, testData[i].target);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
