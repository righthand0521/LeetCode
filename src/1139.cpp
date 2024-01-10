#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int retVal = 0;

        /* https://leetcode.com/problems/largest-1-bordered-square/solutions/345233/java-c-python-straight-forward/
         *  1. Count the number of consecutive 1s on the top and on the left.
         *  2. From length of edge l = min(m,n) to l = 1, check if the 1-bordered square exist.
         *
         *  Example: grid = [[1,1,1],[1,0,1],[1,1,1]]
         *       +-----------+
         *       | 1 | 1 | 1 |
         *   top | 2 | 0 | 2 |
         *       | 3 | 1 | 3 |
         *       +-----------+
         *         ^   ^   ^
         *       +-----------+    +-----------+
         *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
         *  grid | 1 | 0 | 1 | -> | 1 | 0 | 1 | left
         *       | 1 | 1 | 1 | -> | 1 | 2 | 3 |
         *       +-----------+    +-----------+
         */
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> left(row, vector<int>(col));
        vector<vector<int>> top(row, vector<int>(col));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                left[i][j] = grid[i][j] + (j && grid[i][j] ? left[i][j - 1] : 0);
                top[i][j] = grid[i][j] + (i && grid[i][j] ? top[i - 1][j] : 0);
            }
        }

        for (int idx = min(row, col); idx > 0; --idx) {
            for (int i = 0; i < row - idx + 1; ++i) {
                for (int j = 0; j < col - idx + 1; ++j) {
                    int topHead = top[i + idx - 1][j];
                    int topTail = top[i + idx - 1][j + idx - 1];
                    int leftHead = left[i][j + idx - 1];
                    int leftTail = left[i + idx - 1][j + idx - 1];
                    if (min({topHead, topTail, leftHead, leftTail}) >= idx) {
                        retVal = idx * idx;
                        return retVal;
                    }
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
    vector<subject> testData{{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}}, {{{1, 1, 0, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: 9
     *
     *  Input: grid = [[1,1,0,0]]
     *  Output: 1
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.largest1BorderedSquare(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
