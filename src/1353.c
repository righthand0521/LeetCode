#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/solutions/732656/1353-zui-duo-ke-yi-can-jia-de-hui-yi-shu-zrks/
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = *(int**)a1;
    int* p2 = *(int**)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
int maxEvents(int** events, int eventsSize, int* eventsColSize) {
    int retVal = 0;

    qsort(events, eventsSize, sizeof(int*), compareIntArray);

#define MAX_EVENTS_SIZE (100000 + 4)  // 1 <= events.length <= 10^5
    int* hash = (int*)calloc(MAX_EVENTS_SIZE, sizeof(int));
    if (hash == NULL) {
        perror("calloc");
        return retVal;
    }

    int temp = 0;
    int prev = 0;
    int i, j;
    for (i = 0; i < eventsSize; ++i) {
        j = (events[i][0] >= prev) ? (fmax(events[i][0], temp)) : (events[i][0]);
        while (j <= events[i][1]) {
            if (hash[j] == 0) {
                hash[j] = 1;
                temp = j + 1;
                prev = events[i][0];
                ++retVal;
                break;
            }

            ++j;
        }
    }

    free(hash);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int events[MAX_SIZE][2];
        int eventsSize;
        int eventsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 3}, {3, 4}}, 3, {2, 2, 2}}, {{{1, 2}, {2, 3}, {3, 4}, {1, 2}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: events = [[1,2],[2,3],[3,4]]
     *  Output: 3
     *
     *  Input: events= [[1,2],[2,3],[3,4],[1,2]]
     *  Output: 4
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
        answer = maxEvents(pEvents, testCase[i].eventsSize, testCase[i].eventsColSize);
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
