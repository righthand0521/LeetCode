#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int firstMissingPositive(int* nums, int numsSize) {
    int retVal = 1;

    int i;

#define MAX_RECORD 100000
    int RECORD[MAX_RECORD];
    for (i = 0; i < MAX_RECORD; ++i) {
        RECORD[i] = INT_MAX;
    }

    int idx;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= 0) {
            continue;
        }
        idx = (nums[i] - 1) % MAX_RECORD;
        RECORD[idx] = (RECORD[idx] < nums[i]) ? RECORD[idx] : nums[i];

        if (nums[i] == retVal) {
            ++retVal;
        }
    }

    idx = (retVal - 1) % MAX_RECORD;
    while (retVal <= INT_MAX) {
        if ((RECORD[idx] == INT_MAX) || (RECORD[idx] != retVal)) {
            break;
        }
        ++retVal;
        idx = (retVal - 1) % MAX_RECORD;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 0}, 3}, {{3, 4, -1, 1}, 4}, {{7, 8, 9, 11, 12}, 5}, {{2, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = firstMissingPositive(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
