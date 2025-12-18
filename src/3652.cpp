#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        long long retVal = 0;

        int pricesSize = prices.size();

        vector<long long> profitSum(pricesSize + 1);
        vector<long long> priceSum(pricesSize + 1);
        for (int i = 0; i < pricesSize; i++) {
            profitSum[i + 1] = profitSum[i] + prices[i] * strategy[i];
            priceSum[i + 1] = priceSum[i] + prices[i];
        }
        retVal = profitSum[pricesSize];

        for (int i = k - 1; i < pricesSize; i++) {
            long long leftProfit = profitSum[i - k + 1];
            long long rightProfit = profitSum[pricesSize] - profitSum[i + 1];
            long long changeProfit = priceSum[i + 1] - priceSum[i - k / 2 + 1];
            retVal = max(retVal, leftProfit + changeProfit + rightProfit);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
        vector<int> strategy;
        int k;
    };
    vector<subject> testData{{{4, 2, 8}, {-1, 0, 1}, 2}, {{5, 4, 3}, {1, 1, 0}, 2}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [4,2,8], strategy = [-1,0,1], k = 2
     *  Output: 10
     *
     *  Input: prices = [5,4,3], strategy = [1,1,0], k = 2
     *  Output: 9
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "], strategy = [";
        for (long unsigned int j = 0; j < testData[i].strategy.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].strategy[j];
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxProfit(testData[i].prices, testData[i].strategy, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
