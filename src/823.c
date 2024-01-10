#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numFactoredBinaryTrees(int* arr, int arrSize) {
    int retVal = 0;

    qsort(arr, arrSize, sizeof(int), compareInteger);

    long long* dp = (long long*)malloc(arrSize * sizeof(long long));
    if (dp == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(dp, 0, (arrSize * sizeof(long long)));

    int left, right;
    int i;
    for (i = 0; i < arrSize; i++) {
        dp[i] = 1;

        right = i - 1;
        for (left = 0; left <= right; left++) {
            while ((left <= right) && (((long long)arr[left] * arr[right]) > arr[i])) {
                right--;
            }

            if ((left <= right) && ((long long)arr[left] * arr[right] == arr[i])) {
                if (left == right) {
                    dp[i] = (dp[i] + dp[left] * dp[right]) % MODULO;
                } else {
                    dp[i] = (dp[i] + dp[left] * dp[right] * 2) % MODULO;
                }
            }
        }

        retVal = (retVal + dp[i]) % MODULO;
    }

    free(dp);
    dp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 4}, 2}, {{2, 4, 5, 10}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,4]
     *  Output: 3
     *
     *  Input: arr = [2,4,5,10]
     *  Output: 7
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = numFactoredBinaryTrees(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
