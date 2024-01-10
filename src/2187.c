#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minimumTime(int *time, int timeSize, int totalTrips) {
    long long retVal = 0;

    long long minTime = time[0];
    int i;
    for (i = 1; i < timeSize; ++i) {
        minTime = fmin(minTime, time[i]);
    }

    long long tmpTrip = 0;
    long long middle;
    long long left = 1;
    long long right = (long long)totalTrips * minTime;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpTrip = 0;
        for (i = 0; i < timeSize; ++i) {
            tmpTrip += (middle / time[i]);
        }

        if (tmpTrip < totalTrips) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int time[MAX_SIZE];
        int timeSize;
        int totalTrips;
    } testCase[] = {{{1, 2, 3}, 3, 5}, {{2}, 1, 1}, {{5, 10, 10}, 3, 9}, {{1}, 1, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: time = [1,2,3], totalTrips = 5
     *  Output: 3
     *
     *  Input: time = [2], totalTrips = 1
     *  Output: 2
     *
     *  Input: time = [5,10,10], totalTrips = 9
     *  Output: 25
     *
     *  Input: time = [1], totalTrips = 4
     *  Output: 4
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: time = [");
        for (j = 0; j < testCase[i].timeSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].time[j]);
        }
        printf("], totalTrips = %d\n", testCase[i].totalTrips);

        answer = minimumTime(testCase[i].time, testCase[i].timeSize, testCase[i].totalTrips);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
