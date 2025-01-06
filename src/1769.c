#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minOperations(char* boxes, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int boxesSize = strlen(boxes);
    pRetVal = (int*)calloc(boxesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    (*returnSize) = boxesSize;

    int ballsToLeft = 0;
    int movesToLeft = 0;
    int ballsToRight = 0;
    int movesToRight = 0;
    int i, j;
    for (i = 0; i < boxesSize; i++) {
        // Left pass
        pRetVal[i] += movesToLeft;
        ballsToLeft += boxes[i] - '0';
        movesToLeft += ballsToLeft;

        // Right pass
        j = boxesSize - 1 - i;
        pRetVal[j] += movesToRight;
        ballsToRight += boxes[j] - '0';
        movesToRight += ballsToRight;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* boxes;
        int returnSize;
    } testCase[] = {{"110", 0}, {"001011", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: boxes = "110"
     *  Output: [1,1,3]
     *
     *  Input: boxes = "001011"
     *  Output: [11,8,5,4,3,4]
     */

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
