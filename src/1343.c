#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int retVal = 0;

    long long prefixSum = 0;  // 1 <= arr.length <= 10^5, 1 <= arr[i] <= 10^4, 1 <= k <= arr.length
    int i;
    for (i = 0; i < (k - 1); ++i) {
        prefixSum += arr[i];
    }

    for (i = (k - 1); i < arrSize; ++i) {
        prefixSum += arr[i];
        if ((prefixSum / k) >= threshold) {
            ++retVal;
        }

        prefixSum -= arr[i - k + 1];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
        int threshold;
    } testCase[] = {{{2, 2, 2, 2, 5, 5, 5, 8}, 8, 3, 4}, {{11, 13, 17, 23, 29, 31, 7, 5, 2, 3}, 10, 3, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
     *  Output: 3
     *
     *  Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
     *  Output: 6
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d, threshold = %d\n", testCase[i].k, testCase[i].threshold);

        answer = numOfSubarrays(testCase[i].arr, testCase[i].arrSize, testCase[i].k, testCase[i].threshold);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
