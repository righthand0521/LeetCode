#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int dfs(vector<vector<int>>& grid, vector<vector<int>>& dp, int i, int j) {
        int retVal = 1;

        if (dp[i][j] != 0) {
            retVal = dp[i][j];
            return retVal;
        }

        int gridSize = grid.size();
        int gridColSize = grid[0].size();  // 1 <= m, n <= 1000
        for (auto& direction : directions) {
            int prev_i = i + direction[0];
            int prev_j = j + direction[1];

            if ((prev_i < 0) || (prev_i >= gridSize)) {
                continue;
            } else if ((prev_j < 0) || (prev_j >= gridColSize)) {
                continue;
            } else if (grid[prev_i][prev_j] >= grid[i][j]) {
                continue;
            }
            retVal = (retVal + dfs(grid, dp, prev_i, prev_j)) % MODULO;
        }
        dp[i][j] = retVal;

        return retVal;
    }
    int countPaths(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();  // 1 <= m, n <= 1000
        vector<vector<int>> dp(gridSize, vector<int>(gridColSize, 0));
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridColSize; ++j) {
                retVal = (retVal + dfs(grid, dp, i, j)) % MODULO;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 1}, {3, 4}}}, {{{1}, {2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,1],[3,4]]
     *  Output: 8
     *
     *  Input: grid = [[1],[2]]
     *  Output: 3
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

        answer = cSolution.countPaths(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
