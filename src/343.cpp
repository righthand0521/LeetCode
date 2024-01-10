#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int integerBreak(int n) {
        int retVal = 0;

        if (n <= 3) {
            retVal = n - 1;
            return retVal;
        }

        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            int maximizeProduct = 0;
            for (int j = 1; j < i; ++j) {
                int product1 = j * (i - j);
                int product2 = j * dp[i - j];
                maximizeProduct = max(maximizeProduct, max(product1, product2));
            }
            dp[i] = maximizeProduct;
        }
        retVal = dp[n];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{2}, {10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2
     *  Output: 1
     *
     *  Input: n = 10
     *  Output: 36
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << "\n";

        answer = cSolution.integerBreak(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
