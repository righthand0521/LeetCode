#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** cellsInRange(char* s, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = (s[3] - s[0] + 1) * (s[4] - s[1] + 1);
    pRetVal = (char**)malloc((*returnSize) * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    // s.length == 5
    // 'A' <= s[0] <= s[3] <= 'Z'
    // '1' <= s[1] <= s[4] <= '9'
    (*returnSize) = 0;
    int returnColumnSizes = 3;
    char row, col;
    for (row = s[0]; row <= s[3]; ++row) {
        for (col = s[1]; col <= s[4]; ++col) {
            pRetVal[(*returnSize)] = (char*)malloc(returnColumnSizes * sizeof(char));
            if (pRetVal == NULL) {
                perror("malloc");
                for (int i = 0; i < (*returnSize); ++i) {
                    free(pRetVal[i]);
                    pRetVal[i] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[(*returnSize)], 0, (returnColumnSizes * sizeof(char)));
            pRetVal[(*returnSize)][0] = row;
            pRetVal[(*returnSize)][1] = col;
            (*returnSize) += 1;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (8)
    struct testCaseType {
        char s[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"K1:L2", 0}, {"A1:F1", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "K1:L2"
     *  Output: ["K1","K2","L1","L2"]
     *
     *  Input: s = "A1:F1"
     *  Output: ["A1","B1","C1","D1","E1","F1"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s =  \"%s\"\n", testCase[i].s);

        pAnswer = cellsInRange(testCase[i].s, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
