#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(int n, vector<int>& cuts) {
        int retVal = 0;

        int cutsSize = cuts.size();

        sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.emplace_back(n);

        vector<vector<int>> dp(cutsSize + 2, vector<int>(cutsSize + 2));
        for (int diff = 2; diff < cutsSize + 2; ++diff) {
            for (int left = 0; left < cutsSize + 2 - diff; ++left) {
                int right = left + diff;
                int ans = numeric_limits<int>::max();
                for (int mid = left + 1; mid < right; ++mid) {
                    ans = min(ans, dp[left][mid] + dp[mid][right] + cuts[right] - cuts[left]);
                }
                dp[left][right] = ans;
            }
        }

        retVal = dp[0][cutsSize + 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> cuts;
    };
    vector<subject> testData{{7, {1, 3, 4, 5}}, {9, {5, 6, 1, 4, 2}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 7, cuts = [1,3,4,5]
     *  Output: 16
     *
     *  Input: n = 9, cuts = [5,6,1,4,2]
     *  Output: 22
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", cuts = [";
        for (long unsigned int j = 0; j < testData[i].cuts.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].cuts[j];
        }
        cout << "]\n";

        answer = cSolution.minCost(testData[i].n, testData[i].cuts);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
