#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    bool dfs(int x, int y, vector<vector<int>>& grid1, vector<vector<int>>& grid2, vector<vector<bool>>& visited) {
        bool retVal = true;

        if (grid1[x][y] != 1) {
            retVal = false;
        }

        int rowSize = grid2.size();
        int colSize = grid2[0].size();
        for (auto& direction : directions) {
            int nextX = x + direction[0];
            int nextY = y + direction[1];
            if ((nextX < 0) || (nextX >= rowSize)) {
                continue;
            } else if ((nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            if (visited[nextX][nextY] == true) {
                continue;
            } else if (grid2[nextX][nextY] != 1) {
                continue;
            }

            visited[nextX][nextY] = true;
            bool nextCellIsPartOfSubIsland = dfs(nextX, nextY, grid1, grid2, visited);
            retVal = retVal && nextCellIsPartOfSubIsland;
        }

        return retVal;
    }

   public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int retVal = 0;

        int rowSize = grid2.size();
        int colSize = grid2[0].size();
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));
        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                if (visited[x][y] == true) {
                    continue;
                } else if (grid2[x][y] != 1) {
                    continue;
                }

                visited[x][y] = true;
                if (dfs(x, y, grid1, grid2, visited)) {
                    retVal += 1;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid1;
        vector<vector<int>> grid2;
    };
    vector<subject> testData{{{{1, 1, 1, 0, 0}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 1, 1}},
                              {{1, 1, 1, 0, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 0, 1, 0}}},
                             {{{1, 0, 1, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}},
                              {{0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 1, 0, 1, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]],
     *  grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
     *  Output: 3
     *
     *  Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]],
     *  grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid1 = [";
        for (long unsigned int j = 0; j < testData[i].grid1.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid1[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid1[j][k];
            }
            cout << "]";
        }
        cout << "], grid2 = [";
        for (long unsigned int j = 0; j < testData[i].grid2.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid2[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid2[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countSubIslands(testData[i].grid1, testData[i].grid2);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
