#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef METHOD_SUM
#define METHOD_SUM 1

int missingNumber_sum(int* nums, int numsSize) {
    int retVal = (numsSize * (numsSize + 1)) / 2;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal -= nums[i];
    }

    return retVal;
}
#endif
#ifndef METHOD_XOR
#define METHOD_XOR 1

int missingNumber_xor(int* nums, int numsSize) {
    int retVal = numsSize;

    int i;
    for (i = 0; i < numsSize; ++i) {
        retVal ^= i;
        retVal ^= nums[i];
    }

    return retVal;
}
#endif

int main(int argc, char** argv) {
    typedef int (*executeFunc)(int*, int);
    const struct exampleType {
        char* method;
        executeFunc eFunc;
    } example[] = {
#ifdef METHOD_SUM
        {"sum", missingNumber_sum}
#endif
#ifdef METHOD_XOR
        ,
        {"xor", missingNumber_xor}
#endif
    };
    int numberOfExample = sizeof(example) / sizeof(example[0]);

#define MAX_SIZE 10000
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{3, 0, 1}, 3}, {{0, 1}, 2}, {{9, 6, 4, 2, 3, 5, 7, 0, 1}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int idx_method;
    int idx_testCase;
    int idx_testData;
    for (idx_method = 0; idx_method < numberOfExample; ++idx_method) {
        printf("== Method %d: %s ==\n", idx_method + 1, example[idx_method].method);
        printf("\n");

        for (idx_testCase = 0; idx_testCase < numberOfTestCase; ++idx_testCase) {
            printf("Input: nums = [");
            for (idx_testData = 0; idx_testData < testCase[idx_testCase].numsSize; ++idx_testData) {
                printf("%s%d", (idx_testData == 0) ? "" : ",", testCase[idx_testCase].nums[idx_testData]);
            }
            printf("]\n");

            answer = example[idx_method].eFunc(testCase[idx_testCase].nums, testCase[idx_testCase].numsSize);
            printf("Output: %d\n", answer);

            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
