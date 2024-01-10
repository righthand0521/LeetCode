#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int threeSumClosest(int* nums, int numsSize, int target) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int closest = INT_MAX;
    int first, second, third, sum, diff;
    for (first = 0; first < numsSize - 2; ++first) {
        second = first + 1;
        third = numsSize - 1;
        while (second < third) {
            sum = nums[first] + nums[second] + nums[third];
            diff = abs(target - sum);
            if (closest > diff) {
                closest = diff;
                retVal = sum;
            }

            if (sum == target) {
                return retVal;
            } else if (sum < target) {
                second += 1;
            } else if (sum > target) {
                third -= 1;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{-1, 2, 1, -4}, 4, 1}, {{0, 0, 0}, 3, 1}, {{4, 0, 5, -5, 3, 3, 0, -4, -5}, 9, -2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-1,2,1,-4], target = 1
     *  Output: 2
     *
     *  Input: nums = [0,0,0], target = 1
     *  Output: 0
     *
     *  Input: nums = [4,0,5,-5,3,3,0,-4,-5], target = -2
     *  Output: -2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = threeSumClosest(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
