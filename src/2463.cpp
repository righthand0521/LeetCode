#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        long long retVal = 0;

        // Sort robots and factories by position
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Flatten factory positions according to their capacities
        vector<int> factoryPositions;
        for (auto& f : factory) {
            for (int i = 0; i < f[1]; i++) {
                factoryPositions.push_back(f[0]);
            }
        }

        int robotSize = robot.size();
        int factoryPositionsSize = factoryPositions.size();
        vector<vector<long long>> dp(robotSize + 1, vector<long long>(factoryPositionsSize + 1, 0));

        // Initialize base cases
        for (int i = 0; i < robotSize; i++) {
            dp[i][factoryPositionsSize] = 1e12;  // No factories left
        }

        // Fill DP table bottom-up
        for (int i = robotSize - 1; i >= 0; i--) {
            for (int j = factoryPositionsSize - 1; j >= 0; j--) {
                // Option 1: Assign current robot to current factory
                long long assign = abs(robot[i] - factoryPositions[j]) + dp[i + 1][j + 1];

                // Option 2: Skip current factory for the current robot
                long long skip = dp[i][j + 1];

                dp[i][j] = min(assign, skip);  // Take the minimum option
            }
        }
        retVal = dp[0][0];  // Minimum distance starting from first robot and factory

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> robot;
        vector<vector<int>> factory;
    };
    vector<subject> testData{{{0, 4, 6}, {{2, 2}, {6, 2}}}, {{1, -1}, {{-2, 1}, {2, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: robot = [0,4,6], factory = [[2,2],[6,2]]
     *  Output: 4
     *
     *  Input: robot = [1,-1], factory = [[-2,1],[2,1]]
     *  Output: 2
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: robot = [";
        for (long unsigned int j = 0; j < testData[i].robot.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].robot[j];
        }
        cout << "], factory = [";
        for (long unsigned int j = 0; j < testData[i].factory.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].factory[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].factory[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumTotalDistance(testData[i].robot, testData[i].factory);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
