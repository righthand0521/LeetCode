#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long maxRunTime(int n, int* batteries, int batteriesSize) {
    long long retVal = 0;

    int i;

    long sumPower = 0;
    for (i = 0; i < batteriesSize; ++i) {
        sumPower += batteries[i];
    }

    long long middle;
    long long left = 1;
    long long right = sumPower / n;
    while (left < right) {
        middle = right - (right - left) / 2;

        long long total = 0;
        for (i = 0; i < batteriesSize; ++i) {
            total += fmin(batteries[i], middle);
        }
        if (total >= (long long)(n * middle)) {
            left = middle;
        } else {
            right = middle - 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int batteries[MAX_SIZE];
        int batteriesSize;
    } testCase[] = {{2, {3, 3, 3}, 3}, {2, {1, 1, 1, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, batteries = [3,3,3]
     *  Output: 4
     *
     *  Input: n = 2, batteries = [1,1,1,1]
     *  Output: 2
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, dist = [", testCase[i].n);
        for (j = 0; j < testCase[i].batteriesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].batteries[j]);
        }
        printf("]\n");

        answer = maxRunTime(testCase[i].n, testCase[i].batteries, testCase[i].batteriesSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
