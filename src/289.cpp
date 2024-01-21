#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void gameOfLife(vector<vector<int>>& board) {
        // m == board.length, n == board[i].length, 1 <= m, n <= 25
        int rowSize = board.size();
        int colSize = board[0].size();

        vector<vector<int>> backup(rowSize, vector<int>(colSize, 0));
        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                backup[x][y] = board[x][y];
            }
        }

        for (int x = 0; x < rowSize; ++x) {
            for (int y = 0; y < colSize; ++y) {
                int live = 0;
                for (int i = -1; i <= 1; ++i) {
                    int neighborX = x + i;
                    if ((neighborX < 0) || (neighborX >= rowSize)) {
                        continue;
                    }

                    for (int j = -1; j <= 1; ++j) {
                        if ((i == 0) && (j == 0)) {
                            continue;
                        }

                        int neighborY = y + j;
                        if ((neighborY < 0) || (neighborY >= colSize)) {
                            continue;
                        }

                        if (backup[neighborX][neighborY] == 1) {
                            ++live;
                        }
                    }
                }

                if (backup[x][y] == 1) {
                    if ((live < 2) || (live > 3)) {
                        board[x][y] = 0;
                    }
                } else if (backup[x][y] == 0) {
                    if (live == 3) {
                        board[x][y] = 1;
                    }
                }
            }
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> board;
    };
    vector<subject> testData{{{{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}}}, {{{1, 1}, {1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
     *  Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
     *
     *  Input: board = [[1,1],[1,0]]
     *  Output: [[1,1],[1,1]]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cSolution.gameOfLife(testData[i].board);

        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
