#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int row, int col) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({row, col});
        visited[row][col] = true;
        const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (bfsQueue.empty() == false) {
            int x = bfsQueue.front().first;
            int y = bfsQueue.front().second;
            bfsQueue.pop();
            retVal += grid[x][y];

            for (auto& direction : directions) {
                int nextX = x + direction[0];
                int nextY = y + direction[1];
                if ((nextX < 0) || (nextX >= rowSize) || (nextY < 0) || (nextY >= colSize)) {
                    continue;
                }

                if ((grid[nextX][nextY] != 0) && (visited[nextX][nextY] == false)) {
                    bfsQueue.push({nextX, nextY});
                    visited[nextX][nextY] = true;
                }
            }
        }

        return retVal;
    }

   public:
    int findMaxFish(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<vector<bool>> visited(rowSize, vector<bool>(colSize));
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                if ((grid[i][j] != 0) && (visited[i][j] == false)) {
                    retVal = max(retVal, bfs(grid, visited, i, j));
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 2, 1, 0}, {4, 0, 0, 3}, {1, 0, 0, 4}, {0, 3, 2, 0}}},
                             {{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
     *  Output: 7
     *
     *  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.findMaxFish(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
