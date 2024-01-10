#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minimumRounds(int* tasks, int tasksSize) {
    int retVal = 0;

    qsort(tasks, tasksSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < tasksSize; ++i) {
        if (tasks[i] == tasks[i - 1]) {
            ++count;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        retVal += (count % 3 == 0 ? 0 : 1);

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    retVal += (count % 3 == 0 ? 0 : 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int tasks[MAX_SIZE];
        int tasksSize;
    } testCase[] = {{{2, 2, 3, 3, 2, 4, 4, 4, 4, 4}, 10}, {{2, 3, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tasks = [2,2,3,3,2,4,4,4,4,4]
     *  Output: 4
     *
     *  Input: tasks = [2,3,3]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tasks = [");
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].tasks[j]);
        }
        printf("]\n");

        answer = minimumRounds(testCase[i].tasks, testCase[i].tasksSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
