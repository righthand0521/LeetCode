#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int dfs(vector<vector<int>>& matrix, int row, int column, vector<vector<int>>& dp) {
        int retVal = 0;

        if (dp[row][column] != 0) {
            retVal = dp[row][column];
            return retVal;
        }

        int matrixSize = matrix.size();
        int matrixColSize = matrix[0].size();  // 1 <= m, n <= 200
        ++dp[row][column];
        for (auto& direction : directions) {
            int x = row + direction[0];
            int y = column + direction[1];

            if ((x < 0) || (x >= matrixSize)) {
                continue;
            } else if ((y < 0) || (y >= matrixColSize)) {
                continue;
            } else if (matrix[x][y] <= matrix[row][column]) {
                continue;
            }
            dp[row][column] = max(dp[row][column], dfs(matrix, x, y, dp) + 1);
        }
        retVal = dp[row][column];

        return retVal;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int retVal = 0;

        int matrixSize = matrix.size();
        int matrixColSize = matrix[0].size();  // 1 <= m, n <= 200
        if ((matrixSize == 0) || (matrixColSize == 0)) {
            return retVal;
        }

        auto dp = vector<vector<int>>(matrixSize, vector<int>(matrixColSize));
        for (int x = 0; x < matrixSize; ++x) {
            for (int y = 0; y < matrixColSize; ++y) {
                retVal = max(retVal, dfs(matrix, x, y, dp));
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{9, 9, 4}, {6, 6, 8}, {2, 1, 1}}}, {{{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}}, {{{1}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
     *  Output: 4
     *
     *  Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
     *  Output: 4
     *
     *  Input: matrix = [[1]]
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].matrix[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.longestIncreasingPath(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
