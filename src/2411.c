#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIT (31)  // 0 <= nums[i] <= 10^9
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestSubarrays(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(numsSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int pos[MAX_BIT];
    memset(pos, -1, sizeof(pos));
    for (int i = numsSize - 1; i >= 0; --i) {
        int j = i;
        for (int bit = 0; bit < MAX_BIT; ++bit) {
            if (!(nums[i] & (1 << bit))) {
                if (pos[bit] != -1) {
                    j = fmax(j, pos[bit]);
                }
            } else {
                pos[bit] = i;
            }
        }
        pRetVal[i] = j - i + 1;
    }
    (*returnSize) = numsSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 0, 2, 1, 3}, 5, 0}, {{1, 2}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,0,2,1,3]
     *  Output: [3,3,2,2,1]
     *
     *  Input: nums = [1,2]
     *  Output: [2,1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = smallestSubarrays(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
