#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define MODULO (int)(1e9 + 7)
   public:
    int numberOfArrays(string s, int k) {
        int retVal = 0;

        int sSize = s.size();

        // dp[i] is the number of ways you can divide the string starting from index i to the end.
        vector<int> dp(sSize + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < sSize; ++i) {
            if (s[i] == '0') {
                continue;
            }

            long long num = s[i] - '0';
            for (int j = (i + 1); j < (sSize + 1); ++j) {
                if (num > (long long)k) {
                    break;
                }
                num *= 10;
                num += s[j] - '0';

                dp[j] += dp[i];
                dp[j] %= MODULO;
            }

            dp[i] %= MODULO;
        }
        retVal = dp.back() % MODULO;

        return retVal;
    }
};

int main(int argc, char** argv) {
    struct subject {
        string s;
        int k;
    };
    vector<subject> testData{{"1000", 10000}, {"1000", 10}, {"1317", 2000}};
    int numberOfTestCase = testData.size();
    /* Example
     *  Input: s = "1000", k = 10000
     *  Output: 1
     *
     *  Input: s = "1000", k = 10
     *  Output: 0
     *
     *  Input: s = "1317", k = 2000
     *  Output: 8
     */

    Solution cSolution;
    int answer;
    for (int i = 0; i < numberOfTestCase; ++i) {
        cout << "Input: s = \"" << testData[i].s << "\", k = " << testData[i].k << "\n";

        answer = cSolution.numberOfArrays(testData[i].s, testData[i].k);
        cout << "Output: " << answer << "\n";

        cout << "\n";
    }

    return EXIT_SUCCESS;
}
