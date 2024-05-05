#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int retVal = 0;

        int matrixSize = matrix.size();
        int matrixColSize = matrix[0].size();

        // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300
        if ((matrixSize == 0) || (matrixColSize == 0)) {
            return retVal;
        }

        vector<vector<int>> dp(matrixSize, vector<int>(matrixColSize, 0));
        int maxSide = 0;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixColSize; ++j) {
                if (matrix[i][j] != '1') {
                    continue;
                }

                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                }
                maxSide = max(maxSide, dp[i][j]);
            }
        }
        retVal = maxSide * maxSide;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<char>> matrix;
    };
    vector<subject> testData{
        {{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}},
        {{{'0', '1'}, {'1', '0'}}},
        {{{'0'}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
     *  Output: 4
     *
     *  Input: matrix = [["0","1"],["1","0"]]
     *  Output: 1
     *
     *  Input: matrix = [["0"]]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matrix = [";
        for (long unsigned int j = 0; j < testData[i].matrix.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].matrix[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << "\"" << testData[i].matrix[j][k] << "\"";
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maximalSquare(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
