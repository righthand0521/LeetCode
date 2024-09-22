#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestRectangleArea(int* heights, int heightsSize) {
    int retVal = 0;

    int i;

    int left[heightsSize];
    int right[heightsSize];
    for (i = 0; i < heightsSize; ++i) {
        left[i] = 0;
        right[i] = heightsSize;
    }

#define STACK_EMPTY (-1)
    int monotonicStackTop = STACK_EMPTY;
    int monotonicStack[heightsSize + 1];
    memset(monotonicStack, 0, sizeof(monotonicStack));

    for (i = 0; i < heightsSize; ++i) {
        while ((monotonicStackTop != STACK_EMPTY) && (heights[monotonicStack[monotonicStackTop]] >= heights[i])) {
            right[monotonicStack[monotonicStackTop]] = i;
            monotonicStack[monotonicStackTop] = 0;
            monotonicStackTop--;
        }

        left[i] = -1;
        if (monotonicStackTop != STACK_EMPTY) {
            left[i] = monotonicStack[monotonicStackTop];
        }

        monotonicStackTop++;
        monotonicStack[monotonicStackTop] = i;
    }

    for (i = 0; i < heightsSize; ++i) {
        retVal = fmax(retVal, (right[i] - left[i] - 1) * heights[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int heights[MAX_SIZE];
        int heightsSize;
    } testCase[] = {{{2, 1, 5, 6, 2, 3}, 6}, {{2, 4}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [2,1,5,6,2,3]
     *  Output: 10
     *
     *  Input: heights = [2,4]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].heights[j]);
        }
        printf("]\n");

        answer = largestRectangleArea(testCase[i].heights, testCase[i].heightsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
