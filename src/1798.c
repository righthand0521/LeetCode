#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int getMaximumConsecutive(int* coins, int coinsSize) {
    int retVal = 1;

    qsort(coins, coinsSize, sizeof(int), compareInteger);

    int i;
    for (i = 0; i < coinsSize; ++i) {
        // Return the maximum number of consecutive integer values
        // that you can make with your coins starting from and including 0.
        if (coins[i] > retVal) {
            break;
        }
        retVal += coins[i];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (4 * ((int)(1e4)))
    struct testCaseType {
        int coins[MAX_SIZE];
        int coinsSize;
    } testCase[] = {
        {{1, 3}, 2},
        {{1, 1, 1, 4}, 4},
        {{1, 4, 10, 3, 1}, 5},
        {{1, 89, 8, 1, 47, 34, 99, 1, 1, 1, 55, 89, 1, 52, 36, 1, 62, 1, 1, 1, 4, 27, 1, 45, 1, 1, 48, 1, 94, 1, 63},
         31},
        {{2, 3, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: coins = [");
        for (j = 0; j < testCase[i].coinsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].coins[j]);
        }
        printf("]\n");

        answer = getMaximumConsecutive(testCase[i].coins, testCase[i].coinsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
