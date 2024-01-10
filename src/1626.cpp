#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int retVal = 0;

        int len = scores.size();

        vector<int> player(len);
        for (int i = 0; i < len; ++i) {
            player[i] = i;
        }
        sort(player.begin(), player.end(),
             [&](int i, int j) { return ages[i] < ages[j] || (ages[i] == ages[j] && scores[i] < scores[j]); });

        vector<int> dp(len);
        for (int i = 0; i < len; ++i) {
            int index = player[i];
            dp[i] = scores[index];
            for (int j = 0; j < i; ++j) {
                if (scores[player[j]] <= scores[index]) {
                    dp[i] = max(dp[i], dp[j] + scores[index]);
                }
            }
            retVal = max(retVal, dp[i]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> scores;
        vector<int> ages;
    };
    vector<subject> testData{
        {{1, 3, 5, 10, 15}, {1, 2, 3, 4, 5}}, {{4, 5, 6, 5}, {2, 1, 2, 1}}, {{1, 2, 3, 5}, {8, 9, 10, 1}}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer = false;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: scores = [";
        for (long unsigned int j = 0; j < testData[i].scores.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].scores[j];
        }
        cout << "], ages = [";
        for (long unsigned int j = 0; j < testData[i].ages.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].ages[j];
        }
        cout << "]\n";

        answer = cSolution.bestTeamScore(testData[i].scores, testData[i].ages);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
