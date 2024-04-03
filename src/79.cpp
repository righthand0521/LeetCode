#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool dfs(vector<vector<char>>& board, string word, int row, int col, int idx) {
        bool retVal = false;

        // 1 <= word.length <= 15
        int wordSize = word.size();
        if (idx == wordSize) {
            retVal = true;
            return retVal;
        }

        // m == board.length, n = board[i].length, 1 <= m, n <= 6
        int boardSize = board.size();
        int boardColSize = board[0].size();
        if ((row < 0) || (row > (boardSize - 1))) {
            return retVal;
        } else if ((col < 0) || (col > (boardColSize - 1))) {
            return retVal;
        }

        if (board[row][col] != word[idx]) {
            return retVal;
        }

        char tmp = board[row][col];
        board[row][col] = ' ';
        retVal = dfs(board, word, row - 1, col, idx + 1);
        retVal |= dfs(board, word, row + 1, col, idx + 1);
        retVal |= dfs(board, word, row, col - 1, idx + 1);
        retVal |= dfs(board, word, row, col + 1, idx + 1);
        board[row][col] = tmp;

        return retVal;
    }
    bool exist(vector<vector<char>>& board, string word) {
        bool retVal = false;

        // m == board.length, n = board[i].length, 1 <= m, n <= 6
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardColSize; ++col) {
                retVal = dfs(board, word, row, col, 0);
                if (retVal == true) {
                    return retVal;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> board;
        string word;
    };
    vector<subject> testData{{{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED"},
                             {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "SEE"},
                             {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCB"},
                             {{{'A', 'A'}}, "AAA"},
                             {{{'A'}}, "A"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
     *  Output: true
     *
     *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
     *  Output: true
     *
     *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
     *  Output: false
     *
     *  Input: board = [["A","A"]], word = "AAA"
     *  Output: false
     *
     *  Input: board = [["A"]], word = "A"
     *  Output: true
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = [";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].board[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "], word = \"" << testData[i].word << "\"\n";

        answer = cSolution.exist(testData[i].board, testData[i].word);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
