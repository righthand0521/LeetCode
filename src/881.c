#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int numRescueBoats(int* people, int peopleSize, int limit) {
    int retVal = 0;

    qsort(people, peopleSize, sizeof(int), compareInteger);

    int left = 0;
    int right = peopleSize - 1;
    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            ++left;
        }
        --right;
        ++retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50000)
    struct testCaseType {
        int people[MAX_SIZE];
        int peopleSize;
        int limit;
    } testCase[] = {{{1, 2}, 2, 3}, {{3, 2, 2, 1}, 4, 3}, {{3, 5, 3, 4}, 4, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: people = [1,2], limit = 3
     *  Output: 1
     *
     *  Input: people = [3,2,2,1], limit = 3
     *  Output: 3
     *
     *  Input: people = [3,5,3,4], limit = 5
     *  Output: 4
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: people = [");
        for (j = 0; j < testCase[i].peopleSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].people[j]);
        }
        printf("], target = %d\n", testCase[i].limit);

        answer = numRescueBoats(testCase[i].people, testCase[i].peopleSize, testCase[i].limit);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
