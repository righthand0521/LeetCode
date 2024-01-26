#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int MODULO = (1e9 + 7);

   public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        int retVal = 0;

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[startRow][startColumn] = 1;

        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int move = 0; move < maxMove; ++move) {
            vector<vector<int>> dpCurrent(m, vector<int>(n, 0));
            for (int row = 0; row < m; ++row) {
                for (int col = 0; col < n; ++col) {
                    if (dp[row][col] <= 0) {
                        continue;
                    }

                    for (auto& direction : directions) {
                        int nextRow = row + direction[0];
                        int nextCol = col + direction[1];
                        if (((nextRow >= 0) && (nextRow < m)) && ((nextCol >= 0) && (nextCol < n))) {
                            dpCurrent[nextRow][nextCol] = (dpCurrent[nextRow][nextCol] + dp[row][col]) % MODULO;
                        } else {
                            retVal = (retVal + dp[row][col]) % MODULO;
                        }
                    }
                }
            }
            dp = dpCurrent;
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int m;
        int n;
        int maxMove;
        int startRow;
        int startColumn;
    };
    vector<subject> testData{{2, 2, 2, 0, 0}, {1, 3, 3, 0, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
     *  Output: 6
     *
     *  Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: m = " << testData[i].m << ", n = " << testData[i].n << ", maxMove = " << testData[i].maxMove
             << ", startRow = " << testData[i].startRow << ", startColumn = " << testData[i].startColumn << "\n";

        answer = cSolution.findPaths(testData[i].m, testData[i].n, testData[i].maxMove, testData[i].startRow,
                                     testData[i].startColumn);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
