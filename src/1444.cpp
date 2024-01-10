#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    // https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
    int dfs(int row, int col, int k, int r, int c, vector<vector<vector<int>>>& dp, vector<vector<int>>& preSum) {
        int retVal = 0;

        // if the remain piece has no apple -> invalid
        if (preSum[r][c] == 0) {
            return retVal;
        }

        // found valid way after using k-1 cuts
        if (k == 0) {
            retVal = 1;
            return retVal;
        }

        if (dp[k][r][c] != -1) {
            retVal = dp[k][r][c];
            return retVal;
        }

        // cut in horizontal
        for (int nr = r + 1; nr < row; nr++) {
            // cut if the upper piece contains at least one apple
            if (preSum[r][c] - preSum[nr][c] > 0) {
                retVal = (retVal + dfs(row, col, k - 1, nr, c, dp, preSum)) % MODULO;
            }
        }

        // cut in vertical
        for (int nc = c + 1; nc < col; nc++) {
            // cut if the left piece contains at least one apple
            if (preSum[r][c] - preSum[r][nc] > 0) {
                retVal = (retVal + dfs(row, col, k - 1, r, nc, dp, preSum)) % MODULO;
            }
        }

        dp[k][r][c] = retVal;

        return retVal;
    }
    int ways(vector<string>& pizza, int k) {
        int retVal = 0;

        int row = pizza.size();
        int col = pizza[0].size();

        // preSum[r][c] is the total number of apples in pizza[r:][c:]
        vector<vector<int>> preSum = vector(row + 1, vector(col + 1, 0));
        for (int r = row - 1; r >= 0; r--) {
            for (int c = col - 1; c >= 0; c--) {
                preSum[r][c] = preSum[r][c + 1] + preSum[r + 1][c] - preSum[r + 1][c + 1] + (pizza[r][c] == 'A');
            }
        }

        vector<vector<vector<int>>> dp = vector(k, vector(row, vector(col, -1)));
        retVal = dfs(row, col, k - 1, 0, 0, dp, preSum);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> pizza;
        int k;
    };
    vector<subject> testData{{{"A..", "AAA", "..."}, 3}, {{"A..", "AA.", "..."}, 3}, {{"A..", "A..", "..."}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: pizza = ["A..","AAA","..."], k = 3
     *  Output: 3
     *
     *  Input: pizza = ["A..","AA.","..."], k = 3
     *  Output: 1
     *
     *  Input: pizza = ["A..","A..","..."], k = 1
     *  Output: 1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: pizza = [";
        for (long unsigned int j = 0; j < testData[i].pizza.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "\"" << testData[i].pizza[j] << "\"";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.ways(testData[i].pizza, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
