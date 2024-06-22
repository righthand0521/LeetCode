#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfSubarrays(int* nums, int numsSize, int k) {
    int retVal = 0;

    int initialGap = 0;
    int qsize = 0;
    int start = 0;
    for (int end = 0; end < numsSize; ++end) {
        // If current element is odd, increment qsize by 1.
        if (nums[end] % 2 == 1) {
            qsize += 1;
        }

        if (qsize == k) {
            initialGap = 0;

            // Calculate the number of even elements in the beginning of subarray.
            while (qsize == k) {
                qsize -= nums[start] % 2;
                initialGap += 1;
                start += 1;
            }
        }

        retVal += initialGap;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 1, 2, 1, 1}, 5, 3}, {{2, 4, 6}, 3, 1}, {{2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 10, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,1,2,1,1], k = 3
     *  Output: 2
     *
     *  Input: nums = [2,4,6], k = 1
     *  Output: 0
     *
     *  Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
     *  Output: 16
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = numberOfSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
