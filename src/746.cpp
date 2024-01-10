#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCostClimbingStairs(vector<int>& cost) {
        int retVal = 0;

        int costSize = cost.size();
        vector<int> dp = {cost[0], cost[1]};
        for (int i = 2; i < costSize; ++i) {
            retVal = cost[i] + min(dp[0], dp[1]);
            dp[0] = dp[1];
            dp[1] = retVal;
        }
        retVal = min(dp[0], dp[1]);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> cost;
    };
    vector<subject> testData{{{10, 15, 20}}, {{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: cost = [10,15,20]
     *  Output: 15
     *
     *  Input: cost = [1,100,1,1,1,100,1,1,100,1]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].cost[j];
        }
        cout << "]\n";

        answer = cSolution.minCostClimbingStairs(testData[i].cost);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
