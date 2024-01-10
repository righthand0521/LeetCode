#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int backtracking(int i, int* distribute, int distributeSize, int* cookies, int cookiesSize, int k, int zeroCount) {
    int retVal = INT_MAX;

    if (cookiesSize - i < zeroCount) {
        return retVal;
    }

    int idx;
    if (i == cookiesSize) {
        retVal = distribute[0];
        for (idx = 1; idx < distributeSize; ++idx) {
            retVal = fmax(retVal, distribute[idx]);
        }

        return retVal;
    }

    int j;
    for (j = 0; j < k; ++j) {
        if (distribute[j] == 0) {
            zeroCount -= 1;
        }
        distribute[j] += cookies[i];

        retVal = fmin(retVal, backtracking(i + 1, distribute, distributeSize, cookies, cookiesSize, k, zeroCount));

        distribute[j] -= cookies[i];
        if (distribute[j] == 0) {
            zeroCount += 1;
        }
    }

    return retVal;
}
int distributeCookies(int* cookies, int cookiesSize, int k) {
    int retVal = 0;

    int distributeSize = k;
    int distribute[distributeSize];
    memset(distribute, 0, sizeof(distribute));
    retVal = backtracking(0, distribute, distributeSize, cookies, cookiesSize, k, k);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (8)
    struct testCaseType {
        int cookies[MAX_SIZE];
        int cookiesSize;
        int k;
    } testCase[] = {{{8, 15, 10, 20, 8}, 5, 2}, {{6, 1, 3, 2, 2, 4, 1, 2}, 8, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: cookies = [8,15,10,20,8], k = 2
     *  Output: 31
     *
     *  Input: cookies = [6,1,3,2,2,4,1,2], k = 3
     *  Output: 7
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: cookies = [");
        for (j = 0; j < testCase[i].cookiesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cookies[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = distributeCookies(testCase[i].cookies, testCase[i].cookiesSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
