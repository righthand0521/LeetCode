#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sequenceType {
    int index;
    int value;
};
int compareStructByValue(const void *a1, const void *a2) {
    struct sequenceType *p1 = (struct sequenceType *)a1;
    struct sequenceType *p2 = (struct sequenceType *)a2;

    if (p1->value == p2->value) {
        return (p1->index > p2->index);
    }

    // descending order
    return (p1->value < p2->value);
}
int compareStructByIndex(const void *a1, const void *a2) {
    struct sequenceType *p1 = (struct sequenceType *)a1;
    struct sequenceType *p2 = (struct sequenceType *)a2;

    // ascending order
    return (p1->index > p2->index);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    struct sequenceType sequence[numsSize];
    memset(sequence, 0, sizeof(sequence));
    int i;
    for (i = 0; i < numsSize; ++i) {
        sequence[i].index = i;
        sequence[i].value = nums[i];
    }
    qsort(sequence, numsSize, sizeof(struct sequenceType), compareStructByValue);
    qsort(sequence, k, sizeof(struct sequenceType), compareStructByIndex);

    pRetVal = (int *)malloc(k * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (k * sizeof(int)));
    for (i = 0; i < k; ++i) {
        pRetVal[i] = sequence[i].value;
        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
        int returnSize;
    } testCase[] = {{{2, 1, 3, 3}, 4, 2, 0}, {{-1, -2, 3, 4}, 4, 3, 0}, {{3, 4, 3, 3}, 4, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,3,3], k = 2
     *  Output: [3,3]
     *
     *  Input: nums = [-1,-2,3,4], k = 3
     *  Output: [-1,3,4]
     *
     *  Input: nums = [3,4,3,3], k = 2
     *  Output: [3,4]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pAnswer = maxSubsequence(testCase[i].nums, testCase[i].numsSize, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
