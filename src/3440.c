#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxFreeTime(int eventTime, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int retVal = 0;

    bool* q = (bool*)calloc(startTimeSize, sizeof(bool));
    if (q == NULL) {
        perror("malloc");
        return retVal;
    }

    int t1 = 0, t2 = 0;
    for (int i = 0; i < startTimeSize; i++) {
        if (endTime[i] - startTime[i] <= t1) {
            q[i] = true;
        }
        t1 = fmax(t1, startTime[i] - ((i == 0) ? (0) : (endTime[i - 1])));

        if (endTime[startTimeSize - i - 1] - startTime[startTimeSize - i - 1] <= t2) {
            q[startTimeSize - i - 1] = true;
        }
        t2 = fmax(t2, ((i == 0) ? (eventTime) : (startTime[startTimeSize - i])) - endTime[startTimeSize - i - 1]);
    }

    for (int i = 0; i < startTimeSize; i++) {
        int left = (i == 0) ? (0) : (endTime[i - 1]);
        int right = (i == startTimeSize - 1) ? (eventTime) : (startTime[i + 1]);
        if (q[i] == true) {
            retVal = fmax(retVal, right - left);
        } else {
            retVal = fmax(retVal, right - left - (endTime[i] - startTime[i]));
        }
    }

    //
    free(q);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int eventTime;
        int startTime[MAX_SIZE];
        int startTimeSize;
        int endTime[MAX_SIZE];
        int endTimeSize;
    } testCase[] = {{5, {1, 3}, 2, {2, 5}, 2},
                    {10, {0, 7, 9}, 3, {1, 8, 10}, 3},
                    {10, {0, 3, 7, 9}, 4, {1, 4, 8, 10}, 4},
                    {5, {0, 1, 2, 3, 4}, 5, {1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
     *  Output: 2
     *
     *  Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
     *  Output: 7
     *
     *  Input: eventTime = 10, startTime = [0,3,7,9], endTime = [1,4,8,10]
     *  Output: 6
     *
     *  Input: eventTime = 5, startTime = [0, 1, 2, 3, 4], endTime = [1, 2, 3, 4, 5]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: eventTime = %d,  startTime = [", testCase[i].eventTime);
        for (j = 0; j < testCase[i].startTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].startTime[j]);
        }
        printf("], endTime = [");
        for (j = 0; j < testCase[i].endTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].endTime[j]);
        }
        printf("]\n");

        answer = maxFreeTime(testCase[i].eventTime, testCase[i].startTime, testCase[i].startTimeSize,
                             testCase[i].endTime, testCase[i].endTimeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
