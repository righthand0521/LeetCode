#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canReach(int* arr, int arrSize, int start) {
    bool retVal = false;

    // Breadth-First Search
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    int bfsQueue[arrSize * 2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[0] = start;
    ++bfsQueueRear;

    int visit[arrSize];
    memset(visit, 0, sizeof(visit));
    visit[start] = 1;

    int key;
    int value;
    while (bfsQueueFront < bfsQueueRear) {
        value = bfsQueue[bfsQueueFront];
        ++bfsQueueFront;

        if (arr[value] == 0) {
            retVal = true;
            return retVal;
        }

        key = value + arr[value];
        if ((key < arrSize) && (visit[key] == 0)) {
            visit[key] = 1;
            bfsQueue[bfsQueueRear] = key;
            ++bfsQueueRear;
        }

        key = value - arr[value];
        if ((key >= 0) && (visit[key] == 0)) {
            visit[key] = 1;
            bfsQueue[bfsQueueRear] = key;
            ++bfsQueueRear;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int start;
    } testCase[] = {{{4, 2, 3, 0, 3, 1, 2}, 7, 5}, {{4, 2, 3, 0, 3, 1, 2}, 7, 0}, {{3, 0, 2, 1, 2}, 5, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [4,2,3,0,3,1,2], start = 5
     *  Output: true
     *
     *  Input: arr = [4,2,3,0,3,1,2], start = 0
     *  Output: true
     *
     *  Input: arr = [3,0,2,1,2], start = 2
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("], start = %d\n", testCase[i].start);

        answer = canReach(testCase[i].arr, testCase[i].arrSize, testCase[i].start);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
