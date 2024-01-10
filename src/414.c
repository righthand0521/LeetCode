#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONG_METHOD 1
#define SORT_METHOD 1
#if (LONG_METHOD)
#elif (SORT_METHOD)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int thirdMax(int* nums, int numsSize) {
    int retVal;

#if (LONG_METHOD)
    long first = nums[0];
    long second = LONG_MIN;
    long third = LONG_MIN;

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] <= third) {
            continue;
        } else if (nums[i] < second) {
            third = nums[i];
            continue;
        } else if (nums[i] == second) {
            continue;
        } else if (nums[i] < first) {
            third = second;
            second = nums[i];
            continue;
        } else if (nums[i] == first) {
            continue;
        }

        third = second;
        second = first;
        first = nums[i];
    }
    retVal = (third != LONG_MIN) ? third : first;
#elif (SORT_METHOD)
    qsort(nums, numsSize, sizeof(int), compareInteger);
#define MAX_NUMBER 3
    retVal = nums[0];
    int count = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] != nums[i]) {
            ++count;
        }

        if (count == MAX_NUMBER) {
            retVal = nums[i];
            break;
        }
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 2, 1}, 3},           {{1, 2}, 2},
                    {{2, 2, 3, 1}, 4},        {{1, 2, 2, 5, 3, 5}, 6},
                    {{1, -2147483648, 2}, 3}, {{1, 2, -2147483648}, 3},
                    {{-2147483648, 1, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = thirdMax(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
