#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long mostPoints(vector<vector<int>>& questions) {
        long long retVal = 0;

        int questionsSize = questions.size();
        vector<long long> dp(questionsSize, 0);
        dp[questionsSize - 1] = questions[questionsSize - 1][0];
        for (int i = questionsSize - 2; i >= 0; --i) {
            dp[i] = questions[i][0];
            int skip = questions[i][1];
            if (i + skip + 1 < questionsSize) {
                dp[i] += dp[i + skip + 1];
            }
            dp[i] = max(dp[i], dp[i + 1]);
        }
        retVal = dp[0];

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<vector<int>> questions;
    };
    vector<subject> testData{{{{3, 2}, {4, 3}, {4, 4}, {2, 5}}}, {{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: questions = [[3,2],[4,3],[4,4],[2,5]]
     *  Output: 5
     *
     *  Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
     *  Output: 7
     */

    Solution cSolution;
    long long answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: questions = [";
        for (long unsigned int j = 0; j < testData[i].questions.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << "[";
            for (long unsigned int k = 0; k < testData[i].questions[j].size(); ++k) {
                cout << ((k == 0) ? "" : ",") << testData[i].questions[j][k];
            }
            cout << "]";
        }
        cout << "]\n";

        answer = cSolution.mostPoints(testData[i].questions);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
