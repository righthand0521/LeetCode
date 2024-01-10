#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        (*returnSize) += numsColSize[i];
    }

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    struct pairType {
        int row;
        int col;
    } queue[(*returnSize)];
    int queueHead = 0;
    int queueTail = 0;
    queue[queueTail].row = 0;
    queue[queueTail].col = 0;
    queueTail++;

    (*returnSize) = 0;
    int row, col;
    while (queueHead < queueTail) {
        row = queue[queueHead].row;
        col = queue[queueHead].col;
        queueHead++;
        pRetVal[(*returnSize)++] = nums[row][col];

        if ((col == 0) && (row + 1 < numsSize)) {
            queue[queueTail].row = row + 1;
            queue[queueTail].col = col;
            queueTail++;
        }

        if (col + 1 < numsColSize[row]) {
            queue[queueTail].row = row;
            queue[queueTail].col = col + 1;
            queueTail++;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e2)
#define MAX_COLUMN (int)(1e2)
    struct testCaseType {
        int nums[MAX_ROW][MAX_COLUMN];
        int numsSize;
        int numsColSize[MAX_ROW];
        int returnSize;
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}, 0},
                    {{{1, 2, 3, 4, 5}, {6, 7}, {8}, {9, 10, 11}, {12, 13, 14, 15, 16}}, 5, {5, 2, 1, 3, 5}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,4,2,7,5,3,8,6,9]
     *
     *  Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
     *  Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
     */

    int** pNums = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].numsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].nums[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pNums = (int**)malloc(testCase[i].numsSize * sizeof(int*));
        if (pNums == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].numsSize; ++j) {
            pNums[j] = (int*)malloc(testCase[i].numsColSize[j] * sizeof(int));
            if (pNums[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pNums[k]);
                }
                free(pNums);
                return EXIT_FAILURE;
            }
            memset(pNums[j], 0, (testCase[i].numsColSize[j] * sizeof(int)));
            memcpy(pNums[j], testCase[i].nums[j], (testCase[i].numsColSize[j] * sizeof(int)));
        }
        pAnswer = findDiagonalOrder(pNums, testCase[i].numsSize, testCase[i].numsColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].numsSize; ++j) {
            free(pNums[j]);
        }
        free(pNums);
        pNums = NULL;
    }

    return EXIT_SUCCESS;
}
