#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(int k, vector<int>& prices) {
        int retVal = 0;

        vector<int> buy(k + 1);
        vector<int> sell(k + 1);
        for (int i = 0; i <= k; ++i) {
            buy[i] = -(prices[0]);
            sell[i] = 0;
        }

        int pricesSize = prices.size();
        for (int i = 1; i < pricesSize; ++i) {
            vector<int> dpBuy(k + 1);
            vector<int> dpSell(k + 1);
            for (int j = 1; j <= k; ++j) {
                dpBuy[j] = max(buy[j], sell[j - 1] - prices[i]);
                dpSell[j] = max(sell[j], buy[j] + prices[i]);
            }

            for (int j = 0; j <= k; ++j) {
                buy[j] = dpBuy[j];
                sell[j] = dpSell[j];
            }
        }
        retVal = sell[k];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int k;
        vector<int> prices;
    };
    vector<subject> testData{{2, {2, 4, 1}}, {2, {3, 2, 6, 5, 0, 3}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: k = 2, prices = [2,4,1]
     *  Output: 2
     *
     *  Input: k = 2, prices = [3,2,6,5,0,3]
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: k = " << testData[i].k << ", prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "]\n";

        answer = cSolution.maxProfit(testData[i].k, testData[i].prices);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
