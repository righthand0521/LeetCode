#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int rob(int* nums, int numSize) {
    int retVal = 0;

    int first = nums[0];
    int second = MAX(nums[0], nums[1]);
    int temp;
    int i;
    for (i = 2; i < numSize; ++i) {
        temp = second;
        second = MAX(first + nums[i], second);
        first = temp;
    }
    retVal = second;

    return retVal;
}
int deleteAndEarn(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 1) {
        retVal = nums[0];
        return retVal;
    }

    /* transfer Input Array nums[] to House Robber Input Array
     *  For example, nums = [2,2,3,3,3,4].
     *  Transfer to House Robber Input Array: [0, 0, 4, 9, 4]
     */
    int HouseRobberSize = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        HouseRobberSize = MAX(HouseRobberSize, nums[i]);
    }
    HouseRobberSize += 1;
    int HouseRobber[HouseRobberSize];
    memset(HouseRobber, 0, sizeof(HouseRobber));
    for (i = 0; i < numsSize; ++i) {
        HouseRobber[nums[i]] += nums[i];
    }

    /* 198. House Robber
     *  https://leetcode.com/problems/house-robber
     */
    retVal = rob(HouseRobber, HouseRobberSize);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 4, 2}, 3}, {{2, 2, 3, 3, 3, 4}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = deleteAndEarn(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
