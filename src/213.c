#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int robHouse(int* nums, int start, int end) {
    int retVal = 0;

    int first = nums[start];
    int second = MAX(nums[start], nums[start + 1]);
    int temp;
    int i;
    for (i = start + 2; i < end; ++i) {
        temp = second;
        second = MAX(first + nums[i], second);
        first = temp;
    }
    retVal = second;

    return retVal;
}
int rob(int* nums, int numsSize) {
    int retVal = 0;

    if (numsSize == 1) {
        retVal = nums[0];
        return retVal;
    } else if (numsSize == 2) {
        retVal = MAX(nums[0], nums[1]);
        return retVal;
    }

    int robStartFirst = robHouse(nums, 0, numsSize - 1);
    int robStartSecond = robHouse(nums, 1, numsSize);
    retVal = MAX(robStartFirst, robStartSecond);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 2}, 3}, {{1, 2, 3, 1}, 4}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = rob(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
