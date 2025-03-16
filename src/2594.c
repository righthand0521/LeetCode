#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long repairCars(int* ranks, int ranksSize, int cars) {
    long long retVal = 0;

    // The minimum possible time is 1
    // The maximum possible time is when the slowest mechanic (highest rank) repairs all cars
    long long left = 1;
    long long right = 1LL * cars * cars * ranks[0];
    while (left < right) {
        long long middle = left + (right - left) / 2;

        // Calculate the number of cars that can be repaired in 'middle' time by all mechanics.
        long long carsRepaired = 0;
        for (int i = 0; i < ranksSize; ++i) {
            carsRepaired += sqrt(1.0 * middle / ranks[i]);
        }

        // If the total cars repaired is less than required, increase the time. Otherwise, try a smaller time.
        if (carsRepaired < cars) {
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
        int ranks[MAX_SIZE];
        int ranksSize;
        int cars;
    } testCase[] = {{{4, 2, 3, 1}, 4, 10}, {{5, 1, 8}, 3, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: ranks = [4,2,3,1], cars = 10
     *  Output: 16
     *
     *  Input: ranks = [5,1,8], cars = 6
     *  Output: 16
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ranks = [");
        for (j = 0; j < testCase[i].ranksSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].ranks[j]);
        }
        printf("], cars = %d\n", testCase[i].cars);

        answer = repairCars(testCase[i].ranks, testCase[i].ranksSize, testCase[i].cars);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
