#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long getDescentPeriods(vector<int>& prices) {
        long long retVal = 1;  // total number of smooth descending periods, initial value is dp[0]

        int pricesSize = prices.size();
        // total number of smooth descending periods ending with the previous element, initial value is dp[0]
        int prev = 1;
        // traverse the array starting from 1, and update prev and the total res according to the recurrence relation
        for (int i = 1; i < pricesSize; ++i) {
            if (prices[i] == prices[i - 1] - 1) {
                ++prev;
            } else {
                prev = 1;
            }
            retVal += prev;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> prices;
    };
    vector<subject> testData{{{3, 2, 1, 4}}, {{8, 6, 7, 7}}, {{1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: prices = [3,2,1,4]
     *  Output: 7
     *
     *  Input: prices = [8,6,7,7]
     *  Output: 4
     *
     *  Input: prices = [1]
     *  Output: 1
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: prices = [";
        for (long unsigned int j = 0; j < testData[i].prices.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].prices[j];
        }
        cout << "]\n";

        answer = cSolution.getDescentPeriods(testData[i].prices);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
