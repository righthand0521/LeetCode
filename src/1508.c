#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int rangeSum(int* nums, int numsSize, int n, int left, int right) {
    int retVal = 0;

    int numsSumSize = n * (n + 1) / 2;
    int numsSum[numsSumSize];
    memset(numsSum, 0, sizeof(numsSum));
    int numsSumIdx = 0;

    int idx, start, sum;
    for (start = 0; start < numsSize; ++start) {
        sum = 0;
        for (idx = start; idx < numsSize; ++idx) {
            sum += nums[idx];
            numsSum[numsSumIdx++] = sum;
        }
    }
    qsort(numsSum, numsSumIdx, sizeof(int), compareInteger);

    for (idx = left - 1; idx < right; ++idx) {
        retVal += numsSum[idx];
        retVal %= MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int n;
        int left;
        int right;
    } testCase[] = {{{1, 2, 3, 4}, 4, 4, 1, 5}, {{1, 2, 3, 4}, 4, 4, 3, 4}, {{1, 2, 3, 4}, 4, 4, 1, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
     *  Output: 13
     *
     *  Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
     *  Output: 6
     *
     *  Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
     *  Output: 50
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], n = %d, left = %d, right = %d\n", testCase[i].n, testCase[i].left, testCase[i].right);

        answer = rangeSum(testCase[i].nums, testCase[i].numsSize, testCase[i].n, testCase[i].left, testCase[i].right);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
