#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxCoins(int* piles, int pilesSize) {
    int retVal = 0;

    qsort(piles, pilesSize, sizeof(int), compareInteger);

    int left = 0;
    int right = pilesSize - 1;
    while (left < right) {
        --right;
        retVal += piles[right];
        --right;
        ++left;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int piles[MAX_SIZE];
        int pilesSize;
    } testCase[] = {{{2, 4, 1, 2, 7, 8}, 6}, {{2, 4, 5}, 3}, {{9, 8, 7, 6, 5, 1, 2, 3, 4}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: piles = [2,4,1,2,7,8]
     *  Output: 9
     *
     *  Input: piles = [2,4,5]
     *  Output: 4
     *
     *  Input: piles = [9,8,7,6,5,1,2,3,4]
     *  Output: 18
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: piles = [");
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].piles[j]);
        }
        printf("]\n");

        answer = maxCoins(testCase[i].piles, testCase[i].pilesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
