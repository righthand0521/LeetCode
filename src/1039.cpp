#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minScoreTriangulation(vector<int>& values) {
        int retVal = 0;

        int valuesSize = values.size();
        vector<vector<int>> dp(valuesSize, vector<int>(valuesSize, 0));
        for (int d = 2; d < valuesSize; ++d) {
            for (int i = 0; i < valuesSize - d; ++i) {
                int j = i + d;
                dp[i][j] = numeric_limits<int>::max();
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + values[i] * values[j] * values[k]);
                }
            }
        }
        retVal = dp[0][valuesSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> values;
    };
    vector<subject> testData{{{1, 2, 3}}, {{3, 7, 4, 5}}, {{1, 3, 1, 4, 1, 5}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: values = [1,2,3]
     *  Output: 6
     *
     *  Input: values = [3,7,4,5]
     *  Output: 144
     *
     *  Input: values = [1,3,1,4,1,5]
     *  Output: 13
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: values = [";
        for (long unsigned int j = 0; j < testData[i].values.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].values[j];
        }
        cout << "]\n";

        answer = cSolution.minScoreTriangulation(testData[i].values);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
