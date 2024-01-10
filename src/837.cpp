#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // https://leetcode.com/problems/new-21-game/solutions/132334/one-pass-dp-o-n/
    double new21Game(int n, int k, int maxPts) {
        double retVal = 1;

        if ((k == 0) || (n >= k + maxPts)) {
            return retVal;
        }

        // dp[i] is the probability that we get points i at some moment.
        // 1 - dp[i]is the probability that we skip the points i.
        vector<double> dp(n + 1);
        dp[0] = 1.0;

        // maxPtsSum = sum(last maxPts dp values)
        double maxPtsSum = 1.0;

        // dp[i] = sum(last W dp values) / maxPts
        retVal = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = maxPtsSum / maxPts;
            if (i < k) {
                maxPtsSum += dp[i];
            } else {
                retVal += dp[i];
            }

            if (i - maxPts >= 0) {
                maxPtsSum -= dp[i - maxPts];
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        int n;
        int k;
        int maxPts;
    };
    vector<subject> testData{{10, 1, 10}, {6, 1, 10}, {21, 17, 10}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: n = 10, k = 1, maxPts = 10
     *  Output: 1.00000
     *
     *  Input: n = 6, k = 1, maxPts = 10
     *  Output: 0.60000
     *
     *  Input: n = 21, k = 17, maxPts = 10
     *  Output: 0.73278
     */

    Solution cSolution;
    double answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: n = " << testData[i].n << ", k = " << testData[i].k << ", maxPts = " << testData[i].maxPts
             << "\n";

        answer = cSolution.new21Game(testData[i].n, testData[i].k, testData[i].maxPts);
        cout.setf(ios::fixed);
        cout.precision(5);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
