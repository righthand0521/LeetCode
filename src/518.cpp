#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int change(int amount, vector<int>& coins) {
        int retVal = 0;

        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        int coinsSize = coins.size();
        for (int i = 0; i < coinsSize; ++i) {
            for (int j = coins[i]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i]];
            }
        }
        retVal = dp[amount];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int amount;
        vector<int> coins;
    };
    vector<subject> testData{{5, {1, 2, 5}}, {3, {2}}, {10, {10}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: amount = 5, coins = [1,2,5]
     *  Output: 4
     *
     *  Input: amount = 3, coins = [2]
     *  Output: 0
     *
     *  Input: amount = 10, coins = [10]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: amount = " << testData[i].amount << ", coins = [";
        for (long unsigned int j = 0; j < testData[i].coins.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].coins[j];
        }
        cout << "]\n";

        answer = cSolution.change(testData[i].amount, testData[i].coins);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
