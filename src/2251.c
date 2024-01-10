#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int binarySearch(int* arr, int left, int right, int val) {
    int retVal = right + 1;

    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;

        if (arr[middle] > val) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fullBloomFlowers(int** flowers, int flowersSize, int* flowersColSize, int* people, int peopleSize,
                      int* returnSize) {
    int* pRetVal = NULL;

    int starts[flowersSize];
    memset(starts, 0, sizeof(starts));
    int ends[flowersSize];
    memset(ends, 0, sizeof(ends));
    int i;
    for (i = 0; i < flowersSize; ++i) {
        starts[i] = flowers[i][0];
        ends[i] = flowers[i][1] + 1;
    }
    qsort(starts, flowersSize, sizeof(int), compareInteger);
    qsort(ends, flowersSize, sizeof(int), compareInteger);

    (*returnSize) = 0;
    pRetVal = (int*)malloc(peopleSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int x, y;
    for (i = 0; i < peopleSize; ++i) {
        x = binarySearch(starts, 0, flowersSize - 1, people[i]);
        y = binarySearch(ends, 0, flowersSize - 1, people[i]);
        pRetVal[i] = x - y;
        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int flowers[MAX_SIZE][2];
        int flowersSize;
        int flowersColSize[MAX_SIZE];
        int people[MAX_SIZE];
        int peopleSize;
        int returnSize;
    } testCase[] = {{{{1, 6}, {3, 7}, {9, 12}, {4, 13}}, 4, {2, 2, 2, 2}, {2, 3, 7, 11}, 4, 0},
                    {{{1, 10}, {3, 3}}, 2, {2, 2}, {3, 3, 2}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: flowers = [[1,6],[3,7],[9,12],[4,13]], poeple = [2,3,7,11]
     *  Output: [1,2,2,2]
     *
     *  Input: flowers = [[1,10],[3,3]], poeple = [3,3,2]
     *  Output: [2,2,1]
     */

    int** pFlowers = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: flowers = [");
        for (j = 0; j < testCase[i].flowersSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].flowersColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].flowers[j][k]);
            }
            printf("]");
        }
        printf("], poeple = [");
        for (j = 0; j < testCase[i].peopleSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].people[j]);
        }
        printf("]\n");

        pFlowers = (int**)malloc(testCase[i].flowersSize * sizeof(int*));
        if (pFlowers == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].flowersSize; ++j) {
            pFlowers[j] = (int*)malloc(testCase[i].flowersColSize[j] * sizeof(int));
            if (pFlowers[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pFlowers[k]);
                }
                free(pFlowers);
                return EXIT_FAILURE;
            }
            memset(pFlowers[j], 0, (testCase[i].flowersColSize[j] * sizeof(int)));
            memcpy(pFlowers[j], testCase[i].flowers[j], (testCase[i].flowersColSize[j] * sizeof(int)));
        }
        pAnswer = fullBloomFlowers(pFlowers, testCase[i].flowersSize, testCase[i].flowersColSize, testCase[i].people,
                                   testCase[i].peopleSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].flowersSize; ++j) {
            free(pFlowers[j]);
        }
        free(pFlowers);
        pFlowers = NULL;
    }

    return EXIT_SUCCESS;
}
