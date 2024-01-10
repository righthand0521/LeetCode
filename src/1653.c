#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)
int minimumDeletions(char *s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;

#if (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    /* 926. Flip String to Monotone Increasing
     *  https://leetcode.com/problems/flip-string-to-monotone-increasing/
     */
    int num = 0;
    for (i = 0; i < sSize; ++i) {
        /* Let num be the number of character 'b' in s' prefix of length i:
         *  dp[i] = dp[i - 1] if s[i - 1] = 'b'
         *  dp[i] = min(num, dp[i - 1] + 1) otherwise.
         */
        if (s[i] == 'a') {
            retVal = fmin((retVal + 1), num);
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

    int aCount = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            ++aCount;
        }
    }
    retVal = aCount;

    int bCount = 0;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == 'a') {
            --aCount;
        } else {
            ++bCount;
        }

        retVal = fmin(retVal, bCount + aCount);
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aababbab"}, {"bbaaaaabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aababbab"
     *  Output: 2
     *
     *  Input: s = "bbaaaaabb"
     *  Output: 2
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumDeletions(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
