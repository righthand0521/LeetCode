#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numTilings(int n) {
        int retVal = 0;

        vector<vector<long long>> dp(n + 1, vector<long long>(4, 0));
        dp[0][3] = 1;

        for (int i = 1; i <= n; ++i) {
            dp[i][0] = dp[i - 1][3];
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MODULO;
            dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % MODULO;
            dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3]) % MODULO;
        }
        retVal = dp[n][3];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{3}, {1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3
     *  Output: 5
     *
     *  Input: n = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.numTilings(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
