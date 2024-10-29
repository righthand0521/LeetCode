#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxMoves(vector<vector<int>>& grid) {
        int retVal = 0;

        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        for (int x = 0; x < row; ++x) {  // Initialize the first column with moves as 1.
            dp[x][0] = 1;
        }

        // Check all three possible previous cells: (x, y-1), (x-1, y-1), (x+1, y-1)
        for (int y = 1; y < col; ++y) {
            for (int x = 0; x < row; ++x) {
                if ((grid[x][y] > grid[x][y - 1]) && (dp[x][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x][y - 1] + 1);
                }

                if ((x - 1 >= 0) && (grid[x][y] > grid[x - 1][y - 1]) && (dp[x - 1][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x - 1][y - 1] + 1);
                }

                if ((x + 1 < row) && (grid[x][y] > grid[x + 1][y - 1]) && (dp[x + 1][y - 1] > 0)) {
                    dp[x][y] = max(dp[x][y], dp[x + 1][y - 1] + 1);
                }

                retVal = max(retVal, dp[x][y] - 1);
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15}}},
                             {{{3, 2, 4}, {2, 1, 9}, {1, 1, 7}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
     *  Output: 3
     *
     *  Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
     *  Output: 0
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

        answer = cSolution.maxMoves(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
