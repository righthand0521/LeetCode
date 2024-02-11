#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int cherryPickup(vector<vector<int>>& grid) {
        int retVal = 0;

        int rowSize = grid.size();
        int colSize = grid[0].size();

        vector<vector<vector<int>>> dp(rowSize, vector<vector<int>>(colSize, vector<int>(colSize, -1)));
        dp[0][0][colSize - 1] = grid[0][0] + grid[0][colSize - 1];
        for (int i = 1; i < rowSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                for (int k = 0; k < colSize; ++k) {
                    int a = -1;
                    if ((i > 0) && (j > 0) && (k > 0)) {
                        a = dp[i - 1][j - 1][k - 1];
                    }

                    int b = -1;
                    if ((i > 0) && (j > 0)) {
                        b = dp[i - 1][j - 1][k];
                    }

                    int c = -1;
                    if ((i > 0) && (j > 0) && (k + 1 < colSize)) {
                        c = dp[i - 1][j - 1][k + 1];
                    }

                    int d = -1;
                    if ((i > 0) && (k > 0)) {
                        d = dp[i - 1][j][k - 1];
                    }

                    int e = -1;
                    if (i > 0) {
                        e = dp[i - 1][j][k];
                    }

                    int f = -1;
                    if ((i > 0) && (k + 1 < colSize)) {
                        f = dp[i - 1][j][k + 1];
                    }

                    int g = -1;
                    if ((i > 0) && (j + 1 < colSize) && (k > 0)) {
                        g = dp[i - 1][j + 1][k - 1];
                    }

                    int h = -1;
                    if ((i > 0) && (j + 1 < colSize)) {
                        h = dp[i - 1][j + 1][k];
                    }

                    int t = -1;
                    if ((i > 0) && (j + 1 < colSize) && (k + 1 < colSize)) {
                        t = dp[i - 1][j + 1][k + 1];
                    }

                    int temp = max(max(max(max(a, b), max(c, d)), max(max(e, f), max(g, h))), t);
                    if (temp == -1) {
                        dp[i][j][k] = -1;
                    } else {
                        if (j == k) {
                            dp[i][j][k] = temp + grid[i][j];
                        } else {
                            dp[i][j][k] = temp + grid[i][j] + grid[i][k];
                        }
                    }
                }
            }
        }

        for (int i = 0; i < colSize; ++i) {
            for (int j = 0; j < colSize; ++j) {
                retVal = max(retVal, dp[rowSize - 1][i][j]);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}}},
                             {{{1, 0, 0, 0, 0, 0, 1},
                               {2, 0, 0, 0, 0, 3, 0},
                               {2, 0, 9, 0, 0, 0, 0},
                               {0, 3, 0, 5, 4, 0, 0},
                               {1, 0, 2, 3, 0, 0, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
     *  Output: 24
     *
     *  Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
     *  Output: 28
     */

    Solution cSolution;
    int answer;
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

        answer = cSolution.cherryPickup(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
