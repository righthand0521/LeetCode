#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int* nums, int start, int end) {
    int tmp;
    while (start < end) {
        tmp = nums[start];
        nums[start] = nums[end];
        nums[end] = tmp;

        ++start;
        --end;
    }
}
void rotate(int* nums, int numsSize, int k) {
    /* Example: Input: nums = [1,2,3,4,5,6,7], k = 3; Output: [5,6,7,1,2,3,4]
     *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
     *  | 1 2 3 4 | 5 6 7 | => | 7 6 5 | 4 3 2 1 | => | 5 6 7 | 4 3 2 1 | => | 5 6 7 | 1 2 3 4 |
     *  +---------+-------+    +-------+---------+    +-------+---------+    +-------+---------+
     */
    k %= numsSize;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, numsSize - 1);
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7}, 7, 3}, {{-1, -100, 3, 99}, 4, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,5,6,7], k = 3
     *  Output: [5,6,7,1,2,3,4]
     *
     *  Input: nums = [-1,-100,3,99], k = 2
     *  Output: [3,99,-1,-100]
     */

    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        rotate(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
