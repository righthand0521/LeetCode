#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long getCost(int base, int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal += ((long long)(abs(base - nums[i])) * cost[i]);
    }

    return retVal;
}
long long minCost(int* nums, int numsSize, int* cost, int costSize) {
    long long retVal = 0;

    retVal = getCost(nums[0], nums, numsSize, cost, costSize);
    int left = nums[0];
    int right = nums[0];
    int i;
    for (i = 0; i < numsSize; ++i) {
        left = (left < nums[i]) ? (left) : (nums[i]);
        right = (right > nums[i]) ? (right) : (nums[i]);
    }

    int middle;
    long long costLeft, costRight;
    while (left < right) {
        middle = (left + right) / 2;

        costLeft = getCost(middle, nums, numsSize, cost, costSize);
        costRight = getCost((middle + 1), nums, numsSize, cost, costSize);
        retVal = fmin(costLeft, costRight);

        if (costLeft > costRight) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int cost[MAX_SIZE];
        int costSize;
    } testCase[] = {{{1, 3, 5, 2}, 4, {2, 3, 1, 14}, 4}, {{2, 2, 2, 2, 2}, 5, {4, 2, 8, 1, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,5,2], cost = [2,3,1,14]
     *  Output: 8
     *
     *  Input: nums = [2,2,2,2,2], cost = [4,2,8,1,3]
     *  Output: 0
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], cost = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cost[j]);
        }
        printf("]\n");

        answer = minCost(testCase[i].nums, testCase[i].numsSize, testCase[i].cost, testCase[i].costSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
