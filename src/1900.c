#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DP_SIZE (30)  // 2 <= n <= 28, 1 <= firstPlayer < secondPlayer <= n.
int F[DP_SIZE][DP_SIZE][DP_SIZE] = {0};
int G[DP_SIZE][DP_SIZE][DP_SIZE] = {0};
void dp(int n, int f, int s, int* earliest, int* latest) {
    if (F[n][f][s]) {
        *earliest = F[n][f][s];
        *latest = G[n][f][s];
        return;
    }

    if (f + s == n + 1) {
        (*earliest) = 1;
        (*latest) = 1;
        return;
    }

    // F(n,f,s) = F(n,n+1-s,n+1-f)
    int x, y;
    if (f + s > n + 1) {
        dp(n, n + 1 - s, n + 1 - f, &x, &y);
        F[n][f][s] = x;
        G[n][f][s] = y;
        (*earliest) = x;
        (*latest) = y;
        return;
    }

    int minEarliest = INT_MAX;
    int maxLatest = INT_MIN;
    int nHalf = (n + 1) / 2;
    int sPrime, middle;
    int i, j;
    if (s <= nHalf) {  // On the left or in the middle
        for (i = 0; i < f; ++i) {
            for (j = 0; j < s - f; ++j) {
                dp(nHalf, i + 1, i + j + 2, &x, &y);
                if (x < minEarliest) {
                    minEarliest = x;
                }
                if (y > maxLatest) {
                    maxLatest = y;
                }
            }
        }
    } else {  // s on the right
        sPrime = n + 1 - s;
        middle = (n - 2 * sPrime + 1) / 2;
        for (i = 0; i < f; ++i) {
            for (j = 0; j < sPrime - f; ++j) {
                dp(nHalf, i + 1, i + j + middle + 2, &x, &y);
                if (x < minEarliest) {
                    minEarliest = x;
                }
                if (y > maxLatest) {
                    maxLatest = y;
                }
            }
        }
    }

    F[n][f][s] = minEarliest + 1;
    G[n][f][s] = maxLatest + 1;
    (*earliest) = F[n][f][s];
    (*latest) = G[n][f][s];
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* earliestAndLatest(int n, int firstPlayer, int secondPlayer, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc(2 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    // F(n,f,s) = F(n,s,f)
    int temp;
    if (firstPlayer > secondPlayer) {
        temp = firstPlayer;
        firstPlayer = secondPlayer;
        secondPlayer = temp;
    }

    int earliest, latest;
    dp(n, firstPlayer, secondPlayer, &earliest, &latest);
    pRetVal[0] = earliest;
    pRetVal[1] = latest;
    (*returnSize) = 2;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int firstPlayer;
        int secondPlayer;
        int* returnSize;
    } testCase[] = {{11, 2, 4, NULL}, {5, 1, 5, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 11, firstPlayer = 2, secondPlayer = 4
     *  Output: [3,4]
     *
     *  Input: n = 5, firstPlayer = 1, secondPlayer = 5
     *  Output: [1,1]
     */

    int* pAnswer = NULL;
    int returnSize = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, firstPlayer = %d, secondPlayer = %d\n", testCase[i].n, testCase[i].firstPlayer,
               testCase[i].secondPlayer);

        pAnswer = earliestAndLatest(testCase[i].n, testCase[i].firstPlayer, testCase[i].secondPlayer, &returnSize);
        printf("Output: [");
        for (j = 0; j < returnSize; ++j) {
            printf("%d%s", pAnswer[j], (j == returnSize - 1 ? "" : ","));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        returnSize = 0;
    }

    return EXIT_SUCCESS;
}
