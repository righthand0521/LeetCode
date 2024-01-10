#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEDY (1)
#define DYNAMIC_PROGRAMMING (1)
int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
#if (GREEDY)
    if (p1[1] == p2[1]) {
        return (p1[0] > p2[0]);
    }
    return (p1[1] > p2[1]);
#elif (DYNAMIC_PROGRAMMING)
    if (p1[0] == p2[0]) {
        return (p1[1] > p2[1]);
    }
    return (p1[0] > p2[0]);
#endif
}
int findLongestChain(int** pairs, int pairsSize, int* pairsColSize) {
    int retVal = 0;

#if (GREEDY)
    printf("Greedy\n");

    qsort(pairs, pairsSize, sizeof(int*), compareIntArray);

    int preRight = -1001;  // -1000 <= lefti < righti <= 1000
    int left, right;
    int i;
    for (i = 0; i < pairsSize; ++i) {
        left = pairs[i][0];
        right = pairs[i][1];

        if (left > preRight) {
            ++retVal;
            preRight = right;
        }
    }
#elif (DYNAMIC_PROGRAMMING)
    printf("Dynamic Programming\n");

    qsort(pairs, pairsSize, sizeof(int*), compareIntArray);

    // dp[i] will store the length of the longest chain starting from pair i
    int dp[pairsSize];
    memset(dp, 0, sizeof(dp));

    int preRight, left;
    int i, j;
    for (i = 0; i < pairsSize; ++i) {
        dp[i] = 1;
    }
    for (i = pairsSize - 1; i >= 0; --i) {
        preRight = pairs[i][1];
        for (j = i + 1; j < pairsSize; ++j) {
            left = pairs[j][0];
            if (preRight < left) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        retVal = fmax(retVal, dp[i]);
    }

#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int pairs[MAX_SIZE][2];
        int pairsSize;
        int pairsColSize[MAX_SIZE];
    } testCase[] = {
        {{{1, 2}, {2, 3}, {3, 4}}, 3, {2, 2, 2}},
        {{{1, 2}, {7, 8}, {4, 5}}, 3, {2, 2, 2}},
        {{{1, 2}, {2, 5}, {3, 9}, {6, 7}, {8, 9}}, 5, {2, 2, 2, 2, 2}},
        {{{7, 9}, {4, 5}, {7, 9}, {-7, -1}, {0, 10}, {3, 10}, {3, 6}, {2, 3}}, 8, {2, 2, 2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pairs = [[1,2],[2,3],[3,4]]
     *  Output: 2
     *
     *  Input: pairs = [[1,2],[7,8],[4,5]]
     *  Output: 3
     *
     *  Input: pairs = [[1,2],[2,5],[3,9],[6,7],[8,9]]
     *  Output: 3
     *
     *  Input: pairs = [[7,9],[4,5],[7,9],[-7,-1],[0,10],[3,10],[3,6],[2,3]]
     *  Output: 4
     */

    int** pPairs = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pairs = [");
        for (j = 0; j < testCase[i].pairsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pairsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].pairs[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPairs = (int**)malloc(testCase[i].pairsSize * sizeof(int*));
        if (pPairs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pairsSize; ++j) {
            pPairs[j] = (int*)malloc(testCase[i].pairsColSize[j] * sizeof(int));
            if (pPairs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPairs[k]);
                }
                free(pPairs);
                return EXIT_FAILURE;
            }
            memset(pPairs[j], 0, (testCase[i].pairsColSize[j] * sizeof(int)));
            memcpy(pPairs[j], testCase[i].pairs[j], (testCase[i].pairsColSize[j] * sizeof(int)));
        }
        answer = findLongestChain(pPairs, testCase[i].pairsSize, testCase[i].pairsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pairsSize; ++j) {
            free(pPairs[j]);
        }
        free(pPairs);
        pPairs = NULL;
    }

    return EXIT_SUCCESS;
}
