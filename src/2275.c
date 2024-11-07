#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestCombination(int* candidates, int candidatesSize) {
    int retVal = 0;

    // 1 <= candidates[i] <= 10^7 < 2^24
    int maxCount;
    int i, j;
    for (i = 0; i < 24; ++i) {
        maxCount = 0;
        for (j = 0; j < candidatesSize; ++j) {
            if ((candidates[j] & (1 << i)) != 0) {
                maxCount++;
            }
        }
        retVal = fmax(retVal, maxCount);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int candidates[MAX_SIZE];
        int candidatesSize;
    } testCase[] = {{{16, 17, 71, 62, 12, 24, 14}, 7}, {{8, 8}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: candidates = [16,17,71,62,12,24,14]
     *  Output: 4
     *
     *  Input: candidates = [8,8]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: candidates = [");
        for (j = 0; j < testCase[i].candidatesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].candidates[j]);
        }
        printf("]\n");

        answer = largestCombination(testCase[i].candidates, testCase[i].candidatesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
