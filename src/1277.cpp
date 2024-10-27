#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSquares(vector<vector<int>>& matrix) {
        int retVal = 0;

        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        for (int x = 0; x < row; ++x) {
            for (int y = 0; y < col; ++y) {
                if (matrix[x][y] == 0) {
                    continue;
                }
                dp[x + 1][y + 1] = min({dp[x][y + 1], dp[x + 1][y], dp[x][y]}) + 1;
                retVal += dp[x + 1][y + 1];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> matrix;
    };
    vector<subject> testData{{{{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}}}, {{{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matrix = [[0,1,1,1], [1,1,1,1], [0,1,1,1]]
     *  Output: 15
     *
     *  Input: matrix = [[1,0,1], [1,1,0], [1,1,0]]
     *  Output: 7
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

        answer = cSolution.countSquares(testData[i].matrix);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
