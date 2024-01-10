#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE (1)
#if (SPACE)
#else
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#endif
int minStoneSum(int* piles, int pilesSize, int k) {
    int retVal = 0;

#if (SPACE)
    printf("if\n");

#define MAX_OPERATION (10000)
    int Count[MAX_OPERATION + 1];
    memset(Count, 0, sizeof(Count));
    int idx = MAX_OPERATION;

    int i;
    for (i = 0; i < pilesSize; ++i) {
        Count[piles[i]] += piles[i];
    }

    int tmp;
    while (k > 0) {
        if (Count[idx] == 0) {
            --idx;
            continue;
        }
        Count[idx] -= idx;
        tmp = idx - idx / 2;
        Count[tmp] += tmp;

        k--;
    }

    for (i = 0; i <= MAX_OPERATION; ++i) {
        retVal += Count[i];
    }
#else
    printf("else\n");

    int i;
    for (i = 0; i < pilesSize; ++i) {
        retVal += piles[i];
    }
    qsort(piles, pilesSize, sizeof(int), compareInteger);

    i = 0;
    int remove;
    while (k > 0) {
        remove = piles[i] / 2;
        piles[i] -= remove;
        retVal -= remove;

        if ((i < (pilesSize - 1)) && (piles[i] < piles[i + 1]) && (piles[0] <= piles[i + 1])) {
            ++i;
        } else if ((i == (pilesSize - 1)) || (piles[0] > piles[i + 1])) {
            qsort(piles, pilesSize, sizeof(int), compareInteger);
            i = 0;
        }

        --k;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int piles[MAX_SIZE];
        int pilesSize;
        int k;
    } testCase[] = {{{5, 4, 9}, 3, 2}, {{4, 3, 6, 7}, 4, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: piles = [");
        for (j = 0; j < testCase[i].pilesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].piles[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minStoneSum(testCase[i].piles, testCase[i].pilesSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
