#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int retVal = -1;

        if (grid[0][0] == 1) {
            return retVal;
        }

        int gridSize = grid.size();

        vector<vector<int>> visitDistance(gridSize, vector<int>(gridSize, numeric_limits<int>::max()));
        visitDistance[0][0] = 1;

        vector<vector<int>> direction = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        int directionSize = direction.size();

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(0, 0);
        while (bfsQueue.empty() == false) {
            auto [x, y] = bfsQueue.front();
            bfsQueue.pop();
            if ((x == gridSize - 1) && (y == gridSize - 1)) {
                retVal = visitDistance[x][y];
                break;
            }

            for (int i = 0; i < directionSize; ++i) {
                int row = x + direction[i][0];
                int col = y + direction[i][1];
                if ((row < 0) || (row >= gridSize) || (col < 0) || (col >= gridSize)) {
                    continue;
                }

                if ((grid[row][col] == 1) || (visitDistance[row][col] <= visitDistance[x][y] + 1)) {
                    continue;
                }
                visitDistance[row][col] = visitDistance[x][y] + 1;
                bfsQueue.emplace(row, col);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{
        {{{0, 1}, {1, 0}}}, {{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}}, {{{1, 0, 0}, {1, 1, 0}, {1, 1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1],[1,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
     *  Output: 4
     *
     *  Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.shortestPathBinaryMatrix(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
