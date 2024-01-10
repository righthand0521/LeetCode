#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long countSubarrays(int *nums, int numsSize, int minK, int maxK) {
    long long retVal = 0;

    /* Ref
     *  https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/2708099/java-c-python-sliding-window-with-explanation/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895734/fen-xi-ding-jie-zi-shu-zu-de-xing-zhi-yi-qusi/
     *  https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/solutions/1895713/jian-ji-xie-fa-pythonjavacgo-by-endlessc-gag2/
     */
    long long badIdx = -1;
    long long minIdx = -1;
    long long maxIdx = -1;
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] < minK) || (nums[i] > maxK)) {
            badIdx = i;
        }

        if (nums[i] == minK) {
            minIdx = i;
        }

        if (nums[i] == maxK) {
            maxIdx = i;
        }

        retVal += fmax(0, fmin(minIdx, maxIdx) - badIdx);
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int minK;
        int maxK;
    } testCase[] = {{{1, 3, 5, 2, 7, 5}, 6, 1, 5}, {{1, 1, 1, 1}, 4, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example 1:
     *  Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
     *  Output: 2
     *
     *  Input: nums = [1,1,1,1], minK = 1, maxK = 1
     *  Output: 10
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], minK = %d, maxK = %d\n", testCase[i].minK, testCase[i].maxK);

        answer = countSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].minK, testCase[i].maxK);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
