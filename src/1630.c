#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkArithmeticSubarrays(int* nums, int numsSize, int* l, int lSize, int* r, int rSize, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = lSize;

    pRetVal = (bool*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    int subarray[numsSize];
    int left, right, subarraySize;
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = true;

        left = l[i];
        right = r[i] + 1;
        subarraySize = right - left;
        memset(subarray, 0, sizeof(subarray));
        memcpy(subarray, nums + left, subarraySize * sizeof(int));

        qsort(subarray, subarraySize, sizeof(int), compareInteger);
        for (j = 1; j < (subarraySize - 1); ++j) {
            if ((subarray[j] - subarray[j - 1]) != (subarray[j + 1] - subarray[j])) {
                pRetVal[i] = false;
                break;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int l[MAX_SIZE];
        int lSize;
        int r[MAX_SIZE];
        int rSize;
        int returnSize;
    } testCase[] = {
        {{4, 6, 5, 9, 3, 7}, 6, {0, 0, 2}, 3, {2, 3, 5}, 3},
        {{-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10}, 11, {0, 1, 6, 4, 8, 7}, 6, {4, 4, 9, 7, 9, 10}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
     *  Output: [true,false,true]
     *
     *  Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]
     *  Output: [false,true,false,false,true,true]
     */

    int i, j;
    bool* pAnswer = NULL;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], l = [");
        for (j = 0; j < testCase[i].lSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].l[j]);
        }
        printf("], r = [");
        for (j = 0; j < testCase[i].rSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].r[j]);
        }
        printf("]\n");

        pAnswer = checkArithmeticSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].l, testCase[i].lSize,
                                           testCase[i].r, testCase[i].rSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", ((pAnswer[j] == true) ? "true" : "false"));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
