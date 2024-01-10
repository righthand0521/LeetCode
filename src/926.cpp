#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minFlipsMonoIncr(string s) {
        int retVal = 0;

        int num = 0;
        for (char c : s) {
            /* Let number num be the number of character 1s in s' prefix of length i:
             *  dp[i] = dp[i - 1] if s[i - 1] = '1'
             *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
             */
            if (c == '0') {
                retVal = min((retVal + 1), num);
            } else {
                ++num;
            }
        }

        return retVal;
    }
};

int main(int argc, char **argv) {
    struct subject {
        string s;
    };
    vector<subject> testData{{"00110"}, {"010110"}, {"00011000"}};
    int numberOfTestCase = testData.size();

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\"\n";

        answer = cSolution.minFlipsMonoIncr(testData[i].s);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
