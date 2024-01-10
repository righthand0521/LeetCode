#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int retVal = 0;

        int pricesSize = prices.size();
        int buy1 = -(prices[0]);
        int sell1 = 0;
        int buy2 = -(prices[0]);
        int sell2 = 0;
        for (int i = 1; i < pricesSize; ++i) {
            int dpBuy1 = max(buy1, -(prices[i]));
            int dpSell1 = max(sell1, buy1 + prices[i]);
            int dpBuy2 = max(buy2, sell1 - prices[i]);
            int dpSell2 = max(sell2, buy2 + prices[i]);

            buy1 = dpBuy1;
            sell1 = dpSell1;
            buy2 = dpBuy2;
            sell2 = dpSell2;
        }
        retVal = sell2;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{3, 3, 5, 0, 0, 3, 1, 4}}, {{1, 2, 3, 4, 5}}, {{7, 6, 4, 3, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [3,3,5,0,0,3,1,4]
     *  Output: 6
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
