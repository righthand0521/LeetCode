#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chalkReplacer(int* chalk, int chalkSize, int k) {
    int retVal = 0;

    int i;

    long long total = 0;
    for (i = 0; i < chalkSize; ++i) {
        total += chalk[i];
    }
    k %= total;

    for (i = 0; i < chalkSize; ++i) {
        if (chalk[i] > k) {
            retVal = i;
            break;
        }
        k -= chalk[i];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int chalk[MAX_SIZE];
        int chalkSize;
        int k;
    } testCase[] = {{{5, 1, 5}, 3, 22}, {{3, 4, 1, 2}, 4, 25}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: chalk = [5,1,5], k = 22
     *  Output: 0
     *
     *  Input: chalk = [3,4,1,2], k = 25
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: chalk = [");
        for (j = 0; j < testCase[i].chalkSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].chalk[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = chalkReplacer(testCase[i].chalk, testCase[i].chalkSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
