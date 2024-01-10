#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.cn/problems/stone-game-ii/solutions/284065/java-dong-tai-gui-hua-qing-xi-yi-dong-17xing-by-lg/
    int stoneGameII(vector<int>& piles) {
        int retVal = 0;

        int pilesSize = piles.size();
        vector<vector<int>> dp(pilesSize, vector<int>(pilesSize + 1));
        int sum = 0;
        for (int i = pilesSize - 1; i >= 0; --i) {
            sum += piles[i];
            for (int M = 1; M <= pilesSize; ++M) {
                if (i + 2 * M >= pilesSize) {
                    dp[i][M] = sum;
                } else {
                    for (int x = 1; x <= 2 * M; ++x) {
                        dp[i][M] = max(dp[i][M], sum - dp[i + x][max(M, x)]);
                    }
                }
            }
        }
        retVal = dp[0][1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> piles;
    };
    vector<subject> testData{{{2, 7, 9, 4, 4}}, {{1, 2, 3, 4, 5, 100}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: piles = [2,7,9,4,4]
     *  Output: 10
     *
     *  Input: piles = [1,2,3,4,5,100]
     *  Output: 104
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: piles = [";
        for (long unsigned int j = 0; j < testData[i].piles.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].piles[j];
        }
        cout << "]\n";

        answer = cSolution.stoneGameII(testData[i].piles);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
