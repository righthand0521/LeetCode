#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isIdealPermutation(int* nums, int numsSize) {
    bool retVal = false;

    /* if the absolute value is larger than 1, means the number of global inversion must be bigger than local inversion,
     * because a local inversion is a global inversion, but a global one may not be local.
     *
     * proof
     *  If A[i] > i + 1, means at least one number that is smaller than A[i] is kicked out from first A[i] numbers,
     *  and the distance between this smaller number and A[i] is at least 2, then it is a non-local global inversion.
     *  For example, A[i] = 3, i = 1, at least one number that is smaller than 3 is kicked out from first 3 numbers,
     *  and the distance between the smaller number and 3 is at least 2.
     *  If A[i] < i - 1, means at least one number that is bigger than A[i] is kicked out from last n - i numbers,
     *  and the distance between this bigger number and A[i] is at least 2, then it is a non-local global inversion.
     *
     * Ref
     *  https://leetcode.com/problems/global-and-local-inversions/discuss/113656/My-3-lines-C%2B%2B-Solution
     *  https://leetcode.cn/problems/global-and-local-inversions/solutions/1973203/-by-muse-77-q80y/
     */
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (abs(nums[i] - i) > 1) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 0, 2}, 3}, {{1, 2, 0}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = true;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = isIdealPermutation(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
