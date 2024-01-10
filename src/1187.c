#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF (int)(0x3f3f3f3f)  // 0 <= arr1[i], arr2[i] <= 10^9
int compareInteger(const void *n1, const void *n2) {
    // ascending order
    return (*(int *)n1 > *(int *)n2);
}
int binarySearch(int *arr, int left, int right, int val) {
    int retVal = right + 1;

    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;

        if (arr[middle] > val) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return retVal;
}
int makeArrayIncreasing(int *arr1, int arr1Size, int *arr2, int arr2Size) {
    int retVal = -1;

    int i, j;

    qsort(arr2, arr2Size, sizeof(int), compareInteger);
    int arr2Idx = 0;
    for (i = 0; i < arr2Size; i++) {
        if ((i == 0) || (arr2[i] != arr2[i - 1])) {
            arr2[arr2Idx++] = arr2[i];
        }
    }

    int dpRowSize = arr1Size + 1;
    int dpColSize = fmin(arr1Size, arr2Idx) + 1;
    int dp[dpRowSize][dpColSize];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = -1;

    int index;
    for (i = 1; i <= arr1Size; i++) {
        for (j = 0; j <= fmin(i, arr2Idx); j++) {
            if (arr1[i - 1] > dp[i - 1][j]) {
                dp[i][j] = arr1[i - 1];
            }

            if ((j > 0) && (dp[i - 1][j - 1] != INF)) {
                index = binarySearch(arr2, j - 1, arr2Idx - 1, dp[i - 1][j - 1]);
                if (index != arr2Idx) {
                    dp[i][j] = fmin(dp[i][j], arr2[index]);
                }
            }

            if ((i == arr1Size) && (dp[i][j] != INF)) {
                retVal = j;
                return retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (2000)
    struct testCaseType {
        int arr1[MAX_SIZE];
        int arr1Size;
        int arr2[MAX_SIZE];
        int arr2Size;
    } testCase[] = {{{1, 5, 3, 6, 7}, 5, {1, 3, 2, 4}, 4},
                    {{1, 5, 3, 6, 7}, 5, {4, 3, 1}, 3},
                    {{1, 5, 3, 6, 7}, 5, {1, 6, 3, 3}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
     *  Output: 1
     *
     *  Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
     *  Output: 2
     *
     *  Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr1 = [");
        for (j = 0; j < testCase[i].arr1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr1[j]);
        }
        printf("], arr2 = [");
        for (j = 0; j < testCase[i].arr2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr2[j]);
        }
        printf("]\n");

        answer = makeArrayIncreasing(testCase[i].arr1, testCase[i].arr1Size, testCase[i].arr2, testCase[i].arr2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
