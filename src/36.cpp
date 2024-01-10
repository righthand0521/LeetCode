#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool retVal = false;

        int boardSize = board.size();
        int boardColSize = board[0].size();

        vector<vector<int>> rowHashTable(boardColSize, vector<int>(boardSize, 0));
        vector<vector<int>> colHashTable(boardColSize, vector<int>(boardSize, 0));
        vector<vector<int>> boxHashTable(boardColSize, vector<int>(boardSize, 0));
        for (int x = 0; x < boardSize; ++x) {
            for (int y = 0; y < boardColSize; ++y) {
                if (board[x][y] == '.') {
                    continue;
                }

                int digits = board[x][y] - '0' - 1;
                int boxIndex = (x / 3) * 3 + y / 3;
                if ((rowHashTable[x][digits]) || (colHashTable[y][digits]) || (boxHashTable[boxIndex][digits])) {
                    return retVal;
                }
                rowHashTable[x][digits] = 1;
                colHashTable[y][digits] = 1;
                boxHashTable[boxIndex][digits] = 1;
            }
        }
        retVal = true;

        return retVal;
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
                               {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}},
                             {{{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
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
     *  Input: board =
     *  [["5","3",".",".","7",".",".",".","."]
     *  ,["6",".",".","1","9","5",".",".","."]
     *  ,[".","9","8",".",".",".",".","6","."]
     *  ,["8",".",".",".","6",".",".",".","3"]
     *  ,["4",".",".","8",".","3",".",".","1"]
     *  ,["7",".",".",".","2",".",".",".","6"]
     *  ,[".","6",".",".",".",".","2","8","."]
     *  ,[".",".",".","4","1","9",".",".","5"]
     *  ,[".",".",".",".","8",".",".","7","9"]]
     *  Output: true
     *
     *  Input: board =
     *  [["8","3",".",".","7",".",".",".","."]
     *  ,["6",".",".","1","9","5",".",".","."]
     *  ,[".","9","8",".",".",".",".","6","."]
     *  ,["8",".",".",".","6",".",".",".","3"]
     *  ,["4",".",".","8",".","3",".",".","1"]
     *  ,["7",".",".",".","2",".",".",".","6"]
     *  ,[".","6",".",".",".",".","2","8","."]
     *  ,[".",".",".","4","1","9",".",".","5"]
     *  ,[".",".",".",".","8",".",".","7","9"]]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: board = \n[";
        for (long unsigned int j = 0; j < testData[i].board.size(); ++j) {
            cout << ((j == 0) ? "" : ",\n") << "[";
            for (long unsigned int k = 0; k < testData[i].board[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].board[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.isValidSudoku(testData[i].board);
        cout << "Output: " << ((answer == true) ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
