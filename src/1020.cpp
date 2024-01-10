#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(vector<vector<int>>& grid, int x, int y) {
        int row = grid.size();
        int col = grid[0].size();

        if ((x < 0) || (x >= row) || (y < 0) || (y >= col)) {
            return;
        }

        if (grid[x][y] == 0) {
            return;
        }

        grid[x][y] = 0;
        dfs(grid, x - 1, y);
        dfs(grid, x + 1, y);
        dfs(grid, x, y - 1);
        dfs(grid, x, y + 1);
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int retVal = 0;

        int row = grid.size();
        int col = grid[0].size();
        for (int x = 0; x < row; ++x) {
            for (int y = 0; y < col; ++y) {
                if ((x != 0) && (x != row - 1) && (y != 0) && (y != col - 1)) {
                    continue;
                }

                if (grid[x][y] != 1) {
                    continue;
                }

                dfs(grid, x, y);
            }
        }

        for (int x = 0; x < row; ++x) {
            for (int y = 0; y < col; ++y) {
                retVal += grid[x][y];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
                             {{{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
     *  Output: 3
     *
     *  Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
     *  Output: 0
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

        answer = cSolution.numEnclaves(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
