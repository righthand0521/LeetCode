#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    int MODULO = (1e9 + 7);

   public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        int retVal = 0;

        vector<long> dp(forget, 0);
        dp[0] = 1;
        long share = 0;
        for (int i = 1; i < n; ++i) {
            share = (share + dp[(i - delay + forget) % forget] - dp[i % forget] + MODULO) % MODULO;
            dp[i % forget] = share;
        }
        retVal = accumulate(dp.begin(), dp.end(), 0L) % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int delay;
        int forget;
    };
    vector<subject> testData{{6, 2, 4}, {4, 1, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 6, delay = 2, forget = 4
     *  Output: 5
     *
     *  Input: n = 4, delay = 1, forget = 3
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", delay = " << testData[i].delay
             << ", forget = " << testData[i].forget << "\n";

        answer = cSolution.peopleAwareOfSecret(testData[i].n, testData[i].delay, testData[i].forget);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
