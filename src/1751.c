#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order by Array[][0]
    return ((p1[0] > p2[0]) ? (1) : (-1));
}
int dfs(int** events, int eventsSize, int k, int** dp, int index, int count, int previousEndDay) {
    int retVal = 0;

    if ((index == eventsSize) || (count == k)) {
        return retVal;
    }

    if (events[index][0] <= previousEndDay) {
        retVal = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
    } else if (dp[count][index] != -1) {
        retVal = dp[count][index];
    } else {
        int ans1 = dfs(events, eventsSize, k, dp, index + 1, count, previousEndDay);
        int ans2 = dfs(events, eventsSize, k, dp, index + 1, count + 1, events[index][1]) + events[index][2];
        retVal = fmax(ans1, ans2);
        dp[count][index] = retVal;
    }

    return retVal;
}
int maxValue(int** events, int eventsSize, int* eventsColSize, int k) {
    int retVal = 0;

    int i, j;

    qsort(events, eventsSize, sizeof(events[0]), compareIntArray);

    int** pDp = (int**)malloc((k + 1) * sizeof(int*));
    if (pDp == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pDp, 0, ((k + 1) * sizeof(int*)));
    for (i = 0; i < (k + 1); ++i) {
        pDp[i] = (int*)malloc(eventsSize * sizeof(int));
        if (pDp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pDp[i]);
                pDp[j] = NULL;
            }
            free(pDp);
            pDp = NULL;
        }
        memset(pDp[i], -1, (eventsSize * sizeof(int)));
    }
    int index = 0;
    int count = 0;
    int previousEndDay = -1;
    retVal = dfs(events, eventsSize, k, pDp, index, count, previousEndDay);

    //
    for (i = 0; i < (k + 1); ++i) {
        free(pDp[i]);
        pDp[i] = NULL;
    }
    free(pDp);
    pDp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int events[MAX_SIZE][3];
        int eventsSize;
        int eventsColSize[MAX_SIZE];
        int k;
    } testCase[] = {{{{1, 2, 4}, {3, 4, 3}, {2, 3, 1}}, 3, {3, 3, 3}, 2},
                    {{{1, 2, 4}, {3, 4, 3}, {2, 3, 10}}, 3, {3, 3, 3}, 2},
                    {{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}}, 4, {3, 3, 3, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
     *  Output: 7
     *
     *  Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
     *  Output: 10
     *
     *  Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
     *  Output: 9
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
        printf("], k = %d\n", testCase[i].k);

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
        answer = maxValue(pEvents, testCase[i].eventsSize, testCase[i].eventsColSize, testCase[i].k);
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
