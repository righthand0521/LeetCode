#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int coinChange(vector<int>& coins, int amount) {
        int retVal = -1;

        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        int coinsSize = coins.size();
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coinsSize; ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        if (dp[amount] <= amount) {
            retVal = dp[amount];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> coins;
        int amount;
    };
    vector<subject> testData{{{1, 2, 5}, 11}, {{2}, 3}, {{1}, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: coins = [1,2,5], amount = 11
     *  Output: 3
     *
     *  Input: coins = [2], amount = 3
     *  Output: -1
     *
     *  Input: coins = [1], amount = 0
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: coins = [";
        for (long unsigned int j = 0; j < testData[i].coins.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].coins[j];
        }
        cout << "], amount = " << testData[i].amount << "\n ";

        answer = cSolution.coinChange(testData[i].coins, testData[i].amount);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
