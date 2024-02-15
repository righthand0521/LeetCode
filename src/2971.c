#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long largestPerimeter(int* nums, int numsSize) {
    long long retVal = -1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long long sum = nums[0] + nums[1];
    int i;
    for (i = 2; i < numsSize; ++i) {
        if (sum > nums[i]) {
            retVal = sum + nums[i];
        }
        sum += nums[i];
    }
    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{5, 5, 5}, 3}, {{1, 12, 1, 2, 5, 50, 3}, 7}, {{5, 5, 50}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [5,5,5]
     *  Output: 15
     *
     *  Input: nums = [1,12,1,2,5,50,3]
     *  Output: 12
     *
     *  Input: nums = [5,5,50]
     *  Output: -1
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = largestPerimeter(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
