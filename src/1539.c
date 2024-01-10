#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (1)
int findKthPositive(int *arr, int arrSize, int k) {
    int retVal = 0;

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int left = 0;
    int right = arrSize;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (arr[middle] - middle >= k + 1) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = k + left;
#else
    int i;
    for (i = 0; i < arrSize; ++i) {
        ++retVal;
        if (retVal != arr[i]) {
            --i;
            --k;
        }

        if (k == 0) {
            break;
        }
    }

    while (k > 0) {
        ++retVal;
        --k;
    }
#endif

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{2, 3, 4, 7, 11}, 5, 5}, {{1, 2, 3, 4}, 4, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,3,4,7,11], k = 5
     *  Output: 9
     *
     *  Input: arr = [1,2,3,4], k = 2
     *  Output: 6
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = findKthPositive(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
