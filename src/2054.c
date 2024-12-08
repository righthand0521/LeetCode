#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        if (p1[1] == p2[1]) {
            return (p1[2] > p2[2]);
        }
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    int retVal = 0;

    int timesIndex = 0;
    int timesSize = eventsSize * 2;
    int times[timesSize][3];
    memset(times, 0, sizeof(times));
    for (int i = 0; i < eventsSize; ++i) {
        times[timesIndex][0] = events[i][0];
        times[timesIndex][1] = 1;  // 1 denotes start time.
        times[timesIndex][2] = events[i][2];
        timesIndex++;
        times[timesIndex][0] = events[i][1] + 1;
        times[timesIndex][1] = 0;  // 0 denotes end time.
        times[timesIndex][2] = events[i][2];
        timesIndex++;
    }
    qsort(times, timesSize, sizeof(times[0]), compareIntArray);

    int maxValue = 0;
    for (int i = 0; i < timesSize; ++i) {
        // If current time is a start time, find maximum sum of maximum end time till now.
        if (times[i][1]) {
            retVal = fmax(retVal, times[i][2] + maxValue);
        } else {
            maxValue = fmax(maxValue, times[i][2]);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int events[MAX_SIZE][3];
        int eventsSize;
        int eventsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 3, 2}, {4, 5, 2}, {2, 4, 3}}, 3, {3, 3, 3}},
                    {{{1, 3, 2}, {4, 5, 2}, {1, 5, 5}}, 3, {3, 3, 3}},
                    {{{1, 5, 3}, {1, 5, 1}, {6, 6, 5}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: events = [[1,3,2],[4,5,2],[2,4,3]]
     *  Output: 4
     *
     *  Input: events = [[1,3,2],[4,5,2],[1,5,5]]
     *  Output: 5
     *
     *  Input: events = [[1,5,3],[1,5,1],[6,6,5]]
     *  Output: 8
     */

    int** pEvents = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("events = [");
        for (j = 0; j < testCase[i].eventsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].eventsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].events[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEvents = (int**)malloc(testCase[i].eventsSize * sizeof(int*));
        if (pEvents == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        memset(pEvents, 0, testCase[i].eventsSize * sizeof(int*));
        for (j = 0; j < testCase[i].eventsSize; ++j) {
            pEvents[j] = (int*)malloc(testCase[i].eventsColSize[j] * sizeof(int));
            if (pEvents[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEvents[k]);
                    pEvents[k] = NULL;
                }
                free(pEvents);
                pEvents = NULL;
            }
            memset(pEvents[j], 0, (testCase[i].eventsColSize[j] * sizeof(int)));
            memcpy(pEvents[j], testCase[i].events[j], (testCase[i].eventsColSize[j] * sizeof(int)));
        }
        answer = maxTwoEvents(pEvents, testCase[i].eventsSize, testCase[i].eventsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].eventsSize; ++j) {
            free(pEvents[j]);
            pEvents[j] = NULL;
        }
        free(pEvents);
        pEvents = NULL;
    }

    return EXIT_SUCCESS;
}
