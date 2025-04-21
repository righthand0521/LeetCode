#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfArrays(int* differences, int differencesSize, int lower, int upper) {
    int retVal = 0;

    int minValue = 0;
    int maxValue = 0;
    int currentSum = 0;
    for (int i = 0; i < differencesSize; i++) {
        currentSum += differences[i];
        minValue = fmin(minValue, currentSum);
        maxValue = fmax(maxValue, currentSum);
        if ((maxValue - minValue) > (upper - lower)) {
            return retVal;
        }
    }
    retVal = (upper - lower) - (maxValue - minValue) + 1;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int differences[MAX_SIZE];
        int differencesSize;
        int lower;
        int upper;
    } testCase[] = {{{1, -3, 4}, 3, 1, 6}, {{3, -4, 5, 1, -2}, 5, -4, 5}, {{4, -7, 2}, 3, 3, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: differences = [1,-3,4], lower = 1, upper = 6
     *  Output: 2
     *
     *  Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
     *  Output: 4
     *
     *  Input: differences = [4,-7,2], lower = 3, upper = 6
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: differences = [");
        for (j = 0; j < testCase[i].differencesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].differences[j]);
        }
        printf("], lower = %d, upper = %d\n", testCase[i].lower, testCase[i].upper);

        answer =
            numberOfArrays(testCase[i].differences, testCase[i].differencesSize, testCase[i].lower, testCase[i].upper);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
