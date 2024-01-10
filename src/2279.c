#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumBags(int* capacity, int capacitySize, int* rocks, int rocksSize, int additionalRocks) {
    int retVal = 0;

    int space[capacitySize];
    memset(space, 0, sizeof(space));
    int i;
    for (i = 0; i < capacitySize; ++i) {
        space[i] = capacity[i] - rocks[i];
    }
    qsort(space, capacitySize, sizeof(int), compareInteger);

    for (i = 0; i < capacitySize; ++i) {
        additionalRocks -= space[i];
        if (additionalRocks >= 0) {
            ++retVal;
            continue;
        }
        break;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int capacity[MAX_SIZE];
        int capacitySize;
        int rocks[MAX_SIZE];
        int rocksSize;
        int additionalRocks;
    } testCase[] = {{{2, 3, 4, 5}, 4, {1, 2, 4, 4}, 4, 2}, {{10, 2, 2}, 3, {2, 2, 0}, 3, 100}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: capacity =  [");
        for (j = 0; j < testCase[i].capacitySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].capacity[j]);
        }
        printf("], rocks =  [");
        for (j = 0; j < testCase[i].rocksSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rocks[j]);
        }
        printf("]\n");

        answer = maximumBags(testCase[i].capacity, testCase[i].capacitySize, testCase[i].rocks, testCase[i].rocksSize,
                             testCase[i].additionalRocks);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
