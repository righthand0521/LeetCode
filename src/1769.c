#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperations(char* boxes, int* returnSize) {
    int* pRetVal = NULL;

    // malloc return array
    (*returnSize) = strlen(boxes);
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    // count moving steps
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        for (j = 0; j < (*returnSize); ++j) {
            if ((i == j) || (boxes[j] == '0')) {
                continue;
            }
            pRetVal[i] += (abs(j - i));
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* boxes;
        int returnSize;
    } testCase[] = {{"110", 0}, {"001011", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: boxes = \"%s\"\n", testCase[i].boxes);

        pAnswer = minOperations(testCase[i].boxes, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
