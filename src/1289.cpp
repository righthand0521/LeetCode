#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int retVal = 0;

        int gridSize = grid.size();

        vector<vector<int>> dp(gridSize, vector<int>(gridSize, numeric_limits<int>::max()));
        for (int i = 0; i < gridSize; ++i) {
            dp[0][i] = grid[0][i];
        }

        for (int i = 1; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                for (int k = 0; k < gridSize; ++k) {
                    if (j == k) {
                        continue;
                    }
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                }
            }
        }

        retVal = dp[gridSize - 1][0];
        for (int i = 1; i < gridSize; ++i) {
            retVal = min(retVal, dp[gridSize - 1][i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
    };
    vector<subject> testData{{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}}, {{{7}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: 13
     *
     *  Input: grid = [[7]]
     *  Output: 7
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

        answer = cSolution.minFallingPathSum(testData[i].grid);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
