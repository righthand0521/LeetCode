#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUICK_SORT (1)
#define COUNT_SORT (1)
#if (QUICK_SORT)
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
#elif (COUNT_SORT)
#include <math.h>
#endif
int maxIceCream(int* costs, int costsSize, int coins) {
    int retVal = 0;

#if (QUICK_SORT)
    printf("QUICK_SORT\n");

    qsort(costs, costsSize, sizeof(int), compareInteger);
    for (retVal = 0; retVal < costsSize; ++retVal) {
        if (costs[retVal] > coins) {
            break;
        }
        coins -= costs[retVal];
    }
#elif (COUNT_SORT)
    printf("COUNT_SORT\n");

#define MAX_COUNT (int)(1e5 + 1)
    int CountSort[MAX_COUNT];
    memset(CountSort, 0, sizeof(CountSort));

    int i;
    for (i = 0; i < costsSize; ++i) {
        ++CountSort[costs[i]];
    }

    int count;
    for (i = 1; i < MAX_COUNT; ++i) {
        if (i > coins) {
            break;
        }
        count = fmin(CountSort[i], coins / i);
        retVal += count;
        coins -= i * count;
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        int costs[MAX_SIZE];
        int costsSize;
        int coins;
    } testCase[] = {{{1, 3, 2, 4, 1}, 5, 7}, {{10, 6, 8, 7, 7, 8}, 6, 5}, {{1, 6, 3, 1, 2, 5}, 6, 20}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: costs = [");
        for (j = 0; j < testCase[i].costsSize; ++j) {
            printf("%s%d", ((j == 0) ? "" : ","), testCase[i].costs[j]);
        }
        printf("], coins = %d\n", testCase[i].coins);

        answer = maxIceCream(testCase[i].costs, testCase[i].costsSize, testCase[i].coins);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
