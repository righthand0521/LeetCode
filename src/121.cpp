#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int retVal = 0;

        int buy = prices[0];
        int sell = prices[0];
        for (auto price : prices) {
            if (buy > price) {
                buy = price;
                sell = price;
                continue;
            }

            if (sell < price) {
                sell = price;
            }

            retVal = max(retVal, sell - buy);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{7, 1, 5, 3, 6, 4}}, {{7, 6, 4, 3, 1}}, {{2, 4, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [7,1,5,3,6,4]
     *  Output: 5
     *
     *  Input: prices = [7,6,4,3,1]
     *  Output: 0
     *
     *  Input: prices = [2, 4, 1]
     *  Output: 2
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
