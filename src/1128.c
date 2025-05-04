#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize) {
    int retVal = 0;

    int hashTable[100];  // dominoes[i].length == 2, 1 <= dominoes[i][j] <= 9
    memset(hashTable, 0, sizeof(hashTable));
    int x, y, index;
    for (int i = 0; i < dominoesSize; ++i) {
        x = dominoes[i][0];
        y = dominoes[i][1];
        index = (x > y) ? (x * 10 + y) : (y * 10 + x);
        retVal += hashTable[index];
        hashTable[index] += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(4 * 10000)
    struct testCaseType {
        int dominoes[MAX_SIZE][2];
        int dominoesSize;
        int dominoesColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2}, {2, 1}, {3, 4}, {5, 6}}, 4, {2, 2, 2, 2}},
                    {{{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
     *  Output: 1
     *
     *  Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
     *  Output: 3
     */

    int** pDominoes = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("dominoes = [");
        for (j = 0; j < testCase[i].dominoesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].dominoesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].dominoes[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pDominoes = (int**)malloc(testCase[i].dominoesSize * sizeof(int*));
        if (pDominoes == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pDominoes, 0, testCase[i].dominoesSize * sizeof(int*));
        for (j = 0; j < testCase[i].dominoesSize; ++j) {
            pDominoes[j] = (int*)malloc(testCase[i].dominoesColSize[j] * sizeof(int));
            if (pDominoes[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pDominoes[k]);
                    pDominoes[k] = NULL;
                }
                free(pDominoes);
                pDominoes = NULL;
            }
            memset(pDominoes[j], 0, (testCase[i].dominoesColSize[j] * sizeof(int)));
            memcpy(pDominoes[j], testCase[i].dominoes[j], (testCase[i].dominoesColSize[j] * sizeof(int)));
        }
        answer = numEquivDominoPairs(pDominoes, testCase[i].dominoesSize, testCase[i].dominoesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].dominoesSize; ++j) {
            free(pDominoes[j]);
            pDominoes[j] = NULL;
        }
        free(pDominoes);
        pDominoes = NULL;
    }

    return EXIT_SUCCESS;
}
