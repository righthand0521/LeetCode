#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int binarySearch(int** items, int itemsSize, int* itemsColSize, int targetPrice) {
    int retVal = 0;

    int left = 0;
    int right = itemsSize - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (items[middle][0] > targetPrice) {
            right = middle - 1;
        } else {
            retVal = fmax(retVal, items[middle][1]);
            left = middle + 1;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumBeauty(int** items, int itemsSize, int* itemsColSize, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    qsort(items, itemsSize, sizeof(items[0]), compareIntArray);

    int maxBeauty = items[0][1];
    for (int i = 0; i < itemsSize; ++i) {
        maxBeauty = fmax(maxBeauty, items[i][1]);
        items[i][1] = maxBeauty;
    }

    pRetVal = (int*)calloc(queriesSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    for (int i = 0; i < queriesSize; ++i) {
        pRetVal[(*returnSize)++] = binarySearch(items, itemsSize, itemsColSize, queries[i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int items[MAX_SIZE][2];
        int itemsSize;
        int itemsColSize[MAX_SIZE];
        int queries[MAX_SIZE];
        int queriesSize;
        int returnSize;
    } testCase[] = {{{{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}}, 5, {2, 2, 2, 2, 2}, {1, 2, 3, 4, 5, 6}, 6, 0},
                    {{{1, 2}, {1, 2}, {1, 3}, {1, 4}}, 4, {2, 2, 2, 2}, {1}, 1, 0},
                    {{{10, 1000}}, 1, {2}, {5}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: items = [[1,2],[3,2],[2,4],[5,6],[3,5]], queries = [1,2,3,4,5,6]
     *  Output: [2,4,5,5,6,6]
     *
     *  Input: items = [[1,2],[1,2],[1,3],[1,4]], queries = [1]
     *  Output: [4]
     *
     *  Input: items = [[10,1000]], queries = [5]
     *  Output: [0]
     */

    int** pItems = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: items = [");
        for (j = 0; j < testCase[i].itemsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].itemsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].items[j][k]);
            }
            printf("]");
        }
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].queries[j]);
        }
        printf("]\n");

        pItems = (int**)malloc(testCase[i].itemsSize * sizeof(int*));
        if (pItems == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].itemsSize; ++j) {
            pItems[j] = (int*)malloc(testCase[i].itemsColSize[j] * sizeof(int));
            if (pItems[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pItems[k]);
                }
                free(pItems);
                return EXIT_FAILURE;
            }
            memset(pItems[j], 0, (testCase[i].itemsColSize[j] * sizeof(int)));
            memcpy(pItems[j], testCase[i].items[j], (testCase[i].itemsColSize[j] * sizeof(int)));
        }
        pAnswer = maximumBeauty(pItems, testCase[i].itemsSize, testCase[i].itemsColSize, testCase[i].queries,
                                testCase[i].queriesSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].itemsSize; ++j) {
            free(pItems[j]);
        }
        free(pItems);
        pItems = NULL;
    }

    return EXIT_SUCCESS;
}
