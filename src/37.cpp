#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static const int boardSize = 9;
    vector<pair<int, int>> spaces;
    bool valid;
    int line[boardSize];
    int column[boardSize];
    int block[3][3];

    void flip(int i, int j, int digit) {
        line[i] ^= (1 << digit);
        column[j] ^= (1 << digit);
        block[i / 3][j / 3] ^= (1 << digit);
    }

    void dfs(vector<vector<char>>& board, int pos) {
        int spaceSize = spaces.size();
        if (pos == spaceSize) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & (0x1ff);
        for (; mask && !valid; mask &= (mask - 1)) {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

   public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(line, 0, sizeof(line));
        memset(column, 0, sizeof(column));
        memset(block, 0, sizeof(block));
        valid = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    int digit = board[i][j] - '0' - 1;
                    flip(i, j, digit);
                }
            }
        }

        while (true) {
            int modified = false;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] != '.') {
                        continue;
                    }
                    int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & (0x1ff);
                    if (!(mask & (mask - 1))) {
                        int digit = __builtin_ctz(mask);
                        flip(i, j, digit);
                        board[i][j] = digit + '0' + 1;
                        modified = true;
                    }
                }
            }
            if (!modified) {
                break;
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
            }
        }

        dfs(board, 0);
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> board;
    };
    vector<subject> testData{{{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                               {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                               {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                               {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                               {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                               {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                               {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                               {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                               {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [
     *      ["5","3",".",".","7",".",".",".","."],
     *      ["6",".",".","1","9","5",".",".","."],
     *      [".","9","8",".",".",".",".","6","."],
     *      ["8",".",".",".","6",".",".",".","3"],
     *      ["4",".",".","8",".","3",".",".","1"],
     *      ["7",".",".",".","2",".",".",".","6"],
     *      [".","6",".",".",".",".","2","8","."],
     *      [".",".",".","4","1","9",".",".","5"],
     *      [".",".",".",".","8",".",".","7","9"]
     *  ]
     *  Output: [
     *      ["5","3","4","6","7","8","9","1","2"],
     *      ["6","7","2","1","9","5","3","4","8"],
     *      ["1","9","8","3","4","2","5","6","7"],
     *      ["8","5","9","7","6","1","4","2","3"],
     *      ["4","2","6","8","5","3","7","9","1"],
     *      ["7","1","3","9","2","4","8","5","6"],
     *      ["9","6","1","5","3","7","2","8","4"],
     *      ["2","8","7","4","1","9","6","3","5"],
     *      ["3","4","5","2","8","6","1","7","9"]
     *  ]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [\n";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",\n") << "  [";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "\n]\n";

        cSolution.solveSudoku(testData[i].board);
        cout << "Output: [\n";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",\n") << "  [";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "\n]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
