#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maximumProfit(vector<int>& prices, int k) {
        long long retVal = 0;

        int pricesSize = prices.size();

        vector<vector<long long>> dp(k + 1, vector<long long>(3));
        for (int j = 1; j <= k; j++) {
            dp[j][1] = -prices[0];
            dp[j][2] = prices[0];
        }

        for (int i = 1; i < pricesSize; i++) {
            for (int j = k; j > 0; j--) {
                dp[j][0] = max(dp[j][0], max(dp[j][1] + prices[i], dp[j][2] - prices[i]));
                dp[j][1] = max(dp[j][1], dp[j - 1][0] - prices[i]);
                dp[j][2] = max(dp[j][2], dp[j - 1][0] + prices[i]);
            }
        }
        retVal = dp[k][0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
        int k;
    };
    vector<subject> testData{{{1, 7, 9, 8, 2}, 2}, {{12, 16, 19, 19, 8, 1, 19, 13, 9}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [1,7,9,8,2], k = 2
     *  Output: 14
     *
     *  Input: prices = [12,16,19,19,8,1,19,13,9], k = 3
     *  Output: 36
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maximumProfit(testData[i].prices, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
