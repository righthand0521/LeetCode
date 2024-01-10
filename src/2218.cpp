#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int retVal = 0;

        int pilesSize = piles.size();
        vector<vector<int>> prefixSum(pilesSize);
        for (int i = 0; i < pilesSize; ++i) {
            prefixSum[i].push_back(0);
            for (long unsigned int j = 0; j < piles[i].size(); ++j) {
                prefixSum[i].push_back(prefixSum[i][j] + piles[i][j]);
            }
        }

        vector<int> dp(k + 1, 0);
        for (int i = 0; i < pilesSize; ++i) {
            for (int j = k; j >= 0; --j) {
                int len = piles[i].size() + 1;
                for (int select = 0; select < len; ++select) {
                    int sum_ = prefixSum[i][select];
                    if (j - select >= 0) {
                        dp[j] = max(dp[j], dp[j - select] + sum_);
                    }
                }
            }
        }
        retVal = dp[k];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> piles;
        int k;
    };
    vector<subject> testData{{{{1, 100, 3}, {7, 8, 9}}, 2},
                             {{{100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}}, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: piles = [[1,100,3],[7,8,9]], k = 2
     *  Output: 101
     *
     *  Input: piles = [[100],[100],[100],[100],[100],[100],[1,1,1,1,1,1,700]], k = 7
     *  Output: 706
     */

    Solution cSolution;
    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: piles = [";
        for (long unsigned int j = 0; j < testData[i].piles.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].piles[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].piles[j][k];
            }
            cout << "]";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxValueOfCoins(testData[i].piles, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
