#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSpeedOnTime(int* dist, int distSize, double hour) {
    int retVal = -1;

    if ((double)(distSize - 1) >= hour) {
        return retVal;
    }

    int i;
    double totalHour;
    int middle;
    // Tests are generated such that the answer will not exceed 10^7
    // and hour will have at most two digits after the decimal point.
    int left = 1;
    int right = 1e7;
    while (left < right) {
        middle = left + (right - left) / 2;

        /* Example: dist = [1,3,2], hour = 2.7
         *  Speed   Time Required
         *    1     (1/1) + (3/1) + (2/1) = 6
         *    2     (1/2) + (3/2) + (2/2) = 1 + 2 + 1 = 4
         *    3     (1/3) + (3/3) + (2/3) = 1 + 1 + 0.67 = 2.67
         *
         *   10^7
         */
        totalHour = 0;
        for (i = 0; i < distSize - 1; ++i) {
            totalHour += ((dist[i] + middle - 1) / middle);
        }
        totalHour += (((double)dist[i]) / middle);

        if (totalHour > hour) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int dist[MAX_SIZE];
        int distSize;
        double hour;
    } testCase[] = {{{1, 3, 2}, 3, 6}, {{1, 3, 2}, 3, 2.7}, {{1, 3, 2}, 3, 1.9}, {{1, 1, 100000}, 3, 2.01}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dist = [1,3,2], hour = 6
     *  Output: 1
     *
     *  Input: dist = [1,3,2], hour = 2.7
     *  Output: 3
     *
     *  Input: dist = [1,3,2], hour = 1.9
     *  Output: -1
     *
     *  Input: dist = [1,1,100000], hour = 2.01
     *  Output: 10000000
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dist = [");
        for (j = 0; j < testCase[i].distSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].dist[j]);
        }
        printf("], hour = %f\n", testCase[i].hour);

        answer = minSpeedOnTime(testCase[i].dist, testCase[i].distSize, testCase[i].hour);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
