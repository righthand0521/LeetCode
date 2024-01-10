#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int retVal = 0;

        int buy = -(prices[0]);
        int cooldown = 0;
        int sell = 0;
        for (unsigned int i = 1; i < prices.size(); ++i) {
            int dpBuy = max(buy, sell - prices[i]);
            int dpCooldown = buy + prices[i];
            int dpSell = max(cooldown, sell);

            buy = dpBuy;
            cooldown = dpCooldown;
            sell = dpSell;
        }
        retVal = max(cooldown, sell);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{1, 2, 3, 0, 2}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [1,2,3,0,2]
     *  Output: 3
     *
     *  Input: prices = [1]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "]\n";

        answer = cSolution.maxProfit(testData[i].prices);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
