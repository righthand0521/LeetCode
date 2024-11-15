#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findLengthOfShortestSubarray(int* arr, int arrSize) {
    int retVal = 0;

    int right = arrSize - 1;
    while ((right > 0) && (arr[right] >= arr[right - 1])) {
        right--;
    }
    retVal = right;

    int left = 0;
    while ((left < right) && ((left == 0) || (arr[left - 1] <= arr[left]))) {
        while ((right < arrSize) && (arr[left] > arr[right])) {
            right++;
        }
        retVal = fmin(retVal, right - left - 1);
        left++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 2, 3, 10, 4, 2, 3, 5}, 8}, {{5, 4, 3, 2, 1}, 5}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,3,10,4,2,3,5]
     *  Output: 3
     *
     *  Input: arr = [5,4,3,2,1]
     *  Output: 4
     *
     *  Input: arr = [1,2,3]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = findLengthOfShortestSubarray(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
