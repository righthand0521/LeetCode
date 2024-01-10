#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int n, int k, int node, char* pVisit, char* pRetVal, int* returnSize) {
    int highest = pow(10, n - 1);

    int neighbor;
    int x;
    for (x = 0; x < k; ++x) {
        neighbor = node * 10 + x;
        if (pVisit[neighbor] == 0) {
            pVisit[neighbor] = 1;
            dfs(n, k, neighbor % highest, pVisit, pRetVal, returnSize);
            pRetVal[(*returnSize)++] = x + '0';
        }
    }
}
char* crackSafe(int n, int k) {
    char* pRetVal = NULL;

#define MAX_RETURN_SIZE (int)(1e4)

    pRetVal = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));
    int returnSize = 0;

    char* pVisit = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pVisit == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(pVisit, 0, (MAX_RETURN_SIZE * sizeof(char)));
    pVisit[0] = 1;

    dfs(n, k, 0, pVisit, pRetVal, &returnSize);
    int i;
    for (i = 0; i < n; i++) {
        pRetVal[returnSize++] = '0';
    }

    free(pVisit);
    pVisit = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{1, 2}, {2, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1, k = 2
     *  Output: "10"
     *
     *  Input: n = 2, k = 2
     *  Output: "01100"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        pAnswer = crackSafe(testCase[i].n, testCase[i].k);
        if (pAnswer != NULL) {
            printf("Output: \"%s\"\n", pAnswer);
        }

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
