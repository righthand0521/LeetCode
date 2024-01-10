#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long maxPoints(vector<vector<int>>& points) {
        long long retVal = 0;

        int row = points.size();
        int col = points[0].size();
        vector<vector<long long>> dp(row, vector<long long>(col, 0));
        for (int i = 0; i < col; ++i) {
            dp[0][i] = points[0][i];
        }

        // https://leetcode.com/problems/maximum-number-of-points-with-cost/solutions/1344888/c-dp-from-o-m-n-n-to-o-m-n/
        //  dp[i][j] = max(dp[i - 1][k] + point[i][j] - abs(j - k)) for each 0 <= k < points[i - 1].size()
        //  => dp[i][j] = max(dp[i - 1][k] + k) + points[i][j] - j for all 0 <= k <= j
        //  => dp[i][j] = max(dp[i - 1][k] - k) + points[i][j] + j for all j <= k <= points[i].size() - 1
        for (int i = 1; i < row; ++i) {
            vector<long long> dpLeft(col, 0);
            dpLeft[0] = dp[i - 1][0];
            for (int k = 1; k < col; ++k) {
                dpLeft[k] = max(dpLeft[k - 1], dp[i - 1][k] + k);
            }

            vector<long long> dpRight(col, 0);
            dpRight[col - 1] = dp[i - 1][col - 1] - col + 1;
            for (int k = col - 2; k >= 0; --k) {
                dpRight[k] = max(dpRight[k + 1], dp[i - 1][k] - k);
            }

            for (int j = 0; j < col; ++j) {
                dp[i][j] = max(dpLeft[j] - j, dpRight[j] + j) + points[i][j];
            }
        }
        retVal = *max_element(dp[row - 1].begin(), dp[row - 1].end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> points;
    };
    vector<subject> testData{{{{1, 2, 3}, {1, 5, 1}, {3, 1, 1}}}, {{{1, 5}, {2, 3}, {4, 2}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: points = [[1,2,3],[1,5,1],[3,1,1]]
     *  Output: 9
     *
     *  Input: points = [[1,5],[2,3],[4,2]]
     *  Output: 11
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].points.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].points[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].points[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.maxPoints(testData[i].points);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
