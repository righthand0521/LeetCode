#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int step(int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int left, int right) {
    int retVal = 0;

    if (fruits[right][0] <= startPos) {
        retVal = startPos - fruits[left][0];
    } else if (fruits[left][0] >= startPos) {
        retVal = fruits[right][0] - startPos;
    } else {
        retVal = fmin(abs(startPos - fruits[right][0]), abs(startPos - fruits[left][0]));
        retVal += fruits[right][0];
        retVal -= fruits[left][0];
    }

    return retVal;
}
int maxTotalFruits(int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int k) {
    int retVal = 0;

    int sum = 0;
    int left = 0;
    int right = 0;
    while (right < fruitsSize) {
        sum += fruits[right][1];

        while ((left <= right) && (step(fruits, fruitsSize, fruitsColSize, startPos, left, right) > k)) {
            sum -= fruits[left][1];
            left++;
        }
        retVal = fmax(retVal, sum);

        right++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int fruits[MAX_SIZE][2];
        int fruitsSize;
        int fruitsColSize[MAX_SIZE];
        int startPos;
        int k;
    } testCase[] = {{{{2, 8}, {6, 3}, {8, 6}}, 3, {2, 2, 2}, 5, 4},
                    {{{0, 9}, {4, 1}, {5, 7}, {6, 2}, {7, 4}, {10, 9}}, 6, {2, 2, 2, 2, 2, 2}, 5, 4},
                    {{{0, 3}, {6, 4}, {8, 5}}, 3, {2, 2, 2}, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
     *  Output: 9
     *
     *  Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
     *  Output: 14
     *
     *  Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
     *  Output: 0
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
        printf("], startPos = %d, k = %d\n", testCase[i].startPos, testCase[i].k);

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
        answer = maxTotalFruits(pFruits, testCase[i].fruitsSize, testCase[i].fruitsColSize, testCase[i].startPos,
                                testCase[i].k);
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
