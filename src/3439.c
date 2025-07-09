#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxFreeTime(int eventTime, int k, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int retVal = 0;

    int t = 0, left, right;
    for (int i = 0; i < startTimeSize; i++) {
        t += (endTime[i] - startTime[i]);
        left = (i <= k - 1) ? (0) : (endTime[i - k]);
        right = (i == startTimeSize - 1) ? (eventTime) : (startTime[i + 1]);
        if (right - left - t > retVal) {
            retVal = right - left - t;
        }
        if (i >= k - 1) {
            t -= (endTime[i - k + 1] - startTime[i - k + 1]);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int eventTime;
        int k;
        int startTime[MAX_SIZE];
        int startTimeSize;
        int endTime[MAX_SIZE];
        int endTimeSize;
    } testCase[] = {{5, 1, {1, 3}, 2, {2, 5}, 2},
                    {10, 1, {0, 2, 9}, 3, {1, 4, 10}, 3},
                    {5, 2, {0, 1, 2, 3, 4}, 5, {1, 2, 3, 4, 5}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
     *  Output: 2
     *
     *  Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
     *  Output: 6
     *
     *  Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: eventTime = %d, k = %d, startTime = [", testCase[i].eventTime, testCase[i].k);
        for (j = 0; j < testCase[i].startTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].startTime[j]);
        }
        printf("], endTime = [");
        for (j = 0; j < testCase[i].endTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].endTime[j]);
        }
        printf("]\n");

        answer = maxFreeTime(testCase[i].eventTime, testCase[i].k, testCase[i].startTime, testCase[i].startTimeSize,
                             testCase[i].endTime, testCase[i].endTimeSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
