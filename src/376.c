#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_PROGRAMMING (1)
#define GREEDY (1)
int wiggleMaxLength(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize < 2) {
        retVal = numsSize;
        return retVal;
    }

#if (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING\n");

    int up = 1;
    int down = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] > nums[i - 1]) {
            up = fmax(up, down + 1);
        } else if (nums[i] < nums[i - 1]) {
            down = fmax(up + 1, down);
        }
    }
    retVal = fmax(up, down);
#elif (GREEDY)
    printf("GREEDY\n");

    int preDiff = nums[1] - nums[0];
    retVal = (preDiff == 0 ? 1 : 2);
    int curDiff;
    int i;
    for (i = 2; i < numsSize; ++i) {
        curDiff = nums[i] - nums[i - 1];
        if ((curDiff > 0 && preDiff <= 0) || (curDiff < 0 && preDiff >= 0)) {
            ++retVal;
            preDiff = curDiff;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {
        {{1, 7, 4, 9, 2, 5}, 6}, {{1, 17, 5, 10, 13, 15, 10, 5, 16, 8}, 10}, {{1, 2, 3, 4, 5, 6, 7, 8, 9}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = wiggleMaxLength(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
