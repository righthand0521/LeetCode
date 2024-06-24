#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minKBitFlips(int* nums, int numsSize, int k) {
    int retVal = 0;

    int revCnt = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if ((i >= k) && (nums[i - k] > 1)) {
            revCnt ^= 1;
            nums[i - k] -= 2;
        }

        if (nums[i] == revCnt) {
            if (i + k > numsSize) {
                retVal = -1;
                break;
            }
            ++retVal;
            revCnt ^= 1;
            nums[i] += 2;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{0, 1, 0}, 3, 1}, {{1, 1, 0}, 3, 2}, {{0, 0, 0, 1, 0, 1, 1, 0}, 8, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,0], k = 1
     *  Output: 2
     *
     *  Input: nums = [1,1,0], k = 2
     *  Output: -1
     *
     *  Input: nums = [0,0,0,1,0,1,1,0], k = 3
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minKBitFlips(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
