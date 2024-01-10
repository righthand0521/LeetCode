#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Counting_sort
#define COUNTING_SORT 1
#define QUICK_SORT 1
#if (COUNTING_SORT)
void countingSort(int* oriArr, int* sortArr, int n, int maxValue) {
    int* countArr = (int*)malloc(maxValue * sizeof(int));
    if (countArr == NULL) {
        perror("malloc");
        return;
    }
    memset(countArr, 0, maxValue * sizeof(int));

    int i;
    for (i = 0; i < n; ++i) {
        ++countArr[oriArr[i]];
    }
    for (i = 1; i < maxValue; ++i) {
        countArr[i] += countArr[i - 1];
    }
    for (i = n; i > 0; --i) {
        sortArr[--countArr[oriArr[i - 1]]] = oriArr[i - 1];
    }

    free(countArr);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int heightChecker(int* heights, int heightsSize) {
    int retVal = 0;

    int* expected = (int*)malloc(heightsSize * sizeof(int));
    if (expected == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(expected, 0, heightsSize * sizeof(int));
#if (COUNTING_SORT)
#define MAX_VALUE 101
    countingSort(heights, expected, heightsSize, MAX_VALUE);
#elif (QUICK_SORT)
    memcpy(expected, heights, heightsSize * sizeof(int));
    qsort(expected, heightsSize, sizeof(int), compareInteger);
#endif

    int i;
    for (i = 0; i < heightsSize; ++i) {
        if (heights[i] != expected[i]) {
            ++retVal;
        }
    }

    if (expected != NULL) {
        free(expected);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int heights[MAX_SIZE];
        int heightsSize;
    } testCase[] = {{{1, 1, 4, 2, 1, 3}, 6}, {{5, 1, 2, 3, 4}, 5}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].heights[j]);
        }
        printf("]\n");

        answer = heightChecker(testCase[i].heights, testCase[i].heightsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
