#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minNumberOperations(int* target, int targetSize) {
    int retVal = 0;

    retVal = target[0];
    for (int i = 1; i < targetSize; ++i) {
        retVal += fmax(target[i] - target[i - 1], 0);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int target[MAX_SIZE];
        int targetSize;
    } testCase[] = {{{1, 1, 2}, 3}, {{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: target = [1,2,3,2,1]
     *  Output: 3
     *
     *  Input: target = [3,1,1,2]
     *  Output: 4
     *
     *  Input: target = [3,1,5,4,2]
     *  Output: 7
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: target = [");
        for (j = 0; j < testCase[i].targetSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].target[j]);
        }
        printf("]\n");

        answer = minNumberOperations(testCase[i].target, testCase[i].targetSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
