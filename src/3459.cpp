#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    const int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    int dfs(vector<vector<int>>& grid, vector<vector<vector<int>>>& memo, int x, int y, int z, int turn, int target) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        x += directions[z][0];
        y += directions[z][1];
        if ((x < 0) || (x >= gridSize) || (y < 0) || (y >= gridColSize)) {
            return retVal;
        } else if (grid[x][y] != target) {
            return retVal;
        }

        int mask = (z << 1) | turn;
        if (memo[x][y][mask] <= 0) {
            retVal = dfs(grid, memo, x, y, z, turn, 2 - target);
            if (turn == 1) {
                vector<int> maxs = {gridSize - x - 1, y, x, gridColSize - y - 1};
                int next = (z + 1) % 4;
                if (maxs[next] > retVal) {
                    retVal = max(retVal, dfs(grid, memo, x, y, next, 0, 2 - target));
                }
            }
            memo[x][y][mask] = retVal + 1;
        }
        retVal = memo[x][y][mask];

        return retVal;
    };

   public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        vector<vector<vector<int>>> memo(gridSize, vector<vector<int>>(gridColSize, vector<int>(1 << 3, 0)));
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridColSize; ++y) {
                if (grid[x][y] != 1) {
                    continue;
                }

                vector<int> maxs = {gridSize - x, y + 1, x + 1, gridColSize - y};
                for (int z = 0; z < 4; ++z) {
                    if (maxs[z] > retVal) {
                        retVal = max(retVal, dfs(grid, memo, x, y, z, 1, 2) + 1);
                    }
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
    vector<subject> testData{{{{2, 2, 1, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}},
                             {{{2, 2, 2, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}},
                             {{{1, 2, 2, 2, 2}, {2, 2, 2, 2, 0}, {2, 0, 0, 0, 0}, {0, 0, 2, 2, 2}, {2, 0, 0, 2, 0}}},
                             {{{1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
     *  Output: 5
     *
     *  Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
     *  Output: 4
     *
     *  Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
     *  Output: 5
     *
     *  Input: grid = [[1]]
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

        answer = cSolution.lenOfVDiagonal(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
