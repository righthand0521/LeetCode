#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize) {
    int* pRetVal = NULL;

    *returnSize = k;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (*returnSize) * sizeof(int));

    int head = 0;
    int tail = arrSize - 1;
    while ((tail - head) >= k) {
        if (abs(arr[head] - x) > abs(arr[tail] - x)) {
            ++head;
        } else {
            --tail;
        }
    }
    memcpy(pRetVal, arr + head, k * sizeof(int));

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
        int x;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5, 4, 3, 0},
                    {{1, 2, 3, 4, 5}, 5, 4, -1, 0},
                    {{1, 1, 1, 10, 10, 10}, 6, 1, 9, 0},
                    {{0, 0, 0, 1, 3, 5, 6, 7, 8, 8}, 10, 2, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d, x = %d\n", testCase[i].k, testCase[i].x);

        pAnswer = findClosestElements(testCase[i].arr, testCase[i].arrSize, testCase[i].k, testCase[i].x,
                                      &testCase[i].returnSize);
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
