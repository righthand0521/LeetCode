#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(const int *seq, int seqSize, int target) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = seqSize;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (seq[middle] >= target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
int *getLISArray(const int *nums, int numsSize) {
    int *pRetVal = NULL;

    pRetVal = (int *)malloc(numsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    for (i = 0; i < numsSize; i++) {
        pRetVal[i] = 1;
    }

    int index;
    int seq[numsSize];
    int pos = 0;
    for (i = 0; i < numsSize; ++i) {
        index = binarySearch(seq, pos, nums[i]);
        if (index == pos) {
            seq[pos++] = nums[i];
            pRetVal[i] = pos;
        } else {
            seq[index] = nums[i];
            pRetVal[i] = index + 1;
        }
    }

    return pRetVal;
}
void reverse(int *nums, int numsSize) {
    int tmp;
    int i, j;
    for (i = 0, j = numsSize - 1; i < j; i++, j--) {
        tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
int minimumMountainRemovals(int *nums, int numsSize) {
    int retVal = 0;

    int *pre = getLISArray(nums, numsSize);
    if (pre == NULL) {
        free(pre);
        pre = NULL;
        return retVal;
    }
    reverse(nums, numsSize);

    int *suf = getLISArray(nums, numsSize);
    if (suf == NULL) {
        return retVal;
    }
    reverse(suf, numsSize);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((pre[i] > 1) && (suf[i] > 1)) {
            retVal = fmax(retVal, pre[i] + suf[i] - 1);
        }
    }
    retVal = numsSize - retVal;

    //
    free(pre);
    pre = NULL;
    free(suf);
    suf = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 1}, 3}, {{2, 1, 1, 5, 6, 2, 3, 1}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,1]
     *  Output: 0
     *
     *  Input: nums = [2,1,1,5,6,2,3,1]
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumMountainRemovals(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
