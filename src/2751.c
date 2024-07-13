#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions,
                           int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(positionsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (positionsSize * sizeof(int)));

    int i;

    // Sort indices based on their positions
    int indices[positionsSize][2];
    for (i = 0; i < positionsSize; ++i) {
        indices[i][0] = i;
        indices[i][1] = positions[i];
    }
    qsort(indices, positionsSize, sizeof(indices[0]), compareIntArray);

    int stackTop = -1;
    int stack[positionsSize];
    memset(stack, 0, sizeof(stack));
    int currentIndex, topIndex;
    for (i = 0; i < positionsSize; ++i) {
        currentIndex = indices[i][0];

        if (directions[currentIndex] == 'R') {
            stackTop++;
            stack[stackTop] = currentIndex;
            continue;
        }

        while ((stackTop > -1) && (healths[currentIndex] > 0)) {
            // Pop the top robot from the stack for collision check
            topIndex = stack[stackTop];
            stackTop--;

            if (healths[topIndex] > healths[currentIndex]) {
                // Top robot survives, current robot is destroyed
                healths[topIndex] -= 1;
                healths[currentIndex] = 0;
                stackTop++;
                stack[stackTop] = topIndex;
            } else if (healths[topIndex] < healths[currentIndex]) {
                // Current robot survives, top robot is destroyed
                healths[currentIndex] -= 1;
                healths[topIndex] = 0;
            } else {
                // Both robots are destroyed
                healths[currentIndex] = 0;
                healths[topIndex] = 0;
            }
        }
    }

    // Collect surviving robots
    for (i = 0; i < positionsSize; ++i) {
        if (healths[i] > 0) {
            pRetVal[(*returnSize)++] = healths[i];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int positions[MAX_SIZE];
        int positionsSize;
        int healths[MAX_SIZE];
        int healthsSize;
        char directions[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{5, 4, 3, 2, 1}, 5, {2, 17, 9, 15, 10}, 5, "RRRRR", 0},
                    {{3, 5, 2, 6}, 4, {10, 10, 15, 12}, 4, "RLRL", 0},
                    {{1, 2, 5, 6}, 4, {10, 10, 11, 11}, 4, "RLRL", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
     *  Output: [2,17,9,15,10]
     *
     *  Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
     *  Output: [14]
     *
     *  Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
     *  Output: []
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: positions = [");
        for (j = 0; j < testCase[i].positionsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].positions[j]);
        }
        printf("], healths = [");
        for (j = 0; j < testCase[i].healthsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].healths[j]);
        }
        printf("], directions = \"%s\"\n", testCase[i].directions);

        pAnswer = survivedRobotsHealths(testCase[i].positions, testCase[i].positionsSize, testCase[i].healths,
                                        testCase[i].healthsSize, testCase[i].directions, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
