#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }

    return (p1[0] > p2[0]);
}
int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    int retVal = 0;

    //
    qsort(meetings, meetingsSize, sizeof(meetings[0]), compareIntArray);

    //
    long long roomAvailabilityTime[n];
    memset(roomAvailabilityTime, 0, sizeof(roomAvailabilityTime));

    int meetingCount[n];
    memset(meetingCount, 0, sizeof(meetingCount));

    long long minRoomAvailabilityTime;
    int minAvailableTimeRoom;
    bool foundUnusedRoom;
    int start, end;

    int i, j;
    for (i = 0; i < meetingsSize; ++i) {
        start = meetings[i][0];
        end = meetings[i][1];

        minRoomAvailabilityTime = LLONG_MAX;
        minAvailableTimeRoom = 0;
        foundUnusedRoom = false;

        for (j = 0; j < n; ++j) {
            if (roomAvailabilityTime[j] <= start) {
                foundUnusedRoom = true;
                meetingCount[j]++;
                roomAvailabilityTime[j] = end;
                break;
            }

            if (minRoomAvailabilityTime > roomAvailabilityTime[j]) {
                minRoomAvailabilityTime = roomAvailabilityTime[j];
                minAvailableTimeRoom = j;
            }
        }

        if (foundUnusedRoom == false) {
            roomAvailabilityTime[minAvailableTimeRoom] += (end - start);
            meetingCount[minAvailableTimeRoom]++;
        }
    }

    //
    int maxMeetingCount = 0;
    int maxMeetingCountRoom = 0;
    for (i = 0; i < n; i++) {
        if (meetingCount[i] > maxMeetingCount) {
            maxMeetingCount = meetingCount[i];
            maxMeetingCountRoom = i;
        }
    }
    retVal = maxMeetingCountRoom;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int meetings[MAX_SIZE][2];
        int meetingsSize;
        int meetingsColSize[MAX_SIZE];
    } testCase[] = {{2, {{0, 10}, {1, 5}, {2, 7}, {3, 4}}, 4, {2, 2, 2, 2}},
                    {3, {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
     *  Output: 0
     *
     *  Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
     *  Output: 1
     */

    int** pMeetings = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, meetings = [", testCase[i].n);
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].meetingsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].meetings[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMeetings = (int**)malloc(testCase[i].meetingsSize * sizeof(int*));
        if (pMeetings == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pMeetings, 0, testCase[i].meetingsSize * sizeof(int*));
        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            pMeetings[j] = (int*)malloc(testCase[i].meetingsColSize[j] * sizeof(int));
            if (pMeetings[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pMeetings[k]);
                    pMeetings[k] = NULL;
                }
                free(pMeetings);
                pMeetings = NULL;
            }
            memset(pMeetings[j], 0, (testCase[i].meetingsColSize[j] * sizeof(int)));
            memcpy(pMeetings[j], testCase[i].meetings[j], (testCase[i].meetingsColSize[j] * sizeof(int)));
        }
        answer = mostBooked(testCase[i].n, pMeetings, testCase[i].meetingsSize, testCase[i].meetingsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].meetingsSize; ++j) {
            free(pMeetings[j]);
            pMeetings[j] = NULL;
        }
        free(pMeetings);
        pMeetings = NULL;
    }

    return EXIT_SUCCESS;
}
