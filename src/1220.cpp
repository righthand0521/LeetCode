#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
#define MODULO (int)(1e9 + 7)
    int countVowelPermutation(int n) {
        int retVal = 0;

        int numberOfCharacter = 5;  // Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')

        vector<long long> dp(numberOfCharacter, 1);
        vector<long long> nextDp(numberOfCharacter);
        for (int i = 2; i <= n; ++i) {
            nextDp[0] = (dp[1] + dp[2] + dp[4]) % MODULO;
            nextDp[1] = (dp[0] + dp[2]) % MODULO;
            nextDp[2] = (dp[1] + dp[3]) % MODULO;
            nextDp[3] = dp[2];
            nextDp[4] = (dp[2] + dp[3]) % MODULO;

            dp = nextDp;
        }
        retVal = accumulate(dp.begin(), dp.end(), 0LL) % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
    };
    vector<subject> testData{{1}, {2}, {5}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 1
     *  Output: 5
     *
     *  Input: n = 2
     *  Output: 10
     *
     *  Input: n = 5
     *  Output: 68
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: x = " << testData[i].n << "\n";

        answer = cSolution.countVowelPermutation(testData[i].n);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
