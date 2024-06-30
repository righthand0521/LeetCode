#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

   public:
    void solve(vector<vector<char>>& board) {
        int boardSize = board.size();
        if (boardSize == 0) {
            return;
        }
        int boardColSize = board[0].size();

        queue<pair<int, int>> bfsQueue;
        for (int i = 0; i < boardSize; i++) {
            if (board[i][0] == 'O') {
                bfsQueue.emplace(i, 0);
                board[i][0] = 'A';
            }
            if (board[i][boardColSize - 1] == 'O') {
                bfsQueue.emplace(i, boardColSize - 1);
                board[i][boardColSize - 1] = 'A';
            }
        }
        for (int i = 1; i < boardColSize - 1; i++) {
            if (board[0][i] == 'O') {
                bfsQueue.emplace(0, i);
                board[0][i] = 'A';
            }
            if (board[boardSize - 1][i] == 'O') {
                bfsQueue.emplace(boardSize - 1, i);
                board[boardSize - 1][i] = 'A';
            }
        }

        while (bfsQueue.empty() == false) {
            int row = bfsQueue.front().first;
            int col = bfsQueue.front().second;
            bfsQueue.pop();
            for (int i = 0; i < 4; i++) {
                int x = row + dx[i];
                int y = col + dy[i];
                if ((x < 0) || (y < 0) || (x >= boardSize) || (y >= boardColSize) || (board[x][y] != 'O')) {
                    continue;
                }
                bfsQueue.emplace(x, y);
                board[x][y] = 'A';
            }
        }

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardColSize; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> board;
    };
    vector<subject> testData{{{{'X', 'X', 'X', 'X'}, {'X', '0', '0', 'X'}, {'X', 'X', '0', 'X'}, {'X', '0', 'X', 'X'}}},
                             {{{'X'}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
     *  Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
     *
     *  Input: board = [["X"]]
     *  Output: [["X"]]
     */

    Solution cSolution;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].board[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cSolution.solve(testData[i].board);
        cout << "Output: [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].board[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
