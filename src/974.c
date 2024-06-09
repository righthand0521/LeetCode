#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subarraysDivByK(int* nums, int numsSize, int k) {
    int retVal = 0;

    int modRecord[k];
    memset(modRecord, 0, sizeof(modRecord));
    modRecord[0] = 1;

    int prefixSumMod = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        prefixSumMod = (prefixSumMod + nums[i] % k + k) % k;
        retVal += modRecord[prefixSumMod];
        modRecord[prefixSumMod]++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{4, 5, 0, -2, -3, 1}, 6, 5}, {{5}, 1, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,5,0,-2,-3,1], k = 5
     *  Output: 7
     *
     *  Input: nums = [5], k = 9
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = subarraysDivByK(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
