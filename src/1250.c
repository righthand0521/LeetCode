#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
bool isGoodArray(int* nums, int numsSize) {
    bool retVal = false;

    /* Bézout's identity: https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
     *  The basic idea is that for integers a and b,
     *  if gcd(a,b) = d, then there exist integers x and y, such that ax + by = d.
     *  This can be generalized for (n >= 2).
     *  if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, ax + by + cz = d.
     *
     *  Now this problem is just asking if gcd(x1, ......, xn) = 1
     */
    int d = gcd(nums[0], nums[0]);
    int i;
    for (i = 1; i < numsSize; ++i) {
        d = gcd(d, nums[i]);
    }
    if (d == 1) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{12, 5, 7, 23}, 4}, {{29, 6, 10}, 3}, {{3, 6}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [12,5,7,23]
     *  Output: true
     *
     *  Input: nums = [29,6,10]
     *  Output: true
     *
     *  Input: nums = [3,6]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: hours = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = isGoodArray(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
