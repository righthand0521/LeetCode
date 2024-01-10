#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int dfs(vector<vector<int>>& events, int eventsSize, int k, vector<vector<int>>& dp, int index, int count,
            int previousEndDay) {
        int retVal = 0;

        if ((index == eventsSize) || (count == k)) {
            return retVal;
        }

        if (events[index][0] <= previousEndDay) {
            retVal = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
        } else if (dp[count][index] != -1) {
            retVal = dp[count][index];
        } else {
            int ans1 = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
            int ans2 = dfs(events, eventsSize, k, dp, index + 1, count + 1, events[index][1]) + events[index][2];
            retVal = max(ans1, ans2);
            dp[count][index] = retVal;
        }

        return retVal;
    }
    int maxValue(vector<vector<int>>& events, int k) {
        int retVal = 0;

        sort(events.begin(), events.end());

        int eventsSize = events.size();
        vector<vector<int>> dp(k + 1, vector<int>(eventsSize, -1));
        int index = 0;
        int count = 0;
        int previousEndDay = -1;
        retVal = dfs(events, eventsSize, k, dp, index, count, previousEndDay);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> events;
        int k;
    };
    vector<subject> testData{{{{1, 2, 4}, {3, 4, 3}, {2, 3, 1}}, 2},
                             {{{1, 2, 4}, {3, 4, 3}, {2, 3, 10}}, 2},
                             {{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
     *  Output: 7
     *
     *  Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
     *  Output: 10
     *
     *  Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
     *  Output: 9
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: events = [";
        for (long unsigned int j = 0; j < testData[i].events.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].events[j].size(); ++k) {
                cout << (k == 0 ? "" : ",") << testData[i].events[j][k];
            }
            cout << "]";
        }
        cout << "], k = " << testData[i].k << "\n";

        answer = cSolution.maxValue(testData[i].events, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
