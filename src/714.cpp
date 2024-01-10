#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices, int fee) {
        int retVal = 0;

        int pricesSize = prices.size();
        int dpSell = 0;
        int dpBuy = -(prices[0]);
        for (int i = 1; i < pricesSize; ++i) {
            int tmpSell = max(dpSell, dpBuy + prices[i] - fee);
            int tmpBuy = max(dpBuy, dpSell - prices[i]);
            dpSell = tmpSell;
            dpBuy = tmpBuy;
        }
        retVal = dpSell;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
        int fee;
    };
    vector<subject> testData{{{1, 3, 2, 8, 4, 9}, 2}, {{1, 3, 7, 5, 10, 3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [1,3,2,8,4,9], fee = 2
     *  Output: 8
     *
     *  Input: prices = [1,3,7,5,10,3], fee = 3
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "], fee = " << testData[i].fee << "\n";

        answer = cSolution.maxProfit(testData[i].prices, testData[i].fee);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
