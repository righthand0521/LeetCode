#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int retVal = 0;

        int pricesSize = prices.size();
        int buy = -(prices[0]);
        int sell = 0;
        for (int i = 1; i < pricesSize; ++i) {
            int dpBuy = max(buy, sell - prices[i]);
            int dpSell = max(sell, buy + prices[i]);

            buy = dpBuy;
            sell = dpSell;
        }
        retVal = sell;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{7, 1, 5, 3, 6, 4}}, {{1, 2, 3, 4, 5}}, {{7, 6, 4, 3, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [7,1,5,3,6,4]
     *  Output: 7
     *
     *  Input: prices = [1,2,3,4,5]
     *  Output: 4
     *
     *  Input: prices = [7,6,4,3,1]
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
