#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(temperaturesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (temperaturesSize * sizeof(int)));

    int MonotonicStack[temperaturesSize];
    memset(MonotonicStack, 0, sizeof(MonotonicStack));
    int pTop = -1;

    int i;
    for (i = 0; i < temperaturesSize; ++i) {
        while ((pTop != -1) && (temperatures[i] > temperatures[MonotonicStack[pTop]])) {
            pRetVal[MonotonicStack[pTop]] = i - MonotonicStack[pTop];
            MonotonicStack[pTop] = 0;
            --pTop;
        }

        ++pTop;
        MonotonicStack[pTop] = i;
    }
    (*returnSize) = temperaturesSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int temperatures[MAX_SIZE];
        int temperaturesSize;
        int returnSize;
    } testCase[] = {{{73, 74, 75, 71, 69, 72, 76, 73}, 8, 0}, {{30, 40, 50, 60}, 4, 0}, {{30, 60, 90}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: temperatures = [73,74,75,71,69,72,76,73]
     *  Output: [1,1,4,2,1,1,0,0]
     *
     *  Input: temperatures = [30,40,50,60]
     *  Output: [1,1,1,0]
     *
     *  Input: temperatures = [30,60,90]
     *  Output: [1,1,0]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: temperatures = [");
        for (j = 0; j < testCase[i].temperaturesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].temperatures[j]);
        }
        printf("]\n");

        pAnswer = dailyTemperatures(testCase[i].temperatures, testCase[i].temperaturesSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
