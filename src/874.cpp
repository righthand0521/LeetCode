#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int hashCoordinates(int x, int y) {
        int retVal = 0;

        static const int HASH_MULTIPLIER = 60001;  // Slightly larger than 2 * max coordinate value
        retVal = x + HASH_MULTIPLIER * y;

        return retVal;
    }

   public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int retVal = 0;

        unordered_set<int> obstacleSet;
        for (auto& obstacle : obstacles) {
            obstacleSet.insert(hashCoordinates(obstacle[0], obstacle[1]));
        }

        vector<int> currentPosition = {0, 0};
        int maxDistanceSquared = 0;
        int currentDirection = 0;
        for (int command : commands) {
            if (command == -1) {
                currentDirection = (currentDirection + 1) % 4;
                continue;
            } else if (command == -2) {
                currentDirection = (currentDirection + 3) % 4;
                continue;
            }

            vector<int> direction = directions[currentDirection];
            for (int step = 0; step < command; step++) {
                int nextX = currentPosition[0] + direction[0];
                int nextY = currentPosition[1] + direction[1];
                if (obstacleSet.count(hashCoordinates(nextX, nextY)) > 0) {
                    break;
                }
                currentPosition[0] = nextX;
                currentPosition[1] = nextY;
            }

            int maxValue = currentPosition[0] * currentPosition[0] + currentPosition[1] * currentPosition[1];
            maxDistanceSquared = max(maxDistanceSquared, maxValue);
        }
        retVal = maxDistanceSquared;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> commands;
        vector<vector<int>> obstacles;
    };
    vector<subject> testData{{{4, -1, 3}, {}}, {{4, -1, 4, -2, 4}, {{2, 4}}}, {{6, -1, -1, 6}, {}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: commands = [4,-1,3], obstacles = []
     *  Output: 25
     *
     *  Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
     *  Output: 65
     *
     *  Input: commands = [6,-1,-1,6], obstacles = []
     *  Output: 36
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: commands = [";
        for (long unsigned int j = 0; j < testData[i].commands.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].commands[j];
        }
        cout << "], obstacles = [";
        for (long unsigned int j = 0; j < testData[i].obstacles.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].obstacles[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].obstacles[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.robotSim(testData[i].commands, testData[i].obstacles);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
