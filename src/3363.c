#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dp(int** fruits, int fruitsSize, int* fruitsColSize) {
    int retVal = 0;

    int* prev = malloc(sizeof(int) * fruitsSize);
    if (prev == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < fruitsSize; ++i) {
        prev[i] = INT_MIN;
    }
    prev[fruitsSize - 1] = fruits[0][fruitsSize - 1];

    int* curr = malloc(sizeof(int) * fruitsSize);
    if (curr == NULL) {
        perror("malloc");
        free(prev);
        return retVal;
    }

    for (int i = 1; i < fruitsSize - 1; ++i) {
        for (int j = 0; j < fruitsSize; ++j) {
            curr[j] = INT_MIN;
        }

        for (int j = ((fruitsSize - 1 - i > i + 1) ? (fruitsSize - 1 - i) : (i + 1)); j < fruitsSize; ++j) {
            int best = prev[j];
            if (j - 1 >= 0) {
                best = best > prev[j - 1] ? best : prev[j - 1];
            }
            if (j + 1 < fruitsSize) {
                best = best > prev[j + 1] ? best : prev[j + 1];
            }
            curr[j] = best + fruits[i][j];
        }

        int* tmp = prev;
        prev = curr;
        curr = tmp;
    }
    retVal = prev[fruitsSize - 1];

    //
    free(prev);
    free(curr);

    return retVal;
}
int maxCollectedFruits(int** fruits, int fruitsSize, int* fruitsColSize) {
    int retVal = 0;

    for (int i = 0; i < fruitsSize; ++i) {
        retVal += fruits[i][i];
    }
    retVal += dp(fruits, fruitsSize, fruitsColSize);

    for (int i = 0; i < fruitsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            int temp = fruits[j][i];
            fruits[j][i] = fruits[i][j];
            fruits[i][j] = temp;
        }
    }
    retVal += dp(fruits, fruitsSize, fruitsColSize);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int fruits[MAX_SIZE][MAX_SIZE];
        int fruitsSize;
        int fruitsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 2, 3, 4}, {5, 6, 8, 7}, {9, 10, 11, 12}, {13, 14, 15, 16}}, 4, {4, 4, 4, 4}},
                    {{{1, 1}, {1, 1}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
     *  Output: 100
     *
     *  Input: fruits = [[1,1],[1,1]]
     *  Output: 4
     */

    int** pFruits = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: fruits = [");
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].fruitsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].fruits[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pFruits = (int**)malloc(testCase[i].fruitsSize * sizeof(int*));
        if (pFruits == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            pFruits[j] = (int*)malloc(testCase[i].fruitsColSize[j] * sizeof(int));
            if (pFruits[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pFruits[k]);
                    pFruits[k] = NULL;
                }
                free(pFruits);
                pFruits = NULL;
                return EXIT_FAILURE;
            }
            memset(pFruits[j], 0, (testCase[i].fruitsColSize[j] * sizeof(int)));
            memcpy(pFruits[j], testCase[i].fruits[j], (testCase[i].fruitsColSize[j] * sizeof(int)));
        }
        answer = maxCollectedFruits(pFruits, testCase[i].fruitsSize, testCase[i].fruitsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            free(pFruits[j]);
            pFruits[j] = NULL;
        }
        free(pFruits);
        pFruits = NULL;
    }

    return EXIT_SUCCESS;
}
