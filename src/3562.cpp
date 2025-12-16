#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    tuple<vector<int>, vector<int>, int> dfs(vector<int>& present, vector<int>& future, int budget,
                                             vector<vector<int>>& g, int u) {
        tuple<vector<int>, vector<int>, int> retVal;

        int cost = present[u];
        int dCost = present[u] / 2;  // discounted cost

        // dp[u][state][budget]
        // state = 0: Do not purchase parent node, state = 1: Must purchase parent node
        auto dp0 = vector(budget + 1, 0);
        auto dp1 = vector(budget + 1, 0);

        // subProfit[state][budget]
        // state = 0: discount not available, state = 1: discount available
        auto subProfit0 = vector(budget + 1, 0);
        auto subProfit1 = vector(budget + 1, 0);

        int uSize = cost;

        for (auto v : g[u]) {
            auto [subDp0, subDp1, vSize] = dfs(present, future, budget, g, v);
            uSize += vSize;
            for (int i = budget; i >= 0; i--) {
                for (int sub = 0; sub <= min(vSize, i); sub++) {
                    subProfit0[i] = max(subProfit0[i], subProfit0[i - sub] + subDp0[sub]);
                    subProfit1[i] = max(subProfit1[i], subProfit1[i - sub] + subDp1[sub]);
                }
            }
        }

        for (int i = 0; i <= budget; i++) {
            dp0[i] = subProfit0[i];
            dp1[i] = subProfit0[i];

            if (i >= dCost) {
                dp1[i] = max(subProfit0[i], subProfit1[i - dCost] + future[u] - dCost);
            }

            if (i >= cost) {
                dp0[i] = max(subProfit0[i], subProfit1[i - cost] + future[u] - cost);
            }
        }

        retVal = {dp0, dp1, uSize};

        return retVal;
    }

   public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        int retVal = 0;

        vector<vector<int>> g(n);
        for (auto& e : hierarchy) {
            g[e[0] - 1].emplace_back(e[1] - 1);
        }
        auto [dp0, dp1, uSize] = dfs(present, future, budget, g, 0);
        retVal = dp0[budget];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> present;
        vector<int> future;
        vector<vector<int>> hierarchy;
        int budget;
    };
    vector<subject> testData{{2, {1, 2}, {4, 3}, {{1, 2}}, 3},
                             {2, {3, 4}, {5, 8}, {{1, 2}}, 4},
                             {3, {4, 6, 8}, {7, 9, 11}, {{1, 2}, {1, 3}}, 10},
                             {3, {5, 2, 3}, {8, 5, 6}, {{1, 2}, {2, 3}}, 7}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
     *  Output: 5
     *
     *  Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4
     *  Output: 4
     *
     *  Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10
     *  Output: 10
     *
     *  Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7
     *  Output: 12
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = [" << testData[i].n << "], present = [";
        for (long unsigned int j = 0; j < testData[i].present.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].present[j];
        }
        cout << "], future = [";
        for (long unsigned int j = 0; j < testData[i].future.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].future[j];
        }
        cout << "], hierarchy = [";
        for (long unsigned int j = 0; j < testData[i].hierarchy.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].hierarchy[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].hierarchy[j][k];
            }
            cout << "]";
        }
        cout << "], budget = " << testData[i].budget << "]\n";

        answer = cSolution.maxProfit(testData[i].n, testData[i].present, testData[i].future, testData[i].hierarchy,
                                     testData[i].budget);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
