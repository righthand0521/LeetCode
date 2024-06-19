#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDays(int* bloomDay, int bloomDaySize, int m, int k) {
    int retVal = -1;

    long flowers = (long)m * (long)k;
    if (flowers > bloomDaySize) {
        return retVal;
    }

    int left = 0;
    int right = bloomDay[0];
    int i;
    for (i = 1; i < bloomDaySize; ++i) {
        right = fmax(right, bloomDay[i]);
    }

    int bouquets, count;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;

        bouquets = 0;
        count = 0;
        for (i = 0; i < bloomDaySize; ++i) {
            if (bloomDay[i] <= middle) {
                count += 1;
            } else {
                count = 0;
            }

            if (count == k) {
                bouquets += 1;
                count = 0;
            }
        }

        if (bouquets >= m) {
            retVal = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int bloomDay[MAX_SIZE];
        int bloomDaySize;
        int m;
        int k;
    } testCase[] = {{{1, 10, 3, 10, 2}, 5, 3, 1}, {{1, 10, 3, 10, 2}, 5, 3, 2}, {{7, 7, 7, 7, 12, 7, 7}, 7, 2, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
     *  Output: 3
     *
     *  Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
     *  Output: -1
     *
     *  Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
     *  Output: 12
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bloomDay = [");
        for (j = 0; j < testCase[i].bloomDaySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].bloomDay[j]);
        }
        printf("], m = %d, k = %d\n", testCase[i].m, testCase[i].k);

        answer = minDays(testCase[i].bloomDay, testCase[i].bloomDaySize, testCase[i].m, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
