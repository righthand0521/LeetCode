#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    const vector<vector<int>> Directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void floodFill(vector<vector<int>>& expandedGrid, int x, int y) {
        int expandedGridSize = expandedGrid.size();
        expandedGrid[x][y] = 1;

        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({x, y});
        while (bfsQueue.empty() == false) {
            auto [currentRow, currentCol] = bfsQueue.front();
            bfsQueue.pop();

            for (auto& direction : Directions) {
                int row = direction[0] + currentRow;
                int col = direction[1] + currentCol;
                if ((row < 0) || (row >= expandedGridSize)) {
                    continue;
                } else if ((col < 0) || (col >= expandedGridSize)) {
                    continue;
                } else if (expandedGrid[row][col] != 0) {
                    continue;
                }

                expandedGrid[row][col] = 1;
                bfsQueue.push({row, col});
            }
        }
    }

   public:
    int regionsBySlashes(vector<string>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        int expandedGridSize = gridSize * 3;

        vector<vector<int>> expandedGrid(expandedGridSize, vector<int>(expandedGridSize, 0));
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridSize; ++y) {
                int row = x * 3;
                int col = y * 3;
                if (grid[x][y] == '\\') {
                    expandedGrid[row][col] = 1;
                    expandedGrid[row + 1][col + 1] = 1;
                    expandedGrid[row + 2][col + 2] = 1;
                } else if (grid[x][y] == '/') {
                    expandedGrid[row][col + 2] = 1;
                    expandedGrid[row + 1][col + 1] = 1;
                    expandedGrid[row + 2][col] = 1;
                }
            }
        }

        for (int x = 0; x < expandedGridSize; ++x) {
            for (int y = 0; y < expandedGridSize; ++y) {
                if (expandedGrid[x][y] == 0) {
                    floodFill(expandedGrid, x, y);
                    retVal++;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> grid;
    };
    vector<subject> testData{{{" /", "/ "}}, {{" /", "  "}}, {{"/\\", "\\/"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [" /","/ "]
     *  Output: 2
     *
     *  Input: grid = [" /","  "]
     *  Output: 1
     *
     *  Input: grid = ["/\\","\\/"]
     *  Output: 5
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].grid[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.regionsBySlashes(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
