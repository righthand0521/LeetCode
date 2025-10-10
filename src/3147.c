#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximumEnergy(int* energy, int energySize, int k) {
    int retVal = INT_MIN;

    int sum;
    for (int i = energySize - k; i < energySize; i++) {
        sum = 0;
        for (int j = i; j >= 0; j -= k) {
            sum += energy[j];
            if (sum > retVal) {
                retVal = sum;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int energy[MAX_SIZE];
        int energySize;
        int k;
    } testCase[] = {{{5, 2, -10, -5, 1}, 5, 3}, {{-2, -3, -1}, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: energy = [5,2,-10,-5,1], k = 3
     *  Output: 3
     *
     *  Input: energy = [-2,-3,-1], k = 2
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: energy = [");
        for (j = 0; j < testCase[i].energySize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].energy[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumEnergy(testCase[i].energy, testCase[i].energySize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
