#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int retVal = 0;

        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        int groupSize = group.size();
        for (int i = 1; i <= groupSize; i++) {
            int members = group[i - 1];
            int earn = profit[i - 1];
            for (int j = n; j >= members; j--) {
                for (int k = minProfit; k >= 0; k--) {
                    dp[j][k] = (dp[j][k] + dp[j - members][max(0, k - earn)]) % MODULO;
                }
            }
        }
        retVal = dp[n][minProfit];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int minProfit;
        vector<int> group;
        vector<int> profit;
    };
    vector<subject> testData{{5, 3, {2, 2}, {2, 3}}, {10, 5, {2, 3, 5}, {6, 7, 8}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
     *  Output: 2
     *
     *  Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
     *  Output: 7
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", minProfit = " << testData[i].minProfit << ", group = [";
        for (long unsigned int j = 0; j < testData[i].group.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].group[j];
        }
        cout << "], profit = [";
        for (long unsigned int j = 0; j < testData[i].profit.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].profit[j];
        }
        cout << "]\n";

        answer =
            cSolution.profitableSchemes(testData[i].n, testData[i].minProfit, testData[i].group, testData[i].profit);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
