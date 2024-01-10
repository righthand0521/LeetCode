#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int permutation(int n) {
    int retVal = 1;

    int i;
    for (i = 1; i <= n; ++i) {
        retVal *= i;
    }

    return retVal;
}
char* getPermutation(int n, int k) {
    char* pRetVal = (char*)malloc((n + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n + 1) * sizeof(char));

    char buf[n + 1];
    memset(buf, 0, n + 1);
    int idx;
    for (idx = 0; idx < n; ++idx) {
        buf[idx] = (idx + 1) + '0';
    }

    int sum = 0;
    int interval;
    int i, j;
    for (i = 1; i <= n - 1; ++i) {
        interval = permutation(n - i);
        for (j = 1; j <= n; ++j) {
            sum += interval;
            if (sum >= k) {
                sum -= interval;
                break;
            }
        }
        if (sum >= k) {
            break;
        }
        // printf("(%d,%d)[%6d][%6d]\n", i, j, interval, sum);

        pRetVal[i - 1] = buf[j - 1];
        for (idx = j - 1; idx < n; ++idx) {
            buf[idx] = buf[idx + 1];
        }
    }
    pRetVal[i - 1] = buf[0];

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{3, 3}, {4, 9}, {3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        pAnswer = getPermutation(testCase[i].n, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
