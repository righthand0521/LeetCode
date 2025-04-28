#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long countSubarrays(int* nums, int numsSize, long long k) {
    long long retVal = 0;

    long long total = 0;
    int head = 0;
    for (int tail = 0; tail < numsSize; ++tail) {
        total += nums[tail];
        while ((head <= tail) && (total * (tail - head + 1) >= k)) {
            total -= nums[head];
            ++head;
        }
        retVal += (tail - head + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{2, 1, 4, 3, 5}, 5, 10}, {{1, 1, 1}, 3, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,4,3,5], k = 10
     *  Output: 6
     *
     *  Input: nums = [1,1,1], k = 5
     *  Output: 5
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = countSubarrays(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
