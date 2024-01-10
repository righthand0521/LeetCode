#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int totalHammingDistance(int* nums, int numsSize) {
    int retVal = 0;

#if 1
    int countOne;
    int countZero;
    int i, j;
    for (i = 0; i < 32; ++i) {
        countZero = 0;
        countOne = 0;
        for (j = 0; j < numsSize; ++j) {
            if ((nums[j] & ((unsigned int)1 << i)) != 0) {
                ++countOne;
            } else {
                ++countZero;
            }
        }
        retVal += (countOne * countZero);
    }
#else
    qsort(nums, numsSize, sizeof(int), compareInteger);

    int xorValue;
    int i, j;
    for (i = 0; i < numsSize; ++i) {
        for (j = (i + 1); j < numsSize; ++j) {
            if (nums[i] == nums[j]) {
                continue;
            }
            xorValue = nums[i] ^ nums[j];
            while (xorValue > 0) {
                retVal += (xorValue & 0x1);
                xorValue >>= 1;
            }
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_NUMSSIZE (10000)
    struct testCaseType {
        int nums[MAX_NUMSSIZE];
        int numsSize;
    } testCase[] = {{{4, 14, 2}, 3}, {{4, 14, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = totalHammingDistance(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
