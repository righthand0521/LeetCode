#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int heightChecker(int* heights, int heightsSize) {
    int retVal = 0;

    int* expected = (int*)malloc(heightsSize * sizeof(int));
    if (expected == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(expected, 0, heightsSize * sizeof(int));
    memcpy(expected, heights, heightsSize * sizeof(int));
    qsort(expected, heightsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < heightsSize; ++i) {
        if (heights[i] != expected[i]) {
            ++retVal;
        }
    }

    free(expected);
    expected = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int heights[MAX_SIZE];
        int heightsSize;
    } testCase[] = {{{1, 1, 4, 2, 1, 3}, 6}, {{5, 1, 2, 3, 4}, 5}, {{1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [1,1,4,2,1,3]
     *  Output: 3
     *
     *  Input: heights = [5,1,2,3,4]
     *  Output: 5
     *
     *  Input: heights = [1,2,3,4,5]
     *  Output: 0
     */

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
