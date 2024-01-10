#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shipWithinDays(int *weights, int weightsSize, int days) {
    int retVal = 0;

    int i;

    int left = 0;
    int right = 0;
    for (i = 0; i < weightsSize; ++i) {
        left = fmax(left, weights[i]);
        right += weights[i];
    }

    int middle;
    int useDays;
    int capacity;
    while (left < right) {
        middle = left + (right - left) / 2;

        useDays = 1;
        capacity = 0;
        for (i = 0; i < weightsSize; ++i) {
            capacity += weights[i];
            if (capacity > middle) {
                capacity = weights[i];
                useDays += 1;
            }
        }

        if (useDays > days) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int weights[MAX_SIZE];
        int weightsSize;
        int days;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10, 5}, {{3, 2, 2, 4, 1, 4}, 6, 3}, {{1, 2, 3, 1, 1}, 5, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
     *  Output: 15
     *
     *  Input: weights = [3,2,2,4,1,4], days = 3
     *  Output: 6
     *
     *  Input: weights = [1,2,3,1,1], days = 4
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: weights = [");
        for (j = 0; j < testCase[i].weightsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].weights[j]);
        }
        printf("], days = %d\n", testCase[i].days);

        answer = shipWithinDays(testCase[i].weights, testCase[i].weightsSize, testCase[i].days);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
