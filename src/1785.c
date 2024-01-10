#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minElements(int* nums, int numsSize, int limit, int goal) {
    int retVal = 0;

    /* Boundary
     *  1 <= nums.length <= 10^5
     *  1 <= limit <= 10^6.
     */
    long long sum = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    long long diff = llabs(sum - goal);
    /* divisible or not divisible
     *  diff = n * limit
     *  diff = n * limit + r
     */
    retVal = (diff + limit - 1) / limit;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int limit;
        int goal;
    } testCase[] = {{{1, -1, 1}, 3, 3, -4}, {{1, -10, 9, 1}, 4, 100, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], limit = %d, goal = %d\n", testCase[i].limit, testCase[i].goal);

        answer = minElements(testCase[i].nums, testCase[i].numsSize, testCase[i].limit, testCase[i].goal);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
