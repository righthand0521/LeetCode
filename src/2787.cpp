#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;  // Since the answer can be very large, return it modulo 10^9 + 7.

   public:
    int numberOfWays(int n, int x) {
        int retVal = 0;

        vector<long long> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            long long val = pow(i, x);
            if (val > n) {
                break;
            }

            for (int j = n; j >= val; j--) {
                dp[j] = (dp[j] + dp[j - val]) % MODULO;
            }
        }
        retVal = dp[n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int x;
    };
    vector<subject> testData{{10, 2}, {4, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10, x = 2
     *  Output: 1
     *
     *  Input: n = 4, x = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", x = " << testData[i].x << "\n";

        answer = cSolution.numberOfWays(testData[i].n, testData[i].x);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
