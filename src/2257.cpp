#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void markUnguarded(int row, int col, vector<vector<int>>& grid) {
        int gridSize = grid.size();
        for (int x = row - 1; x >= 0; x--) {
            if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
                break;
            }
            grid[x][col] = 1;
        }
        for (int x = row + 1; x < gridSize; x++) {
            if ((grid[x][col] == 3) || (grid[x][col] == 2)) {
                break;
            }
            grid[x][col] = 1;
        }

        int gridColSize = grid[row].size();
        for (int y = col - 1; y >= 0; y--) {
            if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
                break;
            }
            grid[row][y] = 1;
        }
        for (int y = col + 1; y < gridColSize; y++) {
            if ((grid[row][y] == 3) || (grid[row][y] == 2)) {
                break;
            }
            grid[row][y] = 1;
        }
    }
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        int retVal = 0;

        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (const auto& guard : guards) {
            grid[guard[0]][guard[1]] = 2;
        }
        for (const auto& wall : walls) {
            grid[wall[0]][wall[1]] = 3;
        }

        for (const auto& guard : guards) {
            markUnguarded(guard[0], guard[1], grid);
        }

        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (cell == 0) {
                    retVal++;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
        vector<vector<int>> guards;
        vector<vector<int>> walls;
    };
    vector<subject> testData{{4, 6, {{0, 0}, {1, 1}, {2, 3}}, {{0, 1}, {2, 2}, {1, 4}}},
                             {3, 3, {{1, 1}}, {{0, 1}, {1, 0}, {2, 1}, {1, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
     *  Output: 7
     *
     *  Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << ", guards = [";
        for (long unsigned int j = 0; j < testData[i].guards.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].guards[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].guards[j][k];
            }
            cout << "]";
        }
        cout << "], walls = [";
        for (long unsigned int j = 0; j < testData[i].walls.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].walls[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].walls[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.countUnguarded(testData[i].m, testData[i].n, testData[i].guards, testData[i].walls);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
