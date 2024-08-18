#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int nthUglyNumber(int n) {
        int retVal = 0;

        vector<int> dp(n + 1, 0);
        dp[1] = 1;

        int idx2 = 1;
        int idx3 = 1;
        int idx5 = 1;
        for (int i = 2; i <= n; ++i) {
            int num2 = dp[idx2] * 2;
            int num3 = dp[idx3] * 3;
            int num5 = dp[idx5] * 5;
            dp[i] = min(num2, min(num3, num5));

            if (dp[i] == num2) {
                idx2++;
            }
            if (dp[i] == num3) {
                idx3++;
            }
            if (dp[i] == num5) {
                idx5++;
            }
        }
        retVal = dp[n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{10}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10
     *  Output: 12
     *
     *  Input: n = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.nthUglyNumber(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
