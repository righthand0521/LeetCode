#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(int* tasks, int* workers, int workersSize, int pills, int strength, int middle) {
    bool retVal = false;

    int workersIdx = workersSize - 1;
    int workersQueue[workersSize];
    int workersQueueHead = workersSize - 1;
    int workersQueueTail = workersSize - 1;
    for (int i = middle - 1; i >= 0; --i) {
        while ((workersIdx >= workersSize - middle) && (workers[workersIdx] + strength >= tasks[i])) {
            workersQueue[workersQueueHead] = workers[workersIdx];
            --workersQueueHead;
            --workersIdx;
        }

        if (workersQueueHead == workersQueueTail) {
            return retVal;
        }

        // If the largest element in the deque is greater than or equal to tasks[i]
        if (workersQueue[workersQueueTail] >= tasks[i]) {
            workersQueueTail--;
            continue;
        }

        if (pills == 0) {
            return retVal;
        }

        --pills;
        workersQueueHead++;
    }
    retVal = true;

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxTaskAssign(int* tasks, int tasksSize, int* workers, int workersSize, int pills, int strength) {
    int retVal = 0;

    qsort(tasks, tasksSize, sizeof(int), compareInteger);
    qsort(workers, workersSize, sizeof(int), compareInteger);

    int middle;
    int left = 1;
    int right = (workersSize < tasksSize) ? workersSize : tasksSize;
    while (left <= right) {
        middle = (left + right) / 2;
        if (check(tasks, workers, workersSize, pills, strength, middle) == true) {
            left = middle + 1;
            retVal = middle;
        } else {
            right = middle - 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int tasks[MAX_SIZE];
        int tasksSize;
        int workers[MAX_SIZE];
        int workersSize;
        int pills;
        int strength;
    } testCase[] = {{{3, 2, 1}, 3, {0, 3, 3}, 3, 1, 1},
                    {{5, 4}, 2, {0, 0, 0}, 3, 1, 5},
                    {{10, 15, 30}, 3, {0, 10, 10, 10, 10}, 5, 3, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
     *  Output: 3
     *
     *  Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
     *  Output: 1
     *
     *  Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tasks = [");
        for (j = 0; j < testCase[i].tasksSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].tasks[j]);
        }
        printf(", workers = [");
        for (j = 0; j < testCase[i].workersSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].workers[j]);
        }
        printf("], pills = %d, strength = %d\n", testCase[i].pills, testCase[i].strength);

        answer = maxTaskAssign(testCase[i].tasks, testCase[i].tasksSize, testCase[i].workers, testCase[i].workersSize,
                               testCase[i].pills, testCase[i].strength);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
