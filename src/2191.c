#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortJumbled(int *mapping, int mappingSize, int *nums, int numsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int storePairs[numsSize][2];
    memset(storePairs, 0, sizeof(storePairs));
    int num, mappedValue, shift;
    int idx;
    for (idx = 0; idx < numsSize; ++idx) {
        num = nums[idx];
        if (num == 0) {
            storePairs[idx][0] = mapping[num];
            storePairs[idx][1] = idx;
            continue;
        }

        mappedValue = 0;
        shift = 1;
        while (num > 0) {
            mappedValue += (mapping[num % 10] * shift);
            num /= 10;
            shift *= 10;
        }
        storePairs[idx][0] = mappedValue;
        storePairs[idx][1] = idx;
    }

    qsort(storePairs, numsSize, sizeof(storePairs[0]), compareIntArray);

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (numsSize * sizeof(int)));
    for (idx = 0; idx < numsSize; ++idx) {
        pRetVal[idx] = nums[storePairs[idx][1]];
        (*returnSize) += 1;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(3 * 10000)
    struct testCaseType {
        int mapping[10];
        int mappingSize;
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{8, 9, 4, 0, 2, 1, 3, 5, 7, 6}, 10, {991, 338, 38}, 3, 0},
                    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10, {789, 456, 123}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
     *  Output: [338,38,991]
     *
     *  Input: mapping = [0,1,2,3,4,5,6,7,8,9], nums = [789,456,123]
     *  Output: [123,456,789]
     */

    int *pAnswer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mapping = [");
        for (j = 0; j < testCase[i].mappingSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].mapping[j]);
        }
        printf("], nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = sortJumbled(testCase[i].mapping, testCase[i].mappingSize, testCase[i].nums, testCase[i].numsSize,
                              &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
