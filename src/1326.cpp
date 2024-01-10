#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minTaps(int n, vector<int>& ranges) {
        int retVal = -1;

        // 1 <= n <= 10^4; ranges.length == n + 1; 0 <= ranges[i] <= 100
        int infinity = (int)(1e9);

        vector<int> dp(n + 1, infinity);
        dp[0] = 0;

        for (int i = 0; i <= n; ++i) {
            int tapStart = max(0, i - ranges[i]);
            int tapEnd = min(n, i + ranges[i]);
            for (int j = tapStart; j <= tapEnd; ++j) {
                dp[tapEnd] = min(dp[tapEnd], dp[j] + 1);
            }
        }

        if (dp[n] != infinity) {
            retVal = dp[n];
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        vector<int> ranges;
    };
    vector<subject> testData{{5, {3, 4, 1, 1, 0, 0}}, {3, {0, 0, 0, 0}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 5, ranges = [3,4,1,1,0,0]
     *  Output: 1
     *
     *  Input: n = 3, ranges = [0,0,0,0]
     *  Output: -1
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", ranges = [";
        for (long unsigned int j = 0; j < testData[i].ranges.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].ranges[j];
        }
        cout << "]\n";

        answer = cSolution.minTaps(testData[i].n, testData[i].ranges);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
