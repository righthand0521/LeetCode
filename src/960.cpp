#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDeletionSize(vector<string>& strs) {
        int retVal = 0;

        int strSize = strs[0].size();

        vector<int> dp(strSize, 1);
        for (int i = strSize - 2; i >= 0; --i) {
            for (int j = i + 1; j < strSize; ++j) {
                bool needUpdate = true;
                for (const string& s : strs) {
                    if (s[i] > s[j]) {
                        needUpdate = false;
                        break;
                    }
                }
                if (needUpdate == true) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        retVal = strSize - *max_element(dp.begin(), dp.end());

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        vector<string> strs;
    };
    vector<subject> testData{{{"babca", "bbazb"}}, {{"edcba"}}, {{"ghi", "def", "abc"}}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: strs = ["babca","bbazb"]
     *  Output: 3
     *
     *  Input: strs = ["edcba"]
     *  Output: 4
     *
     *  Input: strs = ["ghi","def","abc"]
     *  Output: 0
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: strs = [";
        for (long unsigned int j = 0; j < testData[i].strs.size(); ++j) {
            cout << (j == 0 ? "" : ",") << "\"" << testData[i].strs[j] << "\"";
        }
        cout << "]\n";

        answer = cSolution.minDeletionSize(testData[i].strs);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
