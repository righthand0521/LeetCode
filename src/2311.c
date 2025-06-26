#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubsequence(char* s, int k) {
    int retVal = 0;

    int sm = 0;
    int bits = (int)(log2(k)) + 1;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; i++) {
        char ch = s[sSize - 1 - i];
        if (ch == '1') {
            if ((i < bits) && (sm + (1 << i) <= k)) {
                sm += (1 << i);
                retVal++;
            }
        } else {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
        int k;
    } testCase[] = {{"1001010", 5}, {"00101001", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "1001010", k = 5
     *  Output: 5
     *
     *  Input: s = "00101001", k = 1
     *  Output: 6
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = longestSubsequence(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
