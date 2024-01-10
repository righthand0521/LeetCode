#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* findErrorNums(int* nums, int numsSize, int* returnSize) {
    *returnSize = 2;
    int* pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    bool* pRecord = (bool*)malloc(numsSize * sizeof(bool));
    if (pRecord == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRecord, 0, numsSize * sizeof(bool));

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (pRecord[nums[i] - 1] == true) {
            pRetVal[0] = nums[i];
        }
        pRecord[nums[i] - 1] = true;
    }

    for (i = 0; i < numsSize; ++i) {
        if (pRecord[i] == false) {
            pRetVal[1] = i + 1;
            break;
        }
    }

    free(pRecord);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 2, 4}, 4, 0}, {{1, 1}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = findErrorNums(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
