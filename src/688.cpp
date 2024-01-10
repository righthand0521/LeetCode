#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double knightProbability(int n, int k, int row, int column) {
        double retVal = 0;

        vector<vector<int>> directions = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>>(n, vector<double>(n)));
        for (int step = 0; step <= k; step++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (step == 0) {
                        dp[step][i][j] = 1;
                        continue;
                    }

                    for (auto& direction : directions) {
                        int nextRow = i + direction[0];
                        int nextCol = j + direction[1];
                        if (((nextRow >= 0) && (nextRow < n)) && ((nextCol >= 0) && (nextCol < n))) {
                            dp[step][i][j] += dp[step - 1][nextRow][nextCol] / 8;
                        }
                    }
                }
            }
        }
        retVal = dp[k][row][column];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
        int row;
        int column;
    };
    vector<subject> testData{{3, 2, 0, 0}, {1, 0, 0, 0}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 3, k = 2, row = 0, column = 0
     *  Output: 0.06250
     *
     *  Input: n = 1, k = 0, row = 0, column = 0
     *  Output: 1.00000
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << ", row = " << testData[i].row
             << ", column = " << testData[i].column << "\n";

        answer = cSolution.knightProbability(testData[i].n, testData[i].k, testData[i].row, testData[i].column);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
