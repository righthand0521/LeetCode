#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrix(int m, int n, struct ListNode* head, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    (*returnColumnSizes) = (int*)malloc(m * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (m * sizeof(int)));
    pRetVal = (int**)malloc(m * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < m; ++i) {
        pRetVal[i] = (int*)malloc(n * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], -1, (n * sizeof(int)));
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = m;

    int movement[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int movementIndex = 0;
    int x = 0;
    int y = 0;
    struct ListNode* pCurrent = head;
    while (pCurrent != NULL) {
        pRetVal[x][y] = pCurrent->val;

        x += movement[movementIndex][0];
        y += movement[movementIndex][1];
        // 0 <= Node.val <= 1000
        if ((x < 0) || (y < 0) || (x >= m) || (y >= n) || (pRetVal[x][y] != -1)) {
            x -= movement[movementIndex][0];
            y -= movement[movementIndex][1];
            movementIndex = (movementIndex + 1) % 4;
            x += movement[movementIndex][0];
            y += movement[movementIndex][1];
        }

        pCurrent = pCurrent->next;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int m;
        int n;
        int head[MAX_SIZE];
        int headSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{3, 5, {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0}, 13, 0, NULL}, {1, 4, {0, 1, 2}, 3, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
     *  Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
     *
     *  Input: m = 1, n = 4, head = [0,1,2]
     *  Output: [[0,1,2,-1]]
     */

    struct ListNode* pHead = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        pHead = buildList(testCase[i].head, testCase[i].headSize);
        printf("Input: m = %d, n = %d", testCase[i].m, testCase[i].n);
        printf(", head = [");
        printList(pHead);
        printf("]\n");

        pAnswer =
            spiralMatrix(testCase[i].m, testCase[i].n, pHead, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
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
        freeListNode(pHead);
        pHead = NULL;
    }

    return EXIT_SUCCESS;
}
