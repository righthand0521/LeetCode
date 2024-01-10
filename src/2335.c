#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRUTE_FORCE (1)
#define MATH_1 (1)
#define MATH_2 (1)
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int fillCups(int* amount, int amountSize) {
    int retVal = 0;

#if (BRUTE_FORCE)
    printf("BRUTE_FORCE\n");

    /* Intuition
     *  142: 131, 021, 010, 000
     *  544: 434, 333, 223, 122, 111, 001, 000
     *  500: 400, 300, 200, 100, 000
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    while (amount[0] > 0) {
        if (amount[0] > 0) {
            amount[0] -= 1;
        }

        if (amount[1] > 0) {
            amount[1] -= 1;
        }

        ++retVal;

        qsort(amount, amountSize, sizeof(int), compareInteger);
    }
#elif (MATH_1)
    printf("MATH_1\n");

    /* https://leetcode.cn/problems/minimum-amount-of-time-to-fill-cups/solutions/1658941/by-tsreaper-158c/
     *  Let amount[2] < amount[1] < amount[0]
     *  1. If amount[2] + amount[1] <= amount[0]
     *     => amount[0] is the minimum number of seconds needed
     *  2. If amount[2] + amount[1] > amount[0]
     *     Let Exceed = amount[2] + amount[1] - amount[0]
     *     if Exceed is even: (Exceed / 2) + amount[0] is the minimum number of seconds needed
     *     => (Exceed / 2) + amount[0]
     *        = (amount[2] + amount[1] - amount[0]) / 2 + amount[0]
     *        = (amount[2] + amount[1] + amount[0]) / 2
     *     if Exceed is odd: ((Exceed - 1) / 2) + amount[0] + 1 is the minimum number of seconds needed
     *     => ((Exceed - 1) / 2) + amount[0] + 1
     *        = (amount[2] + amount[1] - amount[0] - 1) / 2 + amount[0] + 1
     *        = (amount[2] + amount[1] + amount[0] + 1) / 2
     */
    qsort(amount, amountSize, sizeof(int), compareInteger);
    if ((amount[1] + amount[2]) <= amount[0]) {
        retVal = amount[0];
    } else {
        retVal = (amount[2] + amount[1] + amount[0] + 1) / 2;
    }
#elif (MATH_2)
    printf("MATH_2\n");

    /* https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/solutions/2261394/java-c-python-max-max-a-sum-a-1-2/
     *  Let amount[2] < amount[1] < amount[0]
     *  Max between amount[0] and (amount[2] + amount[1] + amount[0] + 1) / 2 is the minimum number of seconds needed
     */
    int maxAmount = 0;
    int i;
    for (i = 0; i < amountSize; ++i) {
        maxAmount = fmax(maxAmount, amount[i]);
        retVal += amount[i];
    }
    retVal = (retVal + 1) / 2;
    retVal = fmax(retVal, maxAmount);
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3)
    struct testCaseType {
        int amount[MAX_SIZE];
        int amountSize;
    } testCase[] = {{{1, 4, 2}, 3}, {{5, 4, 4}, 3}, {{5, 0, 0}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: amount =  [");
        for (j = 0; j < testCase[i].amountSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].amount[j]);
        }
        printf("]\n");

        answer = fillCups(testCase[i].amount, testCase[i].amountSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
