#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    bool makesquare(vector<int>& matchsticks) {
        bool retVal = false;

        int sumOfMatchsticks = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sumOfMatchsticks % 4 != 0) {
            return retVal;
        }
        int squareSide = sumOfMatchsticks / 4;

        int matchsticksSize = matchsticks.size();
        int dpSize = (1 << matchsticksSize);
        vector<int> dp(dpSize, -1);
        dp[0] = 0;
        for (int i = 1; i < dpSize; ++i) {
            for (int key = 0; key < matchsticksSize; ++key) {
                int value = matchsticks[key];
                if ((i & (1 << key)) == 0) {
                    continue;
                }
                int j = i & ~(1 << key);

                if ((dp[j] >= 0) && (dp[j] + value <= squareSide)) {
                    dp[i] = (dp[j] + value) % squareSide;
                    break;
                }
            }
        }
        retVal = (dp[dpSize - 1] == 0);

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> matchsticks;
    };
    vector<subject> testData{{{1, 1, 2, 2, 2}}, {{3, 3, 3, 3, 4}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: matchsticks = [1,1,2,2,2]
     *  Output: true
     *
     *  Input: matchsticks = [3,3,3,3,4]
     *  Output: false
     */

    Solution cSolution;
    bool answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: matchsticks = [";
        for (long unsigned int j = 0; j < testData[i].matchsticks.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].matchsticks[j];
        }
        cout << "]\n";

        answer = cSolution.makesquare(testData[i].matchsticks);
        cout << "Output: " << (answer == true ? "true" : "false") << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
