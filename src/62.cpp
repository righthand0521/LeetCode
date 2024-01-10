#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int uniquePaths(int m, int n) {
        int retVal = 0;

        /* Example: 3x7
         *     |  0  1  2  3  4  5  6
         *  ---+----------------------
         *  0  |  1  1  1  1  1  1  1
         *  1  |  1  2  3  4  5  6  7
         *  2  |  1  3  6 10 15 21 28
         */
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; ++i) {
            dp[0][i] = 1;
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        retVal = dp[m - 1][n - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
    };
    vector<subject> testData{{3, 7}, {3, 2}, {5, 10}, {16, 16}, {13, 23}, {51, 9}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 3, n = 7
     *  Output: 28
     *
     *  Input: m = 3, n = 2
     *  Output: 3
     *
     *  Input: m = 5, n = 10
     *  Output: 715
     *
     *  Input: m = 16, n = 16
     *  Output: 155117520
     *
     *  Input: m = 13, n = 23
     *  Output: 548354040
     *
     *  Input: m = 51, n = 9
     *  Output: 1916797311
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << "\n";

        answer = cSolution.uniquePaths(testData[i].m, testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
