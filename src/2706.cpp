#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int buyChoco(vector<int>& prices, int money) {
        int retVal = money;

        sort(prices.begin(), prices.end());
        int leftover = money - (prices[0] + prices[1]);
        if (leftover >= 0) {
            retVal = leftover;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
        int money;
    };
    vector<subject> testData{{{1, 2, 2}, 3}, {{3, 2, 3}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [1,2,2], money = 3
     *  Output: 0
     *
     *  Input: prices = [3,2,3], money = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "], money = " << testData[i].money << "\n";

        answer = cSolution.buyChoco(testData[i].prices, testData[i].money);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
