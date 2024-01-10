#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int fib(int n) {
        int retVal = 0;

        // F(0) = 0, F(1) = 1 and F(n) = F(n - 1) + F(n - 2), for n> 1.
        vector<int> dp;
        dp.emplace_back(0);
        dp.emplace_back(1);
        for (int i = 2; i <= n; ++i) {
            dp.emplace_back(dp[i - 1] + dp[i - 2]);
        }
        retVal = dp[n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {3}, {4}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: 1
     *
     *  Input: n = 3
     *  Output: 2
     *
     *  Input: n = 4
     *  Output: 3
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.fib(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
