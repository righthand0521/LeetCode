#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxSumTrionic(int* nums, int numsSize) {
    long long retVal = LLONG_MIN;

    int p, q, j;
    long long maxSum, currrentSum, res;
    for (int i = 0; i < numsSize; i++) {
        j = i + 1;
        res = 0;

        // first segment
        for (; ((j < numsSize) && (nums[j - 1] < nums[j])); j++);
        p = j - 1;
        if (p == i) {
            continue;
        }

        // second segment
        res += (nums[p] + nums[p - 1]);
        for (; ((j < numsSize) && (nums[j - 1] > nums[j])); j++) {
            res += nums[j];
        }
        q = j - 1;
        if (q == p || q == numsSize - 1 || (nums[j] <= nums[q])) {
            i = q;
            continue;
        }

        // third segment
        res += nums[q + 1];

        // find the maximum sum of the third segment
        maxSum = 0;
        currrentSum = 0;
        for (int k = q + 2; k < numsSize && nums[k] > nums[k - 1]; k++) {
            currrentSum += nums[k];
            maxSum = fmax(maxSum, currrentSum);
        }
        res += maxSum;

        // find the maximum sum of the first segment
        maxSum = 0;
        currrentSum = 0;
        for (int k = p - 2; k >= i; k--) {
            currrentSum += nums[k];
            maxSum = fmax(maxSum, currrentSum);
        }
        res += maxSum;

        // update answer
        retVal = fmax(retVal, res);
        i = q - 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{0, -2, -1, -3, 0, 2, -1}, 7}, {{1, 4, 2, 7}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,-2,-1,-3,0,2,-1]
     *  Output: -4
     *
     *  Input: nums = [1,4,2,7]
     *  Output: 14
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maxSumTrionic(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
