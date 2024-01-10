#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
#define STUCK (-1)
    bool isOutBound(int gridRowSize, int gridColumnSize, int row, int column) {
        if ((row >= gridRowSize) || (row < 0)) {
            return false;
        } else if ((column >= gridColumnSize) || (column < 0)) {
            return false;
        }

        return true;
    }
    int dfs(vector<vector<int>>& grid, int gridRowSize, int gridColumnSize, int row, int column) {
        // at the bottom
        if (row == gridRowSize) {
            return column;
        }

        // check outbound or not
        if (isOutBound(gridRowSize, gridColumnSize, row, column) == false) {
            return STUCK;
        }

        if (grid[row][column] == 1) {  // redirects the ball to the right spans
            if (isOutBound(gridRowSize, gridColumnSize, row, (column + 1)) == false) {
                return STUCK;
            } else if (grid[row][(column + 1)] != 1) {
                return STUCK;
            }

            return dfs(grid, gridRowSize, gridColumnSize, (row + 1), (column + 1));
        } else if (grid[row][column] == -1) {  // redirects the ball to the left spans
            if (isOutBound(gridRowSize, gridColumnSize, row, (column - 1)) == false) {
                return STUCK;
            } else if (grid[row][(column - 1)] != -1) {
                return STUCK;
            }

            return dfs(grid, gridRowSize, gridColumnSize, (row + 1), (column - 1));
        }

        return STUCK;
    }

    vector<int> findBall(vector<vector<int>>& grid) {
        int gridRowSize = grid.size();
        int gridColumnSize = grid[0].size();
        vector<int> retVal(gridColumnSize, STUCK);

        // only 1 column
        if (gridColumnSize == 1) {
            return retVal;
        }

        // Depth-First Search by Recursive
        for (int i = 0; i < gridColumnSize; ++i) {
            retVal[i] = dfs(grid, gridRowSize, gridColumnSize, 0, i);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{
        {{{1, 1, 1, -1, -1}, {1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1}, {1, 1, 1, 1, -1}, {-1, -1, -1, -1, -1}}},
        {{{-1}}},
        {{{1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}, {1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    vector<int> answer;
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

        answer = cSolution.findBall(testData[i].grid);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << answer[j];
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
