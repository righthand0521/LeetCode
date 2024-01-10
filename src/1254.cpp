#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool dfs(vector<vector<int>>& grid, int x, int y) {
        bool retVal = false;

        int row = grid.size();
        int col = grid[0].size();

        if ((x < 0) || (x >= row) || (y < 0) || (y >= col)) {
            return retVal;
        }

        if (grid[x][y] == true) {
            retVal = true;
            return retVal;
        }

        grid[x][y] = 1;

        bool up = dfs(grid, x - 1, y);
        bool down = dfs(grid, x + 1, y);
        bool left = dfs(grid, x, y - 1);
        bool right = dfs(grid, x, y + 1);
        retVal = up && down && left && right;

        return retVal;
    }
    int closedIsland(vector<vector<int>>& grid) {
        int retVal = 0;

        int row = grid.size();
        int col = grid[0].size();

        for (int x = 1; x < row; ++x) {
            for (int y = 1; y < col; ++y) {
                if (grid[x][y] != 0) {
                    continue;
                }

                if (dfs(grid, x, y) == true) {
                    ++retVal;
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
    vector<subject> testData{{{{1, 1, 1, 1, 1, 1, 1, 0},
                               {1, 0, 0, 0, 0, 1, 1, 0},
                               {1, 0, 1, 0, 1, 1, 1, 0},
                               {1, 0, 0, 0, 0, 1, 0, 1},
                               {1, 1, 1, 1, 1, 1, 1, 0}}},
                             {{{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}}},
                             {{{1, 1, 1, 1, 1, 1, 1},
                               {1, 0, 0, 0, 0, 0, 1},
                               {1, 0, 1, 1, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 1, 1, 0, 1},
                               {1, 0, 0, 0, 0, 0, 1},
                               {1, 1, 1, 1, 1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,1,1,1,1,1,1,0],
     *                 [1,0,0,0,0,1,1,0],
     *                 [1,0,1,0,1,1,1,0],
     *                 [1,0,0,0,0,1,0,1],
     *                 [1,1,1,1,1,1,1,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,1,0,0],
     *                 [0,1,0,1,0],
     *                 [0,1,1,1,0]]
     *  Output: 1
     *
     *  Input: grid = [[1,1,1,1,1,1,1],
     *                 [1,0,0,0,0,0,1],
     *                 [1,0,1,1,1,0,1],
     *                 [1,0,1,0,1,0,1],
     *                 [1,0,1,1,1,0,1],
     *                 [1,0,0,0,0,0,1],
     *                 [1,1,1,1,1,1,1]]
     *  Output: 2
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

        answer = cSolution.closedIsland(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
