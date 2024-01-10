#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int sumSubarrayMins(int* arr, int arrSize) {
    int retVal = 0;

    int dp[arrSize];
    memset(dp, 0, sizeof(dp));

    int top = 0;
    int monoStack[arrSize];
    memset(monoStack, 0, sizeof(monoStack));

    int i, j;
    for (i = 0; i < arrSize; ++i) {
        while ((top > 0) && (arr[monoStack[top - 1]] > arr[i])) {
            top--;
        }

        j = ((top == 0) ? (i + 1) : (i - monoStack[top - 1]));
        dp[i] = j * arr[i] + ((top == 0) ? (0) : (dp[i - j]));
        monoStack[top++] = i;

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
