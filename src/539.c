#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findMinDifference(char** timePoints, int timePointsSize) {
    int retVal = 0;

    int minutesSize = timePointsSize;
    int minutes[minutesSize];
    memset(minutes, 0, sizeof(minutes));

    int i;
    for (i = 0; i < timePointsSize; ++i) {
        minutes[i] += ((10 * (timePoints[i][0] - '0') + timePoints[i][1] - '0') * 60);
        minutes[i] += ((10 * (timePoints[i][3] - '0') + timePoints[i][4] - '0') * 1);
    }
    qsort(minutes, minutesSize, sizeof(int), compareInteger);

    retVal = 24 * 60 - minutes[minutesSize - 1] + minutes[0];
    for (i = 0; i < (minutesSize - 1); ++i) {
        retVal = fmin(retVal, minutes[i + 1] - minutes[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 10000)
    struct testCaseType {
        char* timePoints[MAX_SIZE];
        int timePointsSize;
    } testCase[] = {{{"23:59", "00:00"}, 2}, {{"00:00", "23:59", "00:00"}, 3}, {{"01:01", "02:01"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: timePoints = ["23:59","00:00"]
     *  Output: 1
     *
     *  Input: timePoints = ["00:00","23:59","00:00"]
     *  Output: 0
     *
     *  Input: timePoints = ["01:01","02:01"]
     *  Output: 60
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tokens = [");
        for (j = 0; j < testCase[i].timePointsSize; ++j) {
            printf("\"%s\"%s", testCase[i].timePoints[j], (j == (testCase[i].timePointsSize - 1) ? "" : ","));
        }
        printf("]\n");

        answer = findMinDifference(testCase[i].timePoints, testCase[i].timePointsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
