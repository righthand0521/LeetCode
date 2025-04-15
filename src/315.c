#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Update(int* c, int discretizationIndex, int pos) {
    while (pos < discretizationIndex) {
        c[pos] += 1;
        pos += (pos & (-pos));
    }
}
int Query(int* c, int pos) {
    int retVal = 0;

    while (pos > 0) {
        retVal += c[pos];
        pos -= (pos & (-pos));
    }

    return retVal;
}
int lowerBound(int* a, int discretizationIndex, int x) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = discretizationIndex;
    while (left < right) {
        middle = (left + right) >> 1;
        if (a[middle] < x) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int Discretization(int* a, int* nums, int numsSize) {
    int retVal = 0;

    memcpy(a, nums, sizeof(int) * numsSize);
    qsort(a, numsSize, sizeof(int), compareInteger);

    for (int i = 1; i < numsSize; i++) {
        if (a[i] > a[retVal]) {
            a[++retVal] = a[i];
        }
    }
    retVal += 1;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int* a = (int*)calloc(numsSize, sizeof(int));
    if (a == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int discretizationIndex = Discretization(a, nums, numsSize);

    int* c = (int*)calloc(numsSize + 1, sizeof(int));
    if (c == NULL) {
        perror("calloc");
        free(a);
        return pRetVal;
    }
    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        free(a);
        free(c);
        return pRetVal;
    }
    for (int i = numsSize - 1; i >= 0; --i) {
        int id = lowerBound(a, discretizationIndex, nums[i]) + 1;
        pRetVal[i] = Query(c, id - 1);
        Update(c, discretizationIndex + 1, id);
    }
    (*returnSize) = numsSize;

    // Free allocated memory
    free(a);
    free(c);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{5, 2, 6, 1}, 4, 0}, {{-1}, 1, 0}, {{-1, -1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,2,6,1]
     *  Output: [2,1,1,0]
     *
     *  Input: nums = [-1]
     *  Output: [0]
     *
     *  Input: nums = [-1,-1]
     *  Output: [0,0]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = countSmaller(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
