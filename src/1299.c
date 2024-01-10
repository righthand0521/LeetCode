#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* replaceElements(int* arr, int arrSize, int* returnSize) {
#if 1  // return original arr taht is replaced
    *returnSize = arrSize;

    int greatest = -1;
    int tmp;
    int i;
    for (i = (arrSize - 1); i >= 0; --i) {
        tmp = arr[i];
        arr[i] = greatest;
        greatest = (greatest > tmp) ? greatest : tmp;
    }

    return arr;
#else  // return new malloc array
    int* pRetVal;

    *returnSize = arrSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    int greatest = -1;
    int i;
    for (i = (arrSize - 1); i >= 0; --i) {
        pRetVal[i] = greatest;
        greatest = (greatest > arr[i]) ? greatest : arr[i];
    }

    return pRetVal;
#endif
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int returnSize;
    } testCase[] = {{{17, 18, 5, 4, 6, 1}, 6, 0}, {{400}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        pAnswer = replaceElements(testCase[i].arr, testCase[i].arrSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

#if 1  // return original arr taht is replaced
#else  // return new malloc array
        free(pAnswer);
        pAnswer = NULL;
#endif
    }

    return EXIT_SUCCESS;
}
