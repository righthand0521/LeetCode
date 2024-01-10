#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int peakIndexInMountainArray(int* arr, int arrSize) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = arrSize - 1;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (arr[middle] < arr[middle + 1]) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{0, 1, 0}, 3}, {{0, 2, 1, 0}, 4}, {{0, 10, 5, 2}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [0,1,0]
     *  Output: 1
     *
     *  Input: arr = [0,2,1,0]
     *  Output: 1
     *
     *  Input: arr = [0,10,5,2]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = peakIndexInMountainArray(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
