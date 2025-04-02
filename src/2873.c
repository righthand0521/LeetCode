#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maximumTripletValue(int* nums, int numsSize) {
    long long retVal = 0;

    long long idxMax = 0;
    long long diffMax = 0;
    for (int k = 0; k < numsSize; k++) {
        retVal = fmax(retVal, diffMax * nums[k]);
        diffMax = fmax(diffMax, idxMax - nums[k]);
        idxMax = fmax(idxMax, (long long)nums[k]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{12, 6, 1, 2, 7}, 5}, {{1, 10, 3, 4, 19}, 5}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [12,6,1,2,7]
     *  Output: 77
     *
     *  Input: nums = [1,10,3,4,19]
     *  Output: 133
     *
     *  Input: nums = [1,2,3]
     *  Output: 0
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = maximumTripletValue(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
