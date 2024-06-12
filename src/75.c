#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* n1, int* n2) {
    int tmp = (*n1);
    (*n1) = (*n2);
    (*n2) = tmp;
}
void sortColors(int* nums, int numsSize) {
    int ptr = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            swap(&nums[i], &nums[ptr]);
            ptr++;
        }
    }
    for (i = ptr; i < numsSize; ++i) {
        if (nums[i] == 1) {
            swap(&nums[i], &nums[ptr]);
            ptr++;
        }
    }
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 0, 2, 1, 1, 0}, 6}, {{2, 0, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,0,2,1,1,0]
     *  Output: [0,0,1,1,2,2]
     *
     *  Input: nums = [2,0,1]
     *  Output: [0,1,2]
     */

    int* pInput = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pInput = (int*)malloc(testCase[i].numsSize * sizeof(int));
        if (pInput == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pInput, 0, testCase[i].numsSize * sizeof(int));
        memcpy(pInput, testCase[i].nums, testCase[i].numsSize * sizeof(int));
        sortColors(pInput, testCase[i].numsSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pInput[j]);
        }
        printf("]\n");

        printf("\n");

        free(pInput);
        pInput = NULL;
    }

    return EXIT_SUCCESS;
}
