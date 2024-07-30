#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumDeletions(string s) {
        int retVal = 0;

        /* 926. Flip String to Monotone Increasing
         *  https://leetcode.com/problems/flip-string-to-monotone-increasing/
         */
        int num = 0;
        for (char c : s) {
            /* Let num be the number of character 'b' in s' prefix of length i:
             *  dp[i] = dp[i - 1] if s[i - 1] = 'b'
             *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
             */
            if (c == 'a') {
                retVal = min((retVal + 1), num);
            } else {
                ++num;
            }
        }

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"aababbab"}, {"bbaaaaabb"}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "aababbab"
     *  Output: 2
     *
     *  Input: s = "bbaaaaabb"
     *  Output: 2
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minimumDeletions(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
