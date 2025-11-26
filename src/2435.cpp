#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    static constexpr int MODULO = 1e9 + 7;

   public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int retVal = 0;

        int gridSize = grid.size();
        int gridColSize = grid[0].size();
        auto dp = vector(gridSize + 1, vector(gridColSize + 1, vector<long long>(k)));
        for (int i = 1; i <= gridSize; i++) {
            for (int j = 1; j <= gridColSize; j++) {
                if ((i == 1) && (j == 1)) {
                    dp[i][j][grid[0][0] % k] = 1;
                    continue;
                }

                int value = grid[i - 1][j - 1] % k;
                for (int r = 0; r < k; r++) {
                    int prevMod = (r - value + k) % k;
                    dp[i][j][r] = (dp[i - 1][j][prevMod] + dp[i][j - 1][prevMod]) % MODULO;
                }
            }
        }
        retVal = dp[gridSize][gridColSize][0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> grid;
        int k;
    };
    vector<subject> testData{
        {{{5, 2, 4}, {3, 0, 5}, {0, 7, 2}}, 3}, {{{0, 0}}, 5}, {{{7, 3, 4, 9}, {2, 3, 6, 2}, {2, 3, 7, 0}}, 1}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
     *  Output: 2
     *
     *  Input: grid = [[0,0]], k = 5
     *  Output: 1
     *
     *  Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
     *  Output: 10
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: grid = [";
        for (long unsigned int j = 0; j < testData[i].grid.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].grid[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].grid[j][k];
            }
            cout << "]";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.numberOfPaths(testData[i].grid, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
