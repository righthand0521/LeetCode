#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numSubseq(int* nums, int numsSize, int target) {
    int retVal = 0;

    int pows[numsSize];
    memset(pows, 0, sizeof(pows));
    pows[0] = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        pows[i] = pows[i - 1] * 2 % MODULO;
    }

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int head = 0;
    int tail = numsSize - 1;
    while (head <= tail) {
        if (nums[head] + nums[tail] > target) {
            --tail;
            continue;
        }

        retVal += pows[tail - head];
        retVal %= MODULO;
        ++head;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{3, 5, 6, 7}, 4, 9}, {{3, 3, 6, 8}, 4, 10}, {{2, 3, 3, 4, 6, 7}, 6, 12}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,5,6,7], target = 9
     *  Output: 4
     *
     *  Input: nums = [3,3,6,8], target = 10
     *  Output: 6
     *
     *  Input: nums = [2,3,3,4,6,7], target = 12
     *  Output: 61
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = numSubseq(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
