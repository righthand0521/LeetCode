#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findPoisonedDuration(int* timeSeries, int timeSeriesSize, int duration) {
    int retVal = 0;

    int expired = 0;
    int i;
    for (i = 0; i < timeSeriesSize; ++i) {
        if (timeSeries[i] >= expired) {
            retVal += duration;
        } else {
            retVal += (timeSeries[i] + duration - expired);
        }
        expired = timeSeries[i] + duration;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int timeSeries[MAX_SIZE];
        int timeSeriesSize;
        int duration;
    } testCase[] = {{{1, 4}, 2, 2}, {{1, 2}, 2, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: timeSeries = [1,4], duration = 2
     *  Output: 4
     *
     *  Input: timeSeries = [1,2], duration = 2
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: timeSeriesSize = [");
        for (j = 0; j < testCase[i].timeSeriesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].timeSeries[j]);
        }
        printf("], duration = %d\n", testCase[i].duration);

        answer = findPoisonedDuration(testCase[i].timeSeries, testCase[i].timeSeriesSize, testCase[i].duration);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
