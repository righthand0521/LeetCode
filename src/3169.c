#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *a1, const void *a2) {
    const int *p1 = *(const int **)a1;
    const int *p2 = *(const int **)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int countDays(int days, int **meetings, int meetingsSize, int *meetingsColSize) {
    int retVal = 0;

    qsort(meetings, meetingsSize, sizeof(meetings[0]), compareIntArray);

    int latestEnd = 0;
    for (int i = 0; i < meetingsSize; ++i) {
        int start = meetings[i][0];
        int end = meetings[i][1];

        // Add current range of days without a meeting
        if (start > latestEnd + 1) {
            retVal += start - latestEnd - 1;
        }

        // Update latest meeting end
        latestEnd = fmax(latestEnd, end);
    }

    // Add all days after the last day of meetings
    retVal += days - latestEnd;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int days;
        int meetings[MAX_SIZE][2];
        int meetingsSize;
        int meetingsColSize[MAX_SIZE];
    } testCase[] = {
        {10, {{5, 7}, {1, 3}, {9, 10}}, 3, {2, 2, 2}}, {5, {{2, 4}, {1, 3}}, 2, {2, 2}}, {6, {{1, 6}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
     *  Output: 2
     *
     *  Input: days = 5, meetings = [[2,4],[1,3]]
     *  Output: 1
     *
     *  Input: days = 6, meetings = [[1,6]]
     *  Output: 0
     */

    int **pMeetings = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: days = %d, meetings = [", testCase[i].days);
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].meetingsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].meetings[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMeetings = (int **)malloc(testCase[i].meetingsSize * sizeof(int *));
        if (pMeetings == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            pMeetings[j] = (int *)malloc(testCase[i].meetingsColSize[j] * sizeof(int));
            if (pMeetings[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMeetings[k]) {
                        free(pMeetings[k]);
                        pMeetings[k] = NULL;
                    }
                }
                free(pMeetings);
                pMeetings = NULL;
                return EXIT_FAILURE;
            }
            memset(pMeetings[j], 0, testCase[i].meetingsColSize[j] * sizeof(int));
            memcpy(pMeetings[j], testCase[i].meetings[j], testCase[i].meetingsColSize[j] * sizeof(int));
        }
        answer = countDays(testCase[i].days, pMeetings, testCase[i].meetingsSize, testCase[i].meetingsColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            if (pMeetings[j]) {
                free(pMeetings[j]);
                pMeetings[j] = NULL;
            }
        }
        free(pMeetings);
        pMeetings = NULL;
    }

    return EXIT_SUCCESS;
}
