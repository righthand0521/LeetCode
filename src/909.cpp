#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    void getCoordinate(int boardSize, int s, int& row, int& col) {
        row = boardSize - 1 - (s - 1) / boardSize;
        col = (s - 1) % boardSize;

        if (((boardSize % 2 == 1) && (row % 2 == 1)) || ((boardSize % 2 == 0) && (row % 2 == 0))) {
            col = boardSize - 1 - col;
        }
    }
    int snakesAndLadders(vector<vector<int>>& board) {
        int retVal = -1;

        int boardSize = board.size();

        int seenSize = boardSize * boardSize + 1;
        vector<bool> seen(seenSize, false);
        seen[1] = true;

        queue<pair<int, int>> bfsQueue;
        bfsQueue.push({1, 0});
        while (bfsQueue.empty() == false) {
            auto [s, dist] = bfsQueue.front();
            bfsQueue.pop();
            if (s == (seenSize - 1)) {
                retVal = dist;
                return retVal;
            }

            int row, col;
            for (int i = 1; ((s + i < seenSize) && (i <= 6)); i++) {
                getCoordinate(boardSize, s + i, row, col);
                int sfinal = board[row][col];
                if (board[row][col] == -1) {
                    sfinal = s + i;
                }

                if (seen[sfinal] == false) {
                    seen[sfinal] = true;
                    bfsQueue.push({sfinal, dist + 1});
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> board;
    };
    vector<subject> testData{{{{-1, -1, -1, -1, -1, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, 35, -1, -1, 13, -1},
                               {-1, -1, -1, -1, -1, -1},
                               {-1, 15, -1, -1, -1, -1}}},
                             {{{-1, -1}, {-1, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,35,-1,-1,13,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,15,-1,-1,-1,-1]
     *  ]
     *  Output: 4
     *
     *  Input: board = [[-1,-1],[-1,3]]
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
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

        answer = cSolution.snakesAndLadders(testData[i].board);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
