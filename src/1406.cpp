#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    string stoneGameIII(vector<int>& stoneValue) {
        string retVal = "Tie";

        int stoneValueSize = stoneValue.size();
        vector<int> dp(stoneValueSize + 1, 0);
        for (int i = stoneValueSize - 1; i >= 0; --i) {
            dp[i] = stoneValue[i] - dp[i + 1];
            if (i + 2 <= stoneValueSize) {
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] - dp[i + 2]);
            }
            if (i + 3 <= stoneValueSize) {
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2] - dp[i + 3]);
            }
        }

        if (dp[0] > 0) {
            retVal = "Alice";
        } else if (dp[0] < 0) {
            retVal = "Bob";
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<int> stoneValue;
    };
    vector<subject> testData{{{1, 2, 3, 7}}, {{1, 2, 3, -9}}, {{1, 2, 3, 6}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: values = [1,2,3,7]
     *  Output: "Bob"
     *
     *  Input: values = [1,2,3,-9]
     *  Output: "Alice"
     *
     *  Input: values = [1,2,3,6]
     *  Output: "Tie"
     */

    Solution cSolution;
    string answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: values = [";
        for (long unsigned int j = 0; j < testData[i].stoneValue.size(); ++j) {
            cout << ((j == 0) ? "" : ",") << testData[i].stoneValue[j];
        }
        cout << "]\n";

        answer = cSolution.stoneGameIII(testData[i].stoneValue);
        cout << "Output: \"" << answer << "\"\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
