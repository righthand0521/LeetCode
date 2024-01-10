#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(int jobs[][3], int right, int target) {
    int retVal = 0;

    int left = 0;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (jobs[middle][1] > target) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}
int compareIntArray(const void* a1, const void* a2) {
    int* p1 = (int*)a1;
    int* p2 = (int*)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    int retVal = 0;

    int n = startTimeSize;

    int jobs[n][3];
    int i;
    for (i = 0; i < n; ++i) {
        jobs[i][0] = startTime[i];
        jobs[i][1] = endTime[i];
        jobs[i][2] = profit[i];
    }
    qsort(jobs, n, sizeof(jobs[0]), compareIntArray);

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    int k;
    for (i = 1; i <= n; ++i) {
        k = binarySearch(jobs, i - 1, jobs[i - 1][0]);
        dp[i] = fmax(dp[i - 1], dp[k] + jobs[i - 1][2]);
    }
    retVal = dp[n];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int startTime[MAX_SIZE];
        int startTimeSize;
        int endTime[MAX_SIZE];
        int endTimeSize;
        int profit[MAX_SIZE];
        int profitSize;
    } testCase[] = {{{1, 2, 3, 3}, 4, {3, 4, 5, 6}, 4, {50, 10, 40, 70}, 4},
                    {{1, 2, 3, 4, 6}, 5, {3, 5, 10, 6, 9}, 5, {20, 20, 100, 70, 60}, 5},
                    {{1, 1, 1}, 3, {2, 3, 4}, 3, {5, 6, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
     *  Output: 120
     *
     *  Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
     *  Output: 150
     *
     *  Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: startTime = [");
        for (j = 0; j < testCase[i].startTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].startTime[j]);
        }
        printf("], endTime = [");
        for (j = 0; j < testCase[i].endTimeSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].endTime[j]);
        }
        printf("], profit = [");
        for (j = 0; j < testCase[i].profitSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].profit[j]);
        }
        printf("]\n");

        answer = jobScheduling(testCase[i].startTime, testCase[i].startTimeSize, testCase[i].endTime,
                               testCase[i].endTimeSize, testCase[i].profit, testCase[i].profitSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
