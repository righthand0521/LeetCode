#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int retVal = 0;

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int left = 0;
        int right = row * col;
        while (left <= right) {
            int middle = (left + right) / 2;

            vector<vector<int>> grid(row, vector<int>(col, 1));
            for (int i = 0; i < middle; ++i) {
                grid[cells[i][0] - 1][cells[i][1] - 1] = 0;
            }

            queue<pair<int, int>> bfsQueue;
            for (int i = 0; i < col; ++i) {
                if (grid[0][i]) {
                    bfsQueue.emplace(0, i);
                    grid[0][i] = 0;
                }
            }

            bool found = false;
            while (bfsQueue.empty() == false) {
                auto [x, y] = bfsQueue.front();
                bfsQueue.pop();

                for (int i = 0; i < 4; ++i) {
                    int nextX = x + directions[i][0];
                    int nextY = y + directions[i][1];

                    if ((nextX < 0) || (nextX >= row)) {
                        continue;
                    } else if ((nextY < 0) || (nextY >= col)) {
                        continue;
                    } else if (grid[nextX][nextY] == 0) {
                        continue;
                    }

                    if (nextX == row - 1) {
                        found = true;
                        break;
                    }
                    bfsQueue.emplace(nextX, nextY);
                    grid[nextX][nextY] = 0;
                }
            }

            if (found == true) {
                retVal = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int row;
        int col;
        vector<vector<int>> cells;
    };
    vector<subject> testData{{2, 2, {{1, 1}, {2, 1}, {1, 2}, {2, 2}}},
                             {2, 2, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}},
                             {3, 3, {{1, 2}, {2, 1}, {3, 3}, {2, 2}, {1, 1}, {1, 3}, {2, 3}, {3, 2}, {3, 1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
     *  Output: 2
     *
     *  Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
     *  Output: 1
     *
     *  Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: row = " << testData[i].row << ", col = " << testData[i].col << ", cells = [";
        for (long unsigned int j = 0; j < testData[i].cells.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].cells[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].cells[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.latestDayToCross(testData[i].row, testData[i].col, testData[i].cells);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
