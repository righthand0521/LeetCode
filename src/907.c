#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int sumSubarrayMins(int* arr, int arrSize) {
    int retVal = 0;

    int dp[arrSize];
    memset(dp, 0, sizeof(dp));

    int monoStackTop = 0;
    int monoStack[arrSize];
    memset(monoStack, 0, sizeof(monoStack));

    int i, key, value;
    for (i = 0; i < arrSize; ++i) {
        value = arr[i];

        while ((monoStackTop > 0) && (arr[monoStack[monoStackTop - 1]] > value)) {
            monoStackTop--;
        }

        key = i + 1;
        if (monoStackTop != 0) {
            key = i - monoStack[monoStackTop - 1];
        }

        dp[i] = key * value;
        if (monoStackTop != 0) {
            dp[i] += dp[i - key];
        }

        monoStack[monoStackTop++] = i;

        retVal = (retVal + dp[i]) % MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{3, 1, 2, 4}, 4}, {{11, 81, 94, 43, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [3,1,2,4]
     *  Output: 17
     *
     *  Input: arr = [11,81,94,43,3]
     *  Output: 444
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr  = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = sumSubarrayMins(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
