#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int minimumBoxes(int* apple, int appleSize, int* capacity, int capacitySize) {
    int retVal = 0;

    qsort(capacity, capacitySize, sizeof(int), compareInteger);
    int totalApples = 0;
    for (int i = 0; i < appleSize; i++) {
        totalApples += apple[i];
    }
    while (totalApples > 0) {
        totalApples -= capacity[retVal];
        retVal += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int apple[MAX_SIZE];
        int appleSize;
        int capacity[MAX_SIZE];
        int capacitySize;
    } testCase[] = {{{1, 3, 2}, 3, {4, 3, 1, 5, 2}, 5}, {{5, 5, 5}, 3, {2, 4, 2, 7}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: apple = [1,3,2], capacity = [4,3,1,5,2]
     *  Output: 2
     *
     *  Input: apple = [5,5,5], capacity = [2,4,2,7]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: apple = [");
        for (j = 0; j < testCase[i].appleSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].apple[j]);
        }
        printf("], capacity = [");
        for (j = 0; j < testCase[i].capacitySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].capacity[j]);
        }
        printf("]\n");

        answer = minimumBoxes(testCase[i].apple, testCase[i].appleSize, testCase[i].capacity, testCase[i].capacitySize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
