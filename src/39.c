#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
void backtracking(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes,
                  int** answer, int* combine, int* combineSize, int idx) {
    if (idx == candidatesSize) {
        return;
    }

    int* pTmp = NULL;
    if (target == 0) {
        pTmp = (int*)malloc((*combineSize) * sizeof(int));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, ((*combineSize) * sizeof(int)));
        memcpy(pTmp, combine, ((*combineSize) * sizeof(int)));
        answer[(*returnSize)] = pTmp;
        (*returnColumnSizes)[(*returnSize)++] = (*combineSize);
        return;
    }

    backtracking(candidates, candidatesSize, target, returnSize, returnColumnSizes, answer, combine, combineSize,
                 idx + 1);
    if (target - candidates[idx] >= 0) {
        combine[(*combineSize)++] = candidates[idx];
        backtracking(candidates, candidatesSize, target - candidates[idx], returnSize, returnColumnSizes, answer,
                     combine, combineSize, idx);
        (*combineSize)--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = 0;
#define MAX_RETURNSIZE (1000)
    (*returnColumnSizes) = (int*)malloc(MAX_RETURNSIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_RETURNSIZE * sizeof(int)));

    pRetVal = (int**)malloc(MAX_RETURNSIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    //
    if (candidatesSize == 0) {
        return pRetVal;
    }

    qsort(candidates, candidatesSize, sizeof(int), compareInteger);
    if (candidates[0] > target) {
        return pRetVal;
    }

#define MAX_RETURNCOLUMNSIZES (int)(40 / 2 + 4)  // 2 <= candidates[i] <= 40, 1 <= target <= 40
    int combineSize = 0;
    int combine[MAX_RETURNCOLUMNSIZES];
    memset(combine, 0, sizeof(combine));
    backtracking(candidates, candidatesSize, target, returnSize, returnColumnSizes, pRetVal, combine, &combineSize, 0);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int candidates[MAX_SIZE];
        int candidatesSize;
        int target;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{2, 3, 6, 7}, 4, 7, 0, NULL}, {{2, 3, 5}, 3, 8, 0, NULL}, {{2}, 1, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: candidates = [2,3,6,7], target = 7
     *  Output: [[2,2,3],[7]]
     *
     *  Input: candidates = [2,3,5], target = 8
     *  Output: [[2,2,2,2],[2,3,3],[3,5]]
     *
     *  Input: candidates = [2], target = 1
     *  Output: []
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: candidates = [");
        for (j = 0; j < testCase[i].candidatesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].candidates[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = combinationSum(testCase[i].candidates, testCase[i].candidatesSize, testCase[i].target,
                                 &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
