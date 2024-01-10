#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareTheNumberOfBits(const void* n1, const void* n2) {
    if (__builtin_popcount(*(int*)n1) > __builtin_popcount(*(int*)n2)) {
        return 1;
    } else if (__builtin_popcount(*(int*)n1) < __builtin_popcount(*(int*)n2)) {
        return 0;
    } else {
        return (*(int*)n1 - *(int*)n2);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortByBits(int* arr, int arrSize, int* returnSize) {
    int* pRetVal = NULL;
    (*returnSize) = arrSize;

    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));
    memcpy(pRetVal, arr, ((*returnSize) * sizeof(int)));

    qsort(pRetVal, (*returnSize), sizeof(int), compareTheNumberOfBits);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int returnSize;
    } testCase[] = {{{0, 1, 2, 3, 4, 5, 6, 7, 8}, 9, 0}, {{1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1}, 11, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [0,1,2,3,4,5,6,7,8]
     *  Output: [0,1,2,4,8,3,5,6,7]
     *
     *  Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
     *  Output: [1,2,4,8,16,32,64,128,256,512,1024]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        pAnswer = sortByBits(testCase[i].arr, testCase[i].arrSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
