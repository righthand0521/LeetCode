#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Biweekly_Contest_97 (1)  // 0:23:42; 0
#if (Biweekly_Contest_97)
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* separateDigits(int* nums, int numsSize, int* returnSize) {
    int* pRetVal = NULL;

#define MAX_RETURN_SIZE (6 * 1000)
    pRetVal = (int*)calloc(MAX_RETURN_SIZE, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    (*returnSize) = 0;
    int buf[8];
    int count;
    int i;
    for (i = 0; i < numsSize; ++i) {
        memset(buf, 0, sizeof(int));
        count = 0;
        while (nums[i] > 0) {
            buf[count++] = nums[i] % 10;
            nums[i] /= 10;
        }

        while (count > 0) {
            pRetVal[(*returnSize)++] = buf[--count];
        }
    }

    return pRetVal;
}
#endif

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int returnSize;
    } testCase[] = {{{13, 25, 83, 77}, 4, 0}, {{7, 1, 3, 9}, 4, 0}, {{100000, 100}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = separateDigits(testCase[i].nums, testCase[i].numsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
