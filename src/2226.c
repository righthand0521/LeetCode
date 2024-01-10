#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumCandies(int *candies, int candiesSize, long long k) {
    int retVal = 0;

    int i;

    int maxCandies = candies[0];
    for (i = 1; i < candiesSize; ++i) {
        maxCandies = fmax(maxCandies, candies[i]);
    }

    long long tmpCandies;
    int middle;
    int left = 1;
    int right = 1 + maxCandies;
    while (left < right) {
        middle = left + (right - left) / 2;

        tmpCandies = 0;
        for (i = 0; i < candiesSize; ++i) {
            tmpCandies += (candies[i] / middle);
        }

        if (tmpCandies >= k) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left - 1;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int candies[MAX_SIZE];
        int candiesSize;
        long long k;
    } testCase[] = {{{5, 8, 6}, 3, 3},
                    {{2, 5}, 2, 11},
                    {{1, 2, 3, 4, 10}, 5, 5},
                    {{4, 7, 5}, 3, 16},
                    {{5, 6, 4, 10, 10, 1, 1, 2, 2, 2}, 10, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: candies = [5,8,6], k = 3
     *  Output: 5
     *
     *  Input: candies = [2,5], k = 11
     *  Output: 0
     *
     *  Input: candies = [1, 2, 3, 4, 10], k = 5
     *  Output: 3
     *
     *  Input: candies = [4, 7, 5], k = 16
     *  Output: 1
     *
     *  Input: candies = [5, 6, 4, 10, 10, 1, 1, 2, 2, 2], k = 9
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: time = [");
        for (j = 0; j < testCase[i].candiesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].candies[j]);
        }
        printf("], k = %lld\n", testCase[i].k);

        answer = maximumCandies(testCase[i].candies, testCase[i].candiesSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
