#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long countSubarrays(int *nums, int numsSize, int k) {
    long long retVal = 0;

    int maxNum = nums[0];  // 1 <= nums.length <= 10^5
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (maxNum < nums[i]) {
            maxNum = nums[i];
        }
    }
    int maxNumWindow = 0;

    int start = 0;
    int end = 0;
    for (end = 0; end < numsSize; ++end) {
        if (nums[end] == maxNum) {
            maxNumWindow++;
        }

        while (maxNumWindow == k) {
            if (nums[start] == maxNum) {
                maxNumWindow--;
            }
            start++;
        }

        retVal += start;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 3, 2, 3, 3}, 5, 2}, {{1, 4, 2, 1}, 4, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,2,3,3], k = 2
     *  Output: 6
     *
     *  Input: nums = [1,4,2,1], k = 3
     *  Output: 0
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = countSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
