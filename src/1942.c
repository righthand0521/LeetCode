#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/the-number-of-the-smallest-unoccupied-chair/solutions/1102966/zui-xiao-wei-bei-zhan-ju-yi-zi-de-bian-h-tjlc/
int compareIntArray(const void *a1, const void *a2) {
    int *p1 = *(int **)a1;
    int *p2 = *(int **)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int smallestChair(int **times, int timesSize, int *timesColSize, int targetFriend) {
    int retVal = 0;

    int arriveTime = times[targetFriend][0];

    qsort(times, timesSize, sizeof(int *), compareIntArray);

    int seat[arriveTime];
    memset(seat, 0, sizeof(seat));
    int i = 0;
    int j = 0;
    while ((timesSize > i) && (times[i][0] <= arriveTime)) {
        j = 0;
        while ((arriveTime > j) && (seat[j] > times[i][0])) {
            j++;
        }

        if (arriveTime > j) {
            seat[j] = times[i][1];
        }

        i++;
    }
    retVal = j;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int times[MAX_SIZE][2];
        int timesSize;
        int timesColSize[MAX_SIZE];
        int targetFriend;
    } testCase[] = {{{{1, 4}, {2, 3}, {4, 6}}, 3, {2, 2, 2}, 1}, {{{3, 10}, {1, 5}, {2, 6}}, 3, {2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
     *  Output: 1
     *
     *  Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
     *  Output: 2
     */

    int **pTimes = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: times = [");
        for (j = 0; j < testCase[i].timesSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].timesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].times[j][k]);
            }
            printf("]");
        }
        printf("], targetFriend = %d\n", testCase[i].targetFriend);

        pTimes = (int **)malloc(testCase[i].timesSize * sizeof(int *));
        if (pTimes == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].timesSize; ++j) {
            pTimes[j] = (int *)malloc(testCase[i].timesColSize[j] * sizeof(int));
            if (pTimes[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pTimes[k]);
                    pTimes[k] = NULL;
                }
                free(pTimes);
                pTimes = NULL;
                return EXIT_FAILURE;
            }
            memset(pTimes[j], 0, (testCase[i].timesColSize[j] * sizeof(int)));
            memcpy(pTimes[j], testCase[i].times[j], (testCase[i].timesColSize[j] * sizeof(int)));
        }
        answer = smallestChair(pTimes, testCase[i].timesSize, testCase[i].timesColSize, testCase[i].targetFriend);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].timesSize; ++j) {
            free(pTimes[j]);
            pTimes[j] = NULL;
        }
        free(pTimes);
        pTimes = NULL;
    }

    return EXIT_SUCCESS;
}
