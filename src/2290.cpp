#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    bool isValid(int gridSize, int gridColSize, int row, int col) {
        bool retVal = true;

        if (row < 0) {
            retVal = false;
        } else if (row >= gridSize) {
            retVal = false;
        } else if (col < 0) {
            retVal = false;
        } else if (col >= gridColSize) {
            retVal = false;
        }

        return retVal;
    }

   public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        vector<vector<int>> minObstacles(gridSize, vector<int>(gridColSize, numeric_limits<int>::max()));
        minObstacles[0][0] = grid[0][0];

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({minObstacles[0][0], 0, 0});
        while (pq.empty() == false) {
            vector<int> current = pq.top();
            pq.pop();
            int obstacles = current[0];
            int row = current[1];
            int col = current[2];
            if ((row == gridSize - 1) && (col == gridColSize - 1)) {
                retVal = obstacles;
                return retVal;
            }

            for (vector<int>& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                if (isValid(gridSize, gridColSize, newRow, newCol) == false) {
                    continue;
                }

                int newObstacles = obstacles + grid[newRow][newCol];
                if (newObstacles < minObstacles[newRow][newCol]) {
                    minObstacles[newRow][newCol] = newObstacles;
                    pq.push({newObstacles, newRow, newCol});
                }
            }
        }
        retVal = minObstacles[gridSize - 1][gridColSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1, 1}, {1, 1, 0}, {1, 1, 0}}},
                             {{{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
     *  Output: 0
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

        answer = cSolution.minimumObstacles(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
