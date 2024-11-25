#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int retVal = 0;

        // Direction map for zero's possible moves in a 1D representation of the 2x3 board
        vector<vector<int>> directions = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
        string target = "123450";

        string startState;
        int boardSize = board.size();
        int boardColSize = board[0].size();
        for (int i = 0; i < boardSize; i++) {  // Convert the 2D board into a string representation
            for (int j = 0; j < boardColSize; j++) {
                startState += to_string(board[i][j]);
            }
        }
        queue<string> bfsQueue;
        bfsQueue.push(startState);
        unordered_set<string> visited;  // To store visited states
        visited.insert(startState);

        // BFS to find the minimum number of moves
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            while (bfsQueueSize-- > 0) {
                string currentState = bfsQueue.front();
                bfsQueue.pop();
                if (currentState == target) {  // Check if we reached the target solved state
                    return retVal;
                }

                int zeroPos = currentState.find('0');
                for (int newPos : directions[zeroPos]) {
                    string nextState = currentState;
                    swap(nextState[zeroPos], nextState[newPos]);
                    if (visited.count(nextState)) {  // Skip if this state has been visited
                        continue;
                    }

                    // Mark the new state as visited and add it to the queue
                    bfsQueue.push(nextState);
                    visited.insert(nextState);
                }
            }
            retVal++;
        }
        retVal = -1;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> board;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 0, 5}}}, {{{1, 2, 3}, {5, 4, 0}}}, {{{4, 1, 2}, {5, 0, 3}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: board = [[1,2,3],[4,0,5]]
     *  Output: 1
     *
     *  Input: board = [[1,2,3],[5,4,0]]
     *  Output: -1
     *
     *  Input: board = [[4,1,2],[5,0,3]]
     *  Output: 5
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

        answer = cSolution.slidingPuzzle(testData[i].board);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
