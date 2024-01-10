#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minCost(int n, int* cuts, int cutsSize) {
    int retVal = 0;

    // 2 <= n <= 10^6, 1 <= cuts[i] <= n - 1
    int sortCutsSize = cutsSize + 2;
    int sortCuts[sortCutsSize];
    memset(sortCuts, 0, sizeof(sortCuts));
    memcpy(sortCuts + 1, cuts, cutsSize * sizeof(cuts[0]));
    sortCuts[0] = -1;
    sortCuts[sortCutsSize - 1] = INT_MAX;
    qsort(sortCuts, sortCutsSize, sizeof(int), compareInteger);
    sortCuts[0] = 0;
    sortCuts[sortCutsSize - 1] = n;

    int dp[cutsSize + 2][cutsSize + 2];
    memset(dp, 0, sizeof(dp));
    int ans;
    int diff, left, right, mid;
    for (diff = 2; diff < cutsSize + 2; ++diff) {
        for (left = 0; left < cutsSize + 2 - diff; ++left) {
            right = left + diff;
            ans = INT_MAX;
            for (mid = left + 1; mid < right; ++mid) {
                ans = fmin(ans, dp[left][mid] + dp[mid][right] + sortCuts[right] - sortCuts[left]);
            }
            dp[left][right] = ans;
        }
    }

    retVal = dp[0][cutsSize + 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e6)
    struct testCaseType {
        int n;
        int cuts[MAX_SIZE];
        int cutsSize;
    } testCase[] = {{7, {1, 3, 4, 5}, 4}, {9, {5, 6, 1, 4, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 7, cuts = [1,3,4,5]
     *  Output: 16
     *
     *  Input: n = 9, cuts = [5,6,1,4,2]
     *  Output: 22
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, cuts = [", testCase[i].n);
        for (j = 0; j < testCase[i].cutsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cuts[j]);
        }
        printf("]\n");

        answer = minCost(testCase[i].n, testCase[i].cuts, testCase[i].cutsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
