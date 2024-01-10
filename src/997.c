#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
    int retVal = -1;

    int i;

    int Graph[n][2];
    memset(Graph, 0, sizeof(Graph));
    for (i = 0; i < trustSize; ++i) {
        // Graph[n][0]: ai; the person labeled ai trusts the person labeled bi
        ++Graph[trust[i][0] - 1][0];

        // Graph[n][1]: bi; the person labeled ai trusts the person labeled bi
        ++Graph[trust[i][1] - 1][1];
    }

    for (i = 0; i < n; ++i) {
        // The town judge trusts nobody.
        if (Graph[i][0] != 0) {
            continue;
        }

        // Everybody (except for the town judge) trusts the town judge.
        if (Graph[i][1] != n - 1) {
            continue;
        }

        // There is exactly one person that satisfies properties 1 and 2.
        retVal = i + 1;
        break;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int n;
        int trust[MAX_SIZE][2];
        int trustSize;
        int trustColSize[MAX_SIZE];
    } testCase[] = {
        {2, {{1, 2}}, 1, {2}}, {3, {{1, 3}, {2, 3}}, 2, {2, 2}}, {3, {{1, 3}, {2, 3}, {3, 1}}, 3, {2, 2, 2}}, {1, {}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pTrust = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, trust = [", testCase[i].n);
        for (j = 0; j < testCase[i].trustSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].trustColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].trust[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pTrust = (int**)malloc(testCase[i].trustSize * sizeof(int*));
        if (pTrust == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].trustSize; ++j) {
            pTrust[j] = (int*)malloc(testCase[i].trustColSize[j] * sizeof(int));
            if (pTrust[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pTrust[k]) {
                        free(pTrust[k]);
                    }
                }
                free(pTrust);
                pTrust = NULL;
                return EXIT_FAILURE;
            }
            memset(pTrust[j], 0, testCase[i].trustColSize[j] * sizeof(int));
            memcpy(pTrust[j], testCase[i].trust[j], testCase[i].trustColSize[j] * sizeof(int));
        }

        answer = findJudge(testCase[i].n, pTrust, testCase[i].trustSize, testCase[i].trustColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].trustSize; ++j) {
            if (pTrust[j]) {
                free(pTrust[j]);
                pTrust[j] = NULL;
            }
        }
        free(pTrust);
        pTrust = NULL;
    }

    return EXIT_SUCCESS;
}
