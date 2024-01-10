#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
#define DYNAMIC_PROGRAMMING (1)
   public:
    int minimumDeletions(string s) {
        int retVal = 0;

#if (DYNAMIC_PROGRAMMING)
        cout << "DYNAMIC_PROGRAMMING\n";

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
#else
        /* https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/solutions/2149746/qian-hou-zhui-fen-jie-yi-zhang-tu-miao-d-dor2/
         *  Input: s = "aababbab"
         *  | (a)   (a)   b   (a)  b   b  (a)  b   ===> 4
         *     a  |  a    b    a   b   b   a   b   =a=> 4 - 1 = 3
         *     a     a  | b    a   b   b   a   b   =a=> 3 - 1 = 2
         *     a     a    b |  a   b   b   a   b   =b=> 2 + 1 = 3
         *     a     a    b    a | b   b   a   b   =a=> 3 - 1 = 2   => min
         *     a     a    b    a   b | b   a   b   =b=> 2 + 1 = 3
         *     a     a    b    a   b   b | a   b   =b=> 3 + 1 = 4
         *     a     a    b    a   b   b   a | b   =a=> 4 - 1 = 3
         *     a     a    b    a   b   b   a   b | =a=> 3 + 1 = 4
         */
        int sSize = s.size();

        int aCount = 0;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == 'a') {
                ++aCount;
            }
        }
        retVal = aCount;

        int bCount = 0;
        for (int i = 0; i < sSize; ++i) {
            if (s[i] == 'a') {
                --aCount;
            } else {
                ++bCount;
            }

            retVal = min(retVal, bCount + aCount);
        }
#endif

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
