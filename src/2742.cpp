#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int retVal = 0;

        int costSize = cost.size();
        const int INF = 1e9;  // 1 <= cost.length <= 500, 1 <= cost[i] <= 10^6.

        vector<int> dp(costSize + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < costSize; i++) {
            for (int j = costSize; j >= 0; j--) {
                dp[j] = min(dp[j], dp[max(j - time[i] - 1, 0)] + cost[i]);
            }
        }
        retVal = dp[costSize];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> cost;
        vector<int> time;
    };
    vector<subject> testData{{{1, 2, 3, 2}, {1, 2, 3, 2}}, {{2, 3, 4, 2}, {1, 1, 1, 1}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: cost = [1,2,3,2], time = [1,2,3,2]
     *  Output: 3
     *
     *  Input: cost = [2,3,4,2], time = [1,1,1,1]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: cost = [";
        for (long unsigned int j = 0; j < testData[i].cost.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cost[j];
        }
        cout << "], time = [";
        for (long unsigned int j = 0; j < testData[i].time.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].time[j];
        }
        cout << "]\n";

        answer = cSolution.paintWalls(testData[i].cost, testData[i].time);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
