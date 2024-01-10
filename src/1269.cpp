#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numWays(int steps, int arrLen) {
        int retVal = 0;

        // dp[step][index] : 0 <= step <= steps, 0 <= index <= arrLen - 1.
        // => dp[step][index] : 0 <= step <= steps, 0 <= index <= min(arrLen - 1, steps).
        // => dpNextStep[index], 0 <= index <= min(arrLen - 1, steps).
        int maxIndex = min(arrLen - 1, steps);
        vector<int> dp(maxIndex + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= steps; ++i) {
            vector<int> dpNextStep(maxIndex + 1, 0);
            for (int j = 0; j <= maxIndex; ++j) {
                dpNextStep[j] = dp[j];
                if (j - 1 >= 0) {
                    dpNextStep[j] = (dpNextStep[j] + dp[j - 1]) % MODULO;
                }
                if (j + 1 <= maxIndex) {
                    dpNextStep[j] = (dpNextStep[j] + dp[j + 1]) % MODULO;
                }
            }
            dp = dpNextStep;
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int steps;
        int arrLen;
    };
    vector<subject> testData{{3, 2}, {2, 4}, {4, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: steps = 3, arrLen = 2
     *  Output: 4
     *
     *  Input: steps = 2, arrLen = 4
     *  Output: 2
     *
     *  Input: steps = 4, arrLen = 2
     *  Output: 8
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: steps = " << testData[i].steps << ", arrLen = " << testData[i].arrLen << "\n";

        answer = cSolution.numWays(testData[i].steps, testData[i].arrLen);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
