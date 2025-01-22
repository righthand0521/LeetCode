#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        vector<vector<int>> retVal;

        int isWaterRows = isWater.size();
        int isWaterCols = isWater[0].size();
        vector<vector<int>> cellHeights(isWaterRows, vector<int>(isWaterCols, -1));

        queue<pair<int, int>> bfsQueue;
        for (int x = 0; x < isWaterRows; x++) {
            for (int y = 0; y < isWaterCols; y++) {
                if (isWater[x][y] == 1) {
                    bfsQueue.push({x, y});
                    cellHeights[x][y] = 0;
                }
            }
        }

        vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int heightOfNextLayer = 1;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; i++) {
                pair<int, int> currentCell = bfsQueue.front();
                bfsQueue.pop();

                for (int dir = 0; dir < 4; ++dir) {
                    int x = currentCell.first + direction[dir][0];
                    int y = currentCell.second + direction[dir][1];
                    if ((x < 0) || (x >= isWaterRows) || (y < 0) || (y >= isWaterCols)) {
                        continue;
                    } else if (cellHeights[x][y] != -1) {
                        continue;
                    }
                    cellHeights[x][y] = heightOfNextLayer;
                    bfsQueue.push({x, y});
                }
            }
            heightOfNextLayer++;
        }
        retVal = cellHeights;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> isWater;
    };
    vector<subject> testData{{{{0, 1}, {0, 0}}}, {{{0, 0, 1}, {1, 0, 0}, {0, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: isWater = [[0,1],[0,0]]
     *  Output: [[1,0],[2,1]]
     *
     *  Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
     *  Output: [[1,1,0],[0,1,1],[1,2,2]]
     */

    Solution cSolution;
    vector<vector<int>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: isWater = [";
        for (long unsigned int j = 0; j < testData[i].isWater.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].isWater[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].isWater[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.highestPeak(testData[i].isWater);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
