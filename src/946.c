#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize) {
    bool retVal = false;

    int stack[pushedSize];
    memset(stack, -1, sizeof(stack));  // 0 <= pushed[i] <= 1000
    int stackHead = 0;

    int poppedIdx = 0;
    int i;
    for (i = 0; i < pushedSize; ++i) {
        stack[stackHead++] = pushed[i];

        while (poppedIdx < poppedSize) {
            if ((stackHead > 0) && (stack[stackHead - 1] == popped[poppedIdx])) {
                stack[--stackHead] = -1;
                ++poppedIdx;
            } else {
                break;
            }
        }
    }

    if (stackHead == 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int pushed[MAX_SIZE];
        int pushedSize;
        int popped[MAX_SIZE];
        int poppedSize;
    } testCase[] = {
        {{1, 2, 3, 4, 5}, 5, {4, 5, 3, 2, 1}, 5}, {{1, 2, 3, 4, 5}, 5, {4, 3, 5, 1, 2}, 5}, {{1, 0}, 2, {1, 0}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
     *  Output: true
     *
     *  Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
     *  Output: false
     *
     *  Input: pushed = [1, 0], popped = [1, 0]
     *  Output: true
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pushed = [");
        for (j = 0; j < testCase[i].pushedSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].pushed[j]);
        }
        printf("], popped = [");
        for (j = 0; j < testCase[i].poppedSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].popped[j]);
        }
        printf("]\n");

        answer = validateStackSequences(testCase[i].pushed, testCase[i].pushedSize, testCase[i].popped,
                                        testCase[i].poppedSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
