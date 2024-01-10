#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int lastStoneWeight(int* stones, int stonesSize) {
    int retVal = 0;

    while (stonesSize > 1) {
        qsort(stones, stonesSize, sizeof(int), compareInteger);

        stones[stonesSize - 2] = stones[stonesSize - 1] - stones[stonesSize - 2];
        if (stones[stonesSize - 2] == 0) {
            stonesSize -= 2;
        } else {
            stonesSize -= 1;
        }
    }
    retVal = stones[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        int stones[MAX_SIZE];
        int stonesSize;
    } testCase[] = {{{2, 7, 4, 1, 8, 1}, 6}, {{1}, 1}, {{3, 7, 2}, 3}, {{2, 2}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: stones = [2,7,4,1,8,1]
     *  Output: 1
     *
     *  Input: stones = [1]
     *  Output: 1
     *
     *  Input: stones = [3,7,2]
     *  Output: 2
     *
     *  Input: stones = [2,2]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: stones = [");
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].stones[j]);
        }
        printf("]\n");

        answer = lastStoneWeight(testCase[i].stones, testCase[i].stonesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
