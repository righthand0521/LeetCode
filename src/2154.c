#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findFinalValue(int* nums, int numsSize, int original) {
    int retVal = original;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == retVal) {
            retVal *= 2;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int original;
    } testCase[] = {{{5, 3, 6, 1, 12}, 5, 3}, {{2, 7, 9}, 3, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], original = %d\n", testCase[i].original);

        answer = findFinalValue(testCase[i].nums, testCase[i].numsSize, testCase[i].original);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
