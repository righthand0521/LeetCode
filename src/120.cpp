#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int retVal = 0;

        int triangleSize = triangle.size();
        vector<vector<int>> dp(triangleSize, vector<int>(triangleSize, 0));
        dp[0][0] = triangle[0][0];

        for (int i = 1; i < triangleSize; ++i) {
            dp[i][0] = dp[i - 1][0] + triangle[i][0];
            for (int j = 1; j < i; ++j) {
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        }

        retVal = dp[triangleSize - 1][0];
        for (int i = 1; i < triangleSize; i++) {
            retVal = min(retVal, dp[triangleSize - 1][i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> triangle;
    };
    vector<subject> testData{{{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}}, {{{-10}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
     *  Output: 11
     *
     *  Input: triangle = [[-10]]
     *  Output: -10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: triangle = [";
        for (long unsigned int j = 0; j < testData[i].triangle.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].triangle[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].triangle[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.minimumTotal(testData[i].triangle);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
