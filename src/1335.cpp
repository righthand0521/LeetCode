#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int retVal = -1;

        int jobDifficultySize = jobDifficulty.size();
        if (jobDifficultySize < d) {
            return retVal;
        }

        int maxDifficulty = 0;
        vector<int> dp(jobDifficultySize);
        for (int i = 0; i < jobDifficultySize; ++i) {
            maxDifficulty = max(maxDifficulty, jobDifficulty[i]);
            dp[i] = maxDifficulty;
        }

        for (int i = 1; i < d; ++i) {
            vector<int> dpNext(jobDifficultySize);

            stack<pair<int, int>> monotonicStack;
            for (int j = i; j < jobDifficultySize; ++j) {
                int minDifficulty = dp[j - 1];
                while ((monotonicStack.empty() == false) &&
                       (jobDifficulty[monotonicStack.top().first] < jobDifficulty[j])) {
                    minDifficulty = min(minDifficulty, monotonicStack.top().second);
                    monotonicStack.pop();
                }

                if (monotonicStack.empty() == true) {
                    dpNext[j] = minDifficulty + jobDifficulty[j];
                } else {
                    dpNext[j] = min(dpNext[monotonicStack.top().first], minDifficulty + jobDifficulty[j]);
                }
                monotonicStack.emplace(j, minDifficulty);
            }
            swap(dp, dpNext);
        }
        retVal = dp[jobDifficultySize - 1];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> jobDifficulty;
        int d;
    };
    vector<subject> testData{{{6, 5, 4, 3, 2, 1}, 2}, {{9, 9, 9}, 4}, {{1, 1, 1}, 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: jobDifficulty = [6,5,4,3,2,1], d = 2
     *  Output: 7
     *
     *  Input: jobDifficulty = [9,9,9], d = 4
     *  Output: -1
     *
     *  Input: jobDifficulty = [1,1,1], d = 3
     *  Output: 3
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: jobDifficulty = [";
        for (long unsigned int j = 0; j < testData[i].jobDifficulty.size(); ++j) {
            cout << (j == 0 ? "" : ",") << testData[i].jobDifficulty[j];
        }
        cout << "], d = " << testData[i].d << "\n";

        answer = cSolution.minDifficulty(testData[i].jobDifficulty, testData[i].d);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
