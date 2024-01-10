#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int retVal = 0;

        int daysSize = days.size();
        int dpSize = days[daysSize - 1] + 1;
        vector<int> dp(dpSize, 0);

        int idx = 0;
        for (int i = 1; i < dpSize; ++i) {
            if (i != days[idx]) {
                dp[i] = dp[i - 1];
                continue;
            }
            dp[i] = min(dp[max(0, i - 1)] + costs[0], dp[max(0, i - 7)] + costs[1]);
            dp[i] = min(dp[i], dp[max(0, i - 30)] + costs[2]);
            ++idx;
        }
        retVal = dp[dpSize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> days;
        vector<int> costs;
    };
    vector<subject> testData{{{1, 4, 6, 7, 8, 20}, {2, 7, 15}},
                             {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31}, {2, 7, 15}},
                             {{1, 4, 6, 7, 8, 20}, {7, 2, 15}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: days = [1,4,6,7,8,20], costs = [2,7,15]
     *  Output: 11
     *
     *  Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
     *  Output: 17
     *
     *  Input: days = [1,4,6,7,8,20], costs = [7,2,15]
     *  Output: 6
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: days = [";
        for (long unsigned int j = 0; j < testData[i].days.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].days[j];
        }
        cout << "], costs = [";
        for (long unsigned int j = 0; j < testData[i].costs.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].costs[j];
        }
        cout << "]\n";

        answer = cSolution.mincostTickets(testData[i].days, testData[i].costs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
