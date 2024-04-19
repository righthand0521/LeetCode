#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void dfs(vector<vector<char>>& grid, int x, int y) {
        grid[x][y] = '0';

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        if ((x - 1 >= 0) && (grid[x - 1][y] == '1')) {
            dfs(grid, x - 1, y);
        }
        if ((x + 1 < gridSize) && (grid[x + 1][y] == '1')) {
            dfs(grid, x + 1, y);
        }
        if ((y - 1 >= 0) && (grid[x][y - 1] == '1')) {
            dfs(grid, x, y - 1);
        }
        if ((y + 1 < gridColSize) && (grid[x][y + 1] == '1')) {
            dfs(grid, x, y + 1);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridColSize; ++y) {
                if (grid[x][y] == '0') {
                    continue;
                }
                retVal++;
                dfs(grid, x, y);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> grid;
    };
    vector<subject> testData{
        {{{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}}},
        {{{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [
     *    ["1","1","1","1","0"],
     *    ["1","1","0","1","0"],
     *    ["1","1","0","0","0"],
     *    ["0","0","0","0","0"]
     *  ]
     *  Output: 1
     *
     *  Input: grid = [
     *    ["1","1","0","0","0"],
     *    ["1","1","0","0","0"],
     *    ["0","0","1","0","0"],
     *    ["0","0","0","1","1"]
     *  ]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\n  [";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << "\"" << testData[i].grid[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.numIslands(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
