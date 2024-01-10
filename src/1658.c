#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(int* nums, int numsSize, int x) {
    int retVal = -1;

    int target = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        target += nums[i];
    }
    target -= x;
    if (target < 0) {
        return retVal;
    }

    /* https://leetcode.cn/problems/minimum-operations-to-reduce-x-to-zero/solutions/485281/shi-yong-hua-dong-chuang-kou-zhao-zhong-jian-zui-c/
     *  sum(fragment of nums) = sum(nums) - x
     *  Example
     *  +-------------------+   +----------------------------+
     *  | sum-x     | x=5   |   | x=10  | sum-x  | x=10      |
     *  | = 11-5    |       |   |       | =30-10 |           |
     *  +-------------------+   +----------------------------+
     *  | 1 | 1 | 4 | 2 | 3 |   | 3 | 2 |   20   | 1 | 1 | 3 |
     *  +-------------------+   +----------------------------+
     */
    int sum = 0;
    int head = 0;
    int tail = 0;
    for (tail = 0; tail < numsSize; ++tail) {
        sum += nums[tail];

        while (sum > target) {
            sum -= nums[head];
            ++head;
        }

        if (sum == target) {
            retVal = fmax(retVal, (tail - head + 1));
        }
    }
    retVal = ((retVal < 0) ? (-1) : (numsSize - retVal));

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int x;
    } testCase[] = {{{1, 1, 4, 2, 3}, 5, 5}, {{5, 6, 7, 8, 9}, 5, 4}, {{3, 2, 20, 1, 1, 3}, 6, 10}, {{1, 1}, 2, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,4,2,3], x = 5
     *  Output: 2
     *
     *  Input: nums = [5,6,7,8,9], x = 4
     *  Output: -1
     *
     *  Input: nums = [3,2,20,1,1,3], x = 10
     *  Output: 5
     *
     *  Input: nums = [1,1], x = 3
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], x = %d\n", testCase[i].x);

        answer = minOperations(testCase[i].nums, testCase[i].numsSize, testCase[i].x);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
