#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   private:
    int minimumSum2(vector<vector<int>> &grid, int u, int d, int l, int r) {
        int retVal = 0;

        int minRow = grid.size();
        int maxRow = 0;
        int minCol = grid[0].size();
        int maxCol = 0;
        for (int i = u; i <= d; i++) {
            for (int j = l; j <= r; j++) {
                if (grid[i][j] == 1) {
                    minRow = min(minRow, i);
                    minCol = min(minCol, j);
                    maxRow = max(maxRow, i);
                    maxCol = max(maxCol, j);
                }
            }
        }
        retVal = numeric_limits<int>::max() / 3;
        if (minRow <= maxRow) {
            retVal = (maxRow - minRow + 1) * (maxCol - minCol + 1);
        }

        return retVal;
    }
    int solve(vector<vector<int>> &grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        int x, y, z;
        retVal = gridSize * gridColSize;
        for (int i = 0; i + 1 < gridSize; i++) {
            for (int j = 0; j + 1 < gridColSize; j++) {
                x = minimumSum2(grid, 0, i, 0, gridColSize - 1);
                y = minimumSum2(grid, i + 1, gridSize - 1, 0, j);
                z = minimumSum2(grid, i + 1, gridSize - 1, j + 1, gridColSize - 1);
                retVal = min(retVal, x + y + z);

                x = minimumSum2(grid, 0, i, 0, j);
                y = minimumSum2(grid, 0, i, j + 1, gridColSize - 1);
                z = minimumSum2(grid, i + 1, gridSize - 1, 0, gridColSize - 1);
                retVal = min(retVal, x + y + z);
            }
        }

        for (int i = 0; i + 2 < gridSize; i++) {
            for (int j = i + 1; j + 1 < gridSize; j++) {
                x = minimumSum2(grid, 0, i, 0, gridColSize - 1);
                y = minimumSum2(grid, i + 1, j, 0, gridColSize - 1);
                z = minimumSum2(grid, j + 1, gridSize - 1, 0, gridColSize - 1);
                retVal = min(retVal, x + y + z);
            }
        }

        return retVal;
    }
    vector<vector<int>> rotate(vector<vector<int>> &grid) {
        vector<vector<int>> retVal;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        retVal.resize(gridColSize, vector<int>(gridSize));
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridColSize; j++) {
                retVal[gridColSize - j - 1][i] = grid[i][j];
            }
        }

        return retVal;
    }

   public:
    int minimumSum(vector<vector<int>> &grid) {
        int retVal = 0;

        auto rotateGrid = rotate(grid);
        retVal = min(solve(grid), solve(rotateGrid));

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 0, 1}, {1, 1, 1}}}, {{{1, 0, 1, 0}, {0, 1, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,0,1],[1,1,1]]
     *  Output: 5
     *
     *  Input: grid = [[1,0,1,0],[0,1,0,1]]
     *  Output: 5
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

        answer = cSolution.minimumSum(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
