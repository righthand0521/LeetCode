#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSquares(int n) {
        int retVal = 0;

        if (n <= 0) {
            return retVal;
        }

        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; (j * j) <= i; ++j) {
                dp[i] = min(dp[i], dp[i - (j * j)] + 1);
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
    vector<subject> testData{{12}, {13}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 12
     *  Output: 3
     *
     *  Input: n = 13
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.numSquares(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
