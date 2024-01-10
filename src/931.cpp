#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int retVal = 0;

        // n == matrix.length == matrix[i].length, 1 <= n <= 100.
        int rowSize = matrix.size();
        int colSize = matrix[0].size();

        vector<vector<int>> dp(rowSize, vector<int>(colSize));
        copy(matrix[0].begin(), matrix[0].end(), dp[0].begin());
        for (int row = 1; row < rowSize; ++row) {
            for (int col = 0; col < colSize; ++col) {
                int middle = dp[row - 1][col];
                if (col > 0) {
                    int left = dp[row - 1][col - 1];
                    middle = min(middle, left);
                }
                if (col < colSize - 1) {
                    int right = dp[row - 1][col + 1];
                    middle = min(middle, right);
                }
                dp[row][col] = middle + matrix[row][col];
            }
        }
        retVal = *min_element(dp[rowSize - 1].begin(), dp[rowSize - 1].end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{2, 1, 3}, {6, 5, 4}, {7, 8, 9}}}, {{{-19, 57}, {-40, -5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
     *  Output: 13
     *
     *  Input: matrix = [[-19,57],[-40,-5]]
     *  Output: -59
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

        answer = cSolution.minFallingPathSum(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
