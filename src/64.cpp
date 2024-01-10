#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minPathSum(vector<vector<int>>& grid) {
        int retVal = 0;

        // m == grid.length, n == grid[i].length, 1 <= m, n <= 200
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));

        /* Example
         *    | 0 1 2 |  0     1     2
         *  --+-------+------------------
         *  0 | 1 3 1 |   (1) 1+(3) 4+(1)
         *  1 | 1 5 1 | 1+(1) 2+(5) 5+(1)
         *  2 | 4 2 1 | 2+(4) 6+(2) 6+(1)
         */
        dp[0][0] = grid[0][0];
        for (int i = 1; i < col; ++i) {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        for (int i = 1; i < row; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        retVal = dp[row - 1][col - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}}, {{{1, 2, 3}, {4, 5, 6}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
     *  Output: 7
     *
     *  Input: grid = [[1,2,3],[4,5,6]]
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minPathSum(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
