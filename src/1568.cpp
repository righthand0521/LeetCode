#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    const vector<vector<int>> Directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    struct ArticulationPointInfo {
        bool hasArticulationPoint;
        int time;

        ArticulationPointInfo(bool hasArticulationPoint, int time)
            : hasArticulationPoint(hasArticulationPoint), time(time) {}
    };

    void findArticulationPoints(vector<vector<int>>& grid, int row, int col, vector<vector<int>>& discoveryTime,
                                vector<vector<int>>& lowestReachable, vector<vector<int>>& parentCell,
                                ArticulationPointInfo& apInfo) {
        int rowSize = grid.size();
        int colSize = grid[0].size();

        discoveryTime[row][col] = apInfo.time;
        apInfo.time++;
        lowestReachable[row][col] = discoveryTime[row][col];

        int children = 0;
        for (const auto& direction : Directions) {
            int x = row + direction[0];
            int y = col + direction[1];
            if ((x < 0) || (x >= rowSize)) {
                continue;
            } else if ((y < 0) || (y >= colSize)) {
                continue;
            } else if (grid[x][y] != 1) {
                continue;
            }

            if (discoveryTime[x][y] == -1) {
                children++;

                parentCell[x][y] = row * colSize + col;
                findArticulationPoints(grid, x, y, discoveryTime, lowestReachable, parentCell, apInfo);

                // Update lowest reachable time
                lowestReachable[row][col] = min(lowestReachable[row][col], lowestReachable[x][y]);
                // Check for articulation point condition
                if ((lowestReachable[x][y] >= discoveryTime[row][col]) && (parentCell[row][col] != -1)) {
                    apInfo.hasArticulationPoint = true;
                }
            } else if (x * colSize + y != parentCell[row][col]) {
                // Update lowest reachable time for back edge
                lowestReachable[row][col] = min(lowestReachable[row][col], discoveryTime[x][y]);
            }
        }

        // Root of DFS tree is an articulation point if it has more than one child
        if (parentCell[row][col] == -1 && children > 1) {
            apInfo.hasArticulationPoint = true;
        }
    }

   public:
    int minDays(vector<vector<int>>& grid) {
        int retVal = 2;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        // Time when a cell is first discovered
        vector<vector<int>> discoveryTime(rowSize, vector<int>(colSize, -1));
        // Lowest discovery time reachable from the subtree rooted at this cell
        vector<vector<int>> lowestReachable(rowSize, vector<int>(colSize, -1));
        // Parent of each cell in DFS tree
        vector<vector<int>> parentCell(rowSize, vector<int>(colSize, -1));

        ArticulationPointInfo apInfo(false, 0);
        int landCells = 0;
        int islandCount = 0;
        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                if (grid[x][y] != 1) {
                    continue;
                }
                landCells++;

                if (discoveryTime[x][y] != -1) {
                    continue;
                }
                findArticulationPoints(grid, x, y, discoveryTime, lowestReachable, parentCell, apInfo);
                islandCount++;
            }
        }
        if ((islandCount == 0) || (islandCount >= 2)) {
            retVal = 0;  // Already disconnected or no land
        } else if (landCells == 1) {
            retVal = 1;  // Only one land cell
        } else if (apInfo.hasArticulationPoint) {
            retVal = 1;  // An articulation point exists
        }

        return retVal;  // Need to remove any two land cells
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}, {{{1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
     *  Output: 2
     *
     *  Input: grid = [[1,1]]
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

        answer = cSolution.minDays(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
