#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int retVal = -1;

        int mazeRow = maze.size();
        int mazeCol = maze[0].size();
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        queue<tuple<int, int, int>> bfsQueue;
        bfsQueue.emplace(entrance[0], entrance[1], 0);
        maze[entrance[0]][entrance[1]] = '+';
        while (bfsQueue.empty() == false) {
            auto [x, y, steps] = bfsQueue.front();
            bfsQueue.pop();
            for (int i = 0; i < 4; ++i) {
                int nextX = x + directions[i][0];
                int nextY = y + directions[i][1];
                if ((nextX < 0) || (nextX >= mazeRow)) {
                    continue;
                } else if ((nextY < 0) || (nextY >= mazeCol)) {
                    continue;
                } else if (maze[nextX][nextY] == '+') {
                    continue;
                }

                if ((nextX == 0) || (nextX == mazeRow - 1) || (nextY == 0) || (nextY == mazeCol - 1)) {
                    retVal = steps + 1;
                    return retVal;
                }
                maze[nextX][nextY] = '+';
                bfsQueue.emplace(nextX, nextY, steps + 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> maze;
        vector<int> entrance;
    };
    vector<subject> testData{{{{'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}}, {1, 2}},
                             {{{'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}}, {1, 0}},
                             {{{'.', '+'}}, {0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
     *  Output: 1
     *
     *  Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
     *  Output: 2
     *
     *  Input: maze = [[".","+"]], entrance = [0,0]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: maze = [";
        for (long unsigned int j = 0; j < testData[i].maze.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].maze[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].maze[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "], entrance = [";
        for (long unsigned int j = 0; j < testData[i].entrance.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].entrance[j];
        }
        cout << "]\n";

        answer = cSolution.nearestExit(testData[i].maze, testData[i].entrance);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
