#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/sum-of-beauty-of-all-substrings/solutions/2016548/suo-you-zi-zi-fu-chuan-mei-li-zhi-zhi-he-rq3x/
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int beautySum(char* s) {
    int retVal = 0;

    int len = strlen(s);
    if (len == 1) {
        return retVal;
    }

// s consists of only lowercase English letters
#define HASH_SIZE (26)
    int HASHTABLE[HASH_SIZE];
    int mostFrequencies;
    int leastFrequencies;
    int idx;

    int i, j, k;
    for (i = 0; i < len; ++i) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        mostFrequencies = 0;
        for (j = i; j < len; ++j) {
            idx = s[j] - 'a';
            ++HASHTABLE[idx];
            mostFrequencies = MAX(mostFrequencies, HASHTABLE[idx]);

            leastFrequencies = len;
            for (k = 0; k < HASH_SIZE; ++k) {
                if (HASHTABLE[k] == 0) {
                    continue;
                }
                leastFrequencies = MIN(leastFrequencies, HASHTABLE[k]);
            }

            retVal += (mostFrequencies - leastFrequencies);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aabcb"}, {"aabcbaa"}, {""}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = beautySum(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
