#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestWPI(int* hours, int hoursSize) {
    int retVal = 0;

    int i;

    int prefixSum[hoursSize + 1];
    memset(prefixSum, 0, sizeof(prefixSum));
    int monotonicStack[hoursSize + 1];
    memset(monotonicStack, 0, sizeof(monotonicStack));
    int monotonicStackTop = 0;

    monotonicStack[monotonicStackTop++] = 0;
    prefixSum[0] = 0;
    for (i = 1; i <= hoursSize; ++i) {
        prefixSum[i] = prefixSum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
        if (prefixSum[monotonicStack[monotonicStackTop - 1]] > prefixSum[i]) {
            monotonicStack[monotonicStackTop++] = i;
        }
    }

    for (i = hoursSize; i >= 1; --i) {
        while ((monotonicStackTop != 0) && (prefixSum[monotonicStack[monotonicStackTop - 1]] < prefixSum[i])) {
            retVal = fmax(retVal, i - monotonicStack[monotonicStackTop - 1]);
            --monotonicStackTop;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int hours[MAX_SIZE];
        int hoursSize;
    } testCase[] = {
        {{9, 9, 6, 0, 6, 6, 9}, 7}, {{6, 6, 6}, 3}, {{9, 9, 6, 9, 0, 6, 9, 6, 9}, 9}, {{6, 9, 6}, 3}, {{6, 9, 9}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: hours = [9,9,6,0,6,6,9]
     *  Output: 3
     *
     *  Input: hours = [6,6,6]
     *  Output: 0
     *
     *  Input: hours = [9,9,6,9,0,6,9,6,9]
     *  Output: 9
     *
     *  Input: hours = [6,9,6]
     *  Output: 1
     *
     *  Input: hours = [6,9,9]
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: hours = [");
        for (j = 0; j < testCase[i].hoursSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].hours[j]);
        }
        printf("]\n");

        answer = longestWPI(testCase[i].hours, testCase[i].hoursSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
