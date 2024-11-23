#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        vector<vector<char>> retVal;

        int boxSize = box.size();
        int boxColSize = box[0].size();
        retVal.resize(boxColSize, vector<char>(boxSize, '.'));

        // Apply gravity to let stones fall to the lowest possible empty cell in each column
        for (int i = 0; i < boxSize; i++) {
            int lowestRowWithEmptyCell = boxColSize - 1;

            // Process each cell in row 'i' in reversed order
            for (int j = boxColSize - 1; j >= 0; j--) {
                // Found a stone - let it fall to the lowest empty cell
                if (box[i][j] == '#') {
                    // Place it in the correct position in the rotated grid
                    retVal[lowestRowWithEmptyCell][boxSize - i - 1] = '#';
                    // (Optional - already initialized to '.') retVal[j][boxSize - i - 1] = '.';
                    lowestRowWithEmptyCell--;
                }

                // Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
                if (box[i][j] == '*') {
                    // Place the obstacle in the correct position in the rotated grid
                    retVal[j][boxSize - i - 1] = '*';
                    lowestRowWithEmptyCell = j - 1;
                }
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> box;
    };
    vector<subject> testData{{{{'#'}, {'.'}, {'#'}}},
                             {{{{'#'}, {'.'}, {'*'}, {'.'}}, {{'#'}, {'#'}, {'*'}, {'.'}}}},
                             {{{{'#'}, {'#'}, {'*'}, {'.'}, {'*'}, {'.'}},
                               {{'#'}, {'#'}, {'#'}, {'*'}, {'.'}, {'.'}},
                               {{'#'}, {'#'}, {'#'}, {'.'}, {'#'}, {'.'}}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: box = [["#",".","#"]]
     *  Output: [["."],["#"],["#"]]
     *
     *  Input: box = [["#",".","*","."],["#","#","*","."]]
     *  Output: [["#","."],["#","#"],["*","*"],[".","."]]
     *
     *  Input: box = [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]]
     *  Output: [[".","#","#"],[".","#","#"],["#","#","*"],["#","*","."],["#",".","*"],["#",".","."]]
     */

    Solution cSolution;
    vector<vector<char>> answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: box = [";
        for (long unsigned int j = 0; j < testData[i].box.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].box[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].box[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.rotateTheBox(testData[i].box);
        cout << "Output: [";
        for (long unsigned int j = 0; j < answer.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < answer[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << answer[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
