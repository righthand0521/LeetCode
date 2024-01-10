#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numSubarrayProductLessThanK(int* nums, int numsSize, int k) {
    int retVal = 0;

    /* the product of nums could not be strictly less than 1
     *  1 <= nums.length <= 3 * 10^4
     *  1 <= nums[i] <= 1000
     *  0 <= k <= 10^6
     */
    if (k <= 1) {
        return retVal;
    }

    int product = 1;
    int right = 0;
    int left = 0;
    for (right = 0; right < numsSize; right++) {
        /* Sliding window with Two Pointer
         *  +--------------------------------------------+
         *  |    0   |      1      |   2   |      3      |
         *  +--------------------------------------------+
         *  |   10   |      5      |   2   |      6      |
         *  +--------------------------------------------+
         *  |  right -1-> right -2-> right -4-> right    |
         *  |  left  -3-> left                           |
         *  +--------------------------------------------+
         *  | product = 10                               |
         *  | product = 50, product = 100                |
         *  | product = 10                               |
         *  | product = 60                               |
         *  +--------------------------------------------+
         */
        product *= nums[right];
        while (product >= k) {
            product /= nums[left];
            left++;
        }

        retVal += (right - left + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{10, 5, 2, 6}, 4, 100}, {{1, 2, 3}, 0, 0}, {{1, 1, 1}, 3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = numSubarrayProductLessThanK(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
