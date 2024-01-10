#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findSpecialInteger(int* arr, int arrSize) {
    int retVal = 0;

    int shift = arrSize >> 2;  // there is exactly one integer in the array that occurs more than 25% of the time
    int i;
    for (i = 0; i < (arrSize - shift); ++i) {
        if (arr[i] != arr[i + shift]) {
            continue;
        }
        retVal = arr[i];
        break;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 2, 2, 6, 6, 6, 6, 7, 10}, 9}, {{1, 1}, 2}, {{1, 1, 2, 2, 3, 3, 3, 3}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,2,6,6,6,6,7,10]
     *  Output: 6
     *
     *  Input: arr = [1,1]
     *  Output: 1
     *
     *  Input: [1,1,2,2,3,3,3,3]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = findSpecialInteger(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
