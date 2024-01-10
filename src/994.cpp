#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int orangesRotting(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();
        vector<vector<int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        queue<vector<int>> bfsQueue;
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                if (grid[i][j] == 2) {
                    vector<int> value(3, 0);
                    value[0] = i;
                    value[1] = j;
                    value[2] = 0;
                    bfsQueue.push(value);
                }
            }
        }

        while (bfsQueue.empty() == false) {
            auto popValue = bfsQueue.front();
            int x = popValue[0];
            int y = popValue[1];
            retVal = popValue[2];
            bfsQueue.pop();

            for (int i = 0; i < 4; ++i) {
                int row = x + direction[i][0];
                int col = y + direction[i][1];
                if ((0 <= row) && (row < rowSize) && (0 <= col) && (col < colSize)) {
                    if (grid[row][col] == 1) {
                        grid[row][col] = 2;

                        vector<int> value(3, 0);
                        value[0] = row;
                        value[1] = col;
                        value[2] = retVal + 1;
                        bfsQueue.push(value);
                    }
                }
            }
        }

        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                if (grid[i][j] == 1) {
                    retVal = -1;
                    break;
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
    vector<subject> testData{{{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}}, {{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}}, {{{0, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
     *  Output: 4
     *
     *  Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
     *  Output: -1
     *
     *  Input: grid = [[0,2]]
     *  Output: 0
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

        answer = cSolution.orangesRotting(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
