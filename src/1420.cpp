#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numOfArrays(int n, int m, int k) {
        int retVal = 0;

        long long dp[m + 1][k + 1];
        memset(dp, 0, sizeof(dp));
        long long prefix[m + 1][k + 1];
        memset(prefix, 0, sizeof(prefix));
        long long prevDp[m + 1][k + 1];
        memset(prevDp, 0, sizeof(prevDp));
        long long prevPrefix[m + 1][k + 1];
        memset(prevPrefix, 0, sizeof(prevPrefix));

        for (int num = 1; num <= m; num++) {
            dp[num][1] = 1;
        }
        for (int i = 1; i <= n; i++) {
            if (i > 1) {
                memset(dp, 0, sizeof(dp));
            }

            memset(prefix, 0, sizeof(prefix));
            for (int maxNum = 1; maxNum <= m; maxNum++) {
                for (int cost = 1; cost <= k; cost++) {
                    long long answer = (maxNum * prevDp[maxNum][cost]) % MODULO;
                    answer = (answer + prevPrefix[maxNum - 1][cost - 1]) % MODULO;

                    dp[maxNum][cost] += answer;
                    dp[maxNum][cost] %= MODULO;

                    prefix[maxNum][cost] = (prefix[maxNum - 1][cost] + dp[maxNum][cost]);
                    prefix[maxNum][cost] %= MODULO;
                }
            }

            for (int maxNum = 0; maxNum <= m; maxNum++) {
                for (int cost = 0; cost <= k; cost++) {
                    prevDp[maxNum][cost] = dp[maxNum][cost];
                    prevPrefix[maxNum][cost] = prefix[maxNum][cost];
                }
            }
        }
        retVal = prefix[m][k];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int m;
        int k;
    };
    vector<subject> testData{{2, 3, 1}, {5, 2, 3}, {9, 1, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, m = 3, k = 1
     *  Output: 6
     *
     *  Input: n = 5, m = 2, k = 3
     *  Output: 0
     *
     *  Input: n = 9, m = 1, k = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", m = " << testData[i].m << ", k = " << testData[i].k << "\n";

        answer = cSolution.numOfArrays(testData[i].n, testData[i].m, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
