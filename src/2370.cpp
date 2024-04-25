#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int letters = 26;  // s consists of lowercase English letters.

   public:
    int longestIdealString(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        vector<int> dp(letters, 0);
        for (int i = 0; i < sSize; ++i) {
            int current = s[i] - 'a';
            int best = 0;
            for (int j = 0; j < letters; ++j) {
                if (abs(j - current) <= k) {
                    best = max(best, dp[j]);
                }
            }

            dp[current] = max(dp[current], best + 1);
            retVal = max(retVal, dp[current]);
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"acfgbd", 2}, {"abcd", 3}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "acfgbd", k = 2
     *  Output: 4
     *
     *  Input: s = "abcd", k = 3
     *  Output: 4
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.longestIdealString(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
