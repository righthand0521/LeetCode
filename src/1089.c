#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void duplicateZeros(int* arr, int arrSize) {
    int i, j;
    for (i = 0; i < arrSize; ++i) {
        if (arr[i] != 0) {
            continue;
        }

        for (j = arrSize - 2; j >= i; --j) {
            arr[j + 1] = arr[j];
        }
        ++i;
    }
}

int* pInput = NULL;
int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 0, 2, 3, 0, 4, 5, 0}, 8}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        pInput = (int*)malloc(testCase[i].arrSize * sizeof(int));
        if (pInput == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pInput, 0, testCase[i].arrSize * sizeof(int));
        memcpy(pInput, testCase[i].arr, testCase[i].arrSize * sizeof(int));
        duplicateZeros(pInput, testCase[i].arrSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pInput[j]);
        }
        printf("]\n");

        printf("\n");

        free(pInput);
        pInput = NULL;
    }

    return EXIT_SUCCESS;
}
