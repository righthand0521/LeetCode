#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> finalPrices(vector<int>& prices) {
        vector<int> retVal = prices;

        stack<int> monotonicStack;
        int pricesSize = prices.size();
        for (int i = 0; i < pricesSize; ++i) {
            // Process items that can be discounted by current price
            while ((monotonicStack.empty() == false) && (prices[monotonicStack.top()] >= prices[i])) {
                // Apply discount to previous item using current price
                retVal[monotonicStack.top()] -= prices[i];
                monotonicStack.pop();
            }

            // Add current index to monotonicStack
            monotonicStack.push(i);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{8, 4, 6, 2, 3}}, {{1, 2, 3, 4, 5}}, {{10, 1, 1, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [8,4,6,2,3]
     *  Output: [4,2,4,2,3]
     *
     *  Input: prices = [1,2,3,4,5]
     *  Output: [1,2,3,4,5]
     *
     *  Input: prices = [10,1,1,6]
     *  Output: [9,0,1,6]
     */

    Solution cSolution;
    vector<int> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "]\n";

        answer = cSolution.finalPrices(testData[i].prices);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
