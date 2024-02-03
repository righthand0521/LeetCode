#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSumAfterPartitioning(int* arr, int arrSize, int k) {
    int retVal = 0;

    int dp[arrSize + 1];
    memset(dp, 0, sizeof(dp));

    int maxValue;
    int i, j;
    for (i = 1; i <= arrSize; ++i) {
        maxValue = arr[i - 1];
        for (j = i - 1; ((j >= 0) && (j >= i - k)); --j) {
            dp[i] = fmax(dp[i], dp[j] + maxValue * (i - j));
            if (j > 0) {
                maxValue = fmax(maxValue, arr[j - 1]);
            }
        }
    }

    retVal = dp[arrSize];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{1, 15, 7, 9, 2, 5, 10}, 7, 3}, {{1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3}, 11, 4}, {{1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,15,7,9,2,5,10], k = 3
     *  Output: 84
     *
     *  Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
     *  Output: 83
     *
     *  Input: arr = [1], k = 1
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxSumAfterPartitioning(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
