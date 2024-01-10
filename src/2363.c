#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE (0)
#define SORT (1)
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    return (p1[0] > p2[0]);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeSimilarItems(int** items1, int items1Size, int* items1ColSize, int** items2, int items2Size,
                        int* items2ColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    // malloc return value
    (*returnSize) = items1Size + items2Size;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

#if (HASH_TABLE)
    printf("HASH_TABLE\n");

#elif (SORT)
    printf("SORT\n");

    // sort items1 and items2
    qsort(items1, items1Size, sizeof(int*), compareIntArray);
    qsort(items2, items2Size, sizeof(int*), compareIntArray);

    // merge items1 and items2
    int i;
    (*returnSize) = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < items1Size) && (idx2 < items2Size)) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        if (items1[idx1][0] == items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items1[idx1][0];
            pRetVal[(*returnSize)][1] = items1[idx1][1] + items2[idx2][1];
            ++idx1;
            ++idx2;
        } else if (items1[idx1][0] < items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items1[idx1][0];
            pRetVal[(*returnSize)][1] = items1[idx1][1];
            ++idx1;
        } else if (items1[idx1][0] > items2[idx2][0]) {
            pRetVal[(*returnSize)][0] = items2[idx2][0];
            pRetVal[(*returnSize)][1] = items2[idx2][1];
            ++idx2;
        }

        ++(*returnSize);
    }
    while (idx1 < items1Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = items1[idx1][0];
        pRetVal[(*returnSize)][1] = items1[idx1][1];
        ++idx1;

        ++(*returnSize);
    }
    while (idx2 < items2Size) {
        (*returnColumnSizes)[(*returnSize)] = 2;
        pRetVal[(*returnSize)] = (int*)malloc(((*returnColumnSizes)[(*returnSize)]) * sizeof(int));
        if (pRetVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[(*returnSize)][0] = items2[idx2][0];
        pRetVal[(*returnSize)][1] = items2[idx2][1];
        ++idx2;

        ++(*returnSize);
    }
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int items1[MAX_SIZE][2];
        int items1Size;
        int items1ColSize[MAX_SIZE];
        int items2[MAX_SIZE][2];
        int items2Size;
        int items2ColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 1}, {4, 5}, {3, 8}}, 3, {2, 2, 2}, {{3, 1}, {1, 5}}, 2, {2, 2}, 0, NULL},
                    {{{1, 1}, {3, 2}, {2, 3}}, 3, {2, 2, 2}, {{2, 1}, {3, 2}, {1, 3}}, 3, {2, 2, 2}, 0, NULL},
                    {{{1, 1}, {2, 2}}, 2, {2, 2}, {{7, 1}, {2, 2}, {1, 4}}, 3, {2, 2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
     *  Output: [[1,6],[3,9],[4,5]]
     *
     *  Input: items1 = [[1,1],[3,2],[2,3]], items2 = [[2,1],[3,2],[1,3]]
     *  Output: [[1,4],[2,4],[3,4]]
     *
     *  Input: items1 = [[1,3],[2,2]], items2 = [[7,1],[2,2],[1,4]]
     *  Output: [[1,7],[2,4],[7,1]]
     */

    int** pItems1 = NULL;
    int** pItems2 = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: items1 = [");
        for (j = 0; j < testCase[i].items1Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].items1ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].items1[j][k]);
            }
            printf("]");
        }
        printf("], items2 = [");
        for (j = 0; j < testCase[i].items2Size; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].items2ColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].items2[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pItems1 = (int**)malloc(testCase[i].items1Size * sizeof(int*));
        if (pItems1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].items1Size; ++j) {
            pItems1[j] = (int*)malloc(testCase[i].items1ColSize[j] * sizeof(int));
            if (pItems1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pItems1[k]) {
                        free(pItems1[k]);
                    }
                }
                free(pItems1);
                pItems1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pItems1[j], 0, testCase[i].items1ColSize[j] * sizeof(int));
            memcpy(pItems1[j], testCase[i].items1[j], testCase[i].items1ColSize[j] * sizeof(int));
        }
        pItems2 = (int**)malloc(testCase[i].items2Size * sizeof(int*));
        if (pItems2 == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].items1Size; ++j) {
                if (pItems1[j]) {
                    free(pItems1[j]);
                    pItems1[j] = NULL;
                }
            }
            free(pItems1);
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].items2Size; ++j) {
            pItems2[j] = (int*)malloc(testCase[i].items2ColSize[j] * sizeof(int));
            if (pItems2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pItems2[k]) {
                        free(pItems2[k]);
                    }
                }
                free(pItems2);
                pItems2 = NULL;
                for (j = 0; j < testCase[i].items1Size; ++j) {
                    if (pItems1[j]) {
                        free(pItems1[j]);
                        pItems1[j] = NULL;
                    }
                }
                free(pItems1);
                return EXIT_FAILURE;
            }
            memset(pItems2[j], 0, testCase[i].items2ColSize[j] * sizeof(int));
            memcpy(pItems2[j], testCase[i].items2[j], testCase[i].items2ColSize[j] * sizeof(int));
        }

        pAnswer = mergeSimilarItems(pItems1, testCase[i].items1Size, testCase[i].items1ColSize, pItems2,
                                    testCase[i].items2Size, testCase[i].items2ColSize, &testCase[i].returnSize,
                                    &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].items1Size; ++j) {
            if (pItems1[j]) {
                free(pItems1[j]);
                pItems1[j] = NULL;
            }
        }
        free(pItems1);
        pItems1 = NULL;
        for (j = 0; j < testCase[i].items2Size; ++j) {
            if (pItems2[j]) {
                free(pItems2[j]);
                pItems2[j] = NULL;
            }
        }
        free(pItems2);
        pItems2 = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
