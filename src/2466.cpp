#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define MODULO (int)(1e9 + 7)
class Solution {
   public:
    int countGoodStrings(int low, int high, int zero, int one) {
        int retVal = 0;

        vector<int> dp(high + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= high; ++i) {
            if (i >= zero) {
                dp[i] += dp[i - zero];
                dp[i] %= MODULO;
            }

            if (i >= one) {
                dp[i] += dp[i - one];
                dp[i] %= MODULO;
            }
        }

        for (int i = low; i <= high; ++i) {
            retVal += dp[i];
            retVal %= MODULO;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int low;
        int high;
        int zero;
        int one;
    };
    vector<subject> testData{{3, 3, 1, 1}, {2, 3, 1, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: low = 3, high = 3, zero = 1, one = 1
     *  Output: 8
     *
     *  Input: low = 2, high = 3, zero = 1, one = 2
     *  Output: 5
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: low = " << testData[i].low << ", high = " << testData[i].high << ", zero = " << testData[i].zero
             << ", one = " << testData[i].one << "\n";

        answer = cSolution.countGoodStrings(testData[i].low, testData[i].high, testData[i].zero, testData[i].one);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
