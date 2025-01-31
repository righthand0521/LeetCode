#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    int dfs(vector<vector<int>>& grid, int islandId, int row, int col) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();
        if ((row < 0) || (row >= rowSize) || (col < 0) || (col >= colSize)) {
            return retVal;
        }

        if (grid[row][col] != 1) {
            return retVal;
        }
        grid[row][col] = islandId;

        retVal = 1;
        retVal += dfs(grid, islandId, row + 1, col);
        retVal += dfs(grid, islandId, row - 1, col);
        retVal += dfs(grid, islandId, row, col + 1);
        retVal += dfs(grid, islandId, row, col - 1);

        return retVal;
    }

   public:
    int largestIsland(vector<vector<int>>& grid) {
        int retVal = 1;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // Step 1: Mark all islands and calculate their sizes
        unordered_map<int, int> islandSizes;
        int islandId = 2;
        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (grid[row][col] == 1) {
                    islandSizes[islandId] = dfs(grid, islandId, row, col);
                    ++islandId;
                }
            }
        }

        int islandSizesSize = islandSizes.size();
        if (islandSizes.empty() == true) {  // If there are no islands, return 1
            return retVal;
        } else if (islandSizesSize == 1) {  // If the entire grid is one island, return its size or size + 1
            --islandId;
            retVal = islandSizes[islandId];
            if (islandSizes[islandId] != rowSize * colSize) {
                retVal += 1;
            }
            return retVal;
        }

        // Step 2: Try converting every 0 to 1 and calculate the resulting island size
        for (int row = 0; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                if (grid[row][col] != 0) {
                    continue;
                }

                unordered_set<int> neighboringIslands;
                if ((row + 1 < rowSize) && (grid[row + 1][col] > 1)) {  // Check down
                    neighboringIslands.insert(grid[row + 1][col]);
                }
                if ((row - 1 >= 0) && (grid[row - 1][col] > 1)) {  // Check up
                    neighboringIslands.insert(grid[row - 1][col]);
                }
                if ((col + 1 < colSize) && (grid[row][col + 1] > 1)) {  // Check right
                    neighboringIslands.insert(grid[row][col + 1]);
                }
                if ((col - 1 >= 0) && (grid[row][col - 1] > 1)) {  // Check left
                    neighboringIslands.insert(grid[row][col - 1]);
                }

                // Sum the sizes of all unique neighboring islands
                int currentIslandSize = 1;
                for (int id : neighboringIslands) {
                    currentIslandSize += islandSizes[id];
                }

                retVal = max(retVal, currentIslandSize);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 0}, {0, 1}}}, {{{1, 1}, {1, 0}}}, {{{1, 1}, {1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,0],[0,1]]
     *  Output: 3
     *
     *  Input: grid = [[1,1],[1,0]]
     *  Output: 4
     *
     *  Input: grid = [[1,1],[1,1]]
     *  Output: 4
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

        answer = cSolution.largestIsland(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
