#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int shortestBridge(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();
        vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        //
        queue<pair<int, int>> bfsQueue1;
        queue<pair<int, int>> bfsQueue2;
        int island1x, island1y;
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridSize; ++y) {
                if (grid[x][y] == 1) {
                    island1x = x;
                    island1y = y;
                    break;
                }
            }
        }
        bfsQueue1.emplace(island1x, island1y);
        bfsQueue2.emplace(island1x, island1y);
        grid[island1x][island1y] = 2;

        //
        while (bfsQueue1.empty() == false) {
            auto [x, y] = bfsQueue1.front();
            bfsQueue1.pop();

            for (int i = 0; i < 4; ++i) {
                int row = x + direction[i][0];
                int col = y + direction[i][1];
                if ((0 <= row) && (row < gridSize) && (0 <= col) && (col < gridSize)) {
                    if (grid[row][col] == 1) {
                        bfsQueue1.emplace(row, col);
                        bfsQueue2.emplace(row, col);
                        grid[row][col] = 2;
                    }
                }
            }
        }

        //
        while (bfsQueue2.empty() == false) {
            int bfsQueue2Size = bfsQueue2.size();
            for (int times = 0; times < bfsQueue2Size; ++times) {
                auto [x, y] = bfsQueue2.front();
                bfsQueue2.pop();

                for (int i = 0; i < 4; ++i) {
                    int row = x + direction[i][0];
                    int col = y + direction[i][1];
                    if ((0 <= row) && (row < gridSize) && (0 <= col) && (col < gridSize)) {
                        if (grid[row][col] == 1) {
                            return retVal;
                        } else if (grid[row][col] == 0) {
                            bfsQueue2.emplace(row, col);
                            grid[row][col] = -1;
                        }
                    }
                }
            }
            ++retVal;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{0, 1}, {1, 0}}},
                             {{{0, 1, 0}, {0, 0, 0}, {0, 0, 1}}},
                             {{{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[0,1],[1,0]]
     *  Output: 1
     *
     *  Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
     *  Output: 2
     *
     *  Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
     *  Output: 1
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

        answer = cSolution.shortestBridge(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
