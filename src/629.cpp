#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int MODULO = (1e9 + 7);

   public:
    int kInversePairs(int n, int k) {
        int retVal = 0;

        vector<int> dp(k + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < (n + 1); ++i) {
            vector<int> dpCurrent(k + 1, 0);
            for (int j = 0; j < (k + 1); ++j) {
                dpCurrent[j] = 0;
                if (j - 1 >= 0) {
                    dpCurrent[j] = dpCurrent[j - 1];
                }
                if (j - i >= 0) {
                    dpCurrent[j] -= dp[j - i];
                    if (dpCurrent[j] < 0) {
                        dpCurrent[j] += MODULO;
                    }
                }
                dpCurrent[j] = (dpCurrent[j] + dp[j]) % MODULO;
            }
            dp = dpCurrent;
        }
        retVal = dp[k];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
    };
    vector<subject> testData{{3, 0}, {3, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, k = 0
     *  Output: 1
     *
     *  Input: n = 3, k = 1
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << "\n";

        answer = cSolution.kInversePairs(testData[i].n, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
