#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    int retVal = a;

    if (b != 0) {
        retVal = gcd(b, a % b);
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, numsSize * sizeof(int));

    int num, last, g;
    for (int i = 0; i < numsSize; i++) {
        num = nums[i];
        while ((*returnSize) > 0) {
            last = pRetVal[(*returnSize) - 1];
            g = gcd(last, num);
            if (g > 1) {
                num = last / g * num;
                (*returnSize)--;
            } else {
                break;
            }
        }
        pRetVal[(*returnSize)++] = num;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{6, 4, 3, 2, 7, 6, 2}, 7, 0}, {{2, 2, 1, 1, 3, 3, 3}, 7, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [6,4,3,2,7,6,2]
     *  Output: [12,7,6]
     *
     *  Input: nums = [2,2,1,1,3,3,3]
     *  Output: [2,1,1,3]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = replaceNonCoprimes(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
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
