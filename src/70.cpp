#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int climbStairs(int n) {
        int retVal = 0;

        /* Climbing Stairs
         *  C[1] = 1; 1
         *  C[2] = 2; 1+1, 2
         *  C[n] = F[n-1] + F[n-2], n>=3.
         */
#define CLIMBSTAIRS_1 (1)
#define CLIMBSTAIRS_2 (2)
#define CLIMBSTAIRS (3)
        vector<int> dp(CLIMBSTAIRS);
        dp[0] = 0;
        dp[1] = CLIMBSTAIRS_1;
        dp[2] = CLIMBSTAIRS_2;

        retVal = dp[n % CLIMBSTAIRS];
        for (int i = CLIMBSTAIRS; i <= n; ++i) {
            dp[i % CLIMBSTAIRS] = dp[(i - 1) % CLIMBSTAIRS] + dp[(i - 2) % CLIMBSTAIRS];
            retVal = dp[i % CLIMBSTAIRS];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {3}, {4}, {5}, {6}, {1}, {45}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: 2
     *
     *  Input: n = 3
     *  Output: 3
     *
     *  Input: n = 4
     *  Output: 5
     *
     *  Input: n = 5
     *  Output: 8
     *
     *  Input: n = 6
     *  Output: 13
     *
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 45
     *  Output: 1836311903
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.climbStairs(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
