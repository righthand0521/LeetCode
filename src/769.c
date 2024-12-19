#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxChunksToSorted(int* arr, int arrSize) {
    int retVal = 0;

    int maxElement = 0;
    int i;
    for (i = 0; i < arrSize; i++) {
        maxElement = fmax(maxElement, arr[i]);
        // All values in range [0, i] belong to the prefix arr[0:i]; a new chunk can be formed
        if (maxElement == i) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{4, 3, 2, 1, 0}, 5}, {{1, 0, 2, 3, 4}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [4,3,2,1,0]
     *  Output: 1
     *
     *  Input: arr = [1,0,2,3,4]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = maxChunksToSorted(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
