#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int backtrack(vector<vector<int>>& grid, int gridSize, int gridColSize, int row, int col) {
        int retVal = 0;

        // Base case: this cell is not in the matrix or has no gold
        if ((row < 0) || (col < 0) || (row == gridSize) || (col == gridColSize) || (grid[row][col] == 0)) {
            return retVal;
        }

        // Mark the cell as visited and save the value
        int originalVal = grid[row][col];
        grid[row][col] = 0;

        // Backtrack in each of the four directions
        for (int i = 0; i < 4; ++i) {
            int x = row + direction[i][0];
            int y = col + direction[i][1];
            retVal = max(retVal, backtrack(grid, gridSize, gridColSize, x, y));
        }

        // Set the cell back to its original value
        grid[row][col] = originalVal;

        retVal += originalVal;

        return retVal;
    }

   public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();

        // Search for the path with the maximum gold starting from each cell
        for (int row = 0; row < gridSize; ++row) {
            for (int col = 0; col < gridColSize; ++col) {
                retVal = max(retVal, backtrack(grid, gridSize, gridColSize, row, col));
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 6, 0}, {5, 8, 7}, {0, 9, 0}}},
                             {{{1, 0, 7}, {2, 0, 6}, {3, 4, 5}, {0, 3, 0}, {9, 0, 20}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
     *  Output: 24
     *
     *  Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
     *  Output: 28
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

        answer = cSolution.getMaximumGold(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
