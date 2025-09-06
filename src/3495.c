#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long get(int num) {
    long long retVal = 0;

    int end;
    int i = 1;
    int base = 1;
    while (base <= num) {
        end = (base * 2 - 1 < num) ? (base * 2 - 1) : (num);
        retVal += (long long)((i + 1) / 2) * (end - base + 1);

        i++;
        base *= 2;
    }

    return retVal;
}
long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    long long retVal = 0;

    long long count1, count2;
    for (int i = 0; i < queriesSize; i++) {
        count1 = get(queries[i][1]);
        count2 = get(queries[i][0] - 1);
        retVal += (count1 - count2 + 1) / 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 4}}, 2, {2, 2}}, {{{2, 6}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: queries = [[1,2],[2,4]]
     *  Output: 3
     *
     *  Input: queries = [[2,6]]
     *  Output: 4
     */

    int** pQueries = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        answer = minOperations(pQueries, testCase[i].queriesSize, testCase[i].queriesColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
