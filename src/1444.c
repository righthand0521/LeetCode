#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
// https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/solutions/623732/java-c-python-dp-prefixsum-in-matrix-clean-code/
int dfs(int row, int col, int k, int r, int c, int*** dp, int** preSum) {
    int retVal = 0;

    // if the remain piece has no apple -> invalid
    if (preSum[r][c] == 0) {
        return retVal;
    }

    // found valid way after using k-1 cuts
    if (k == 0) {
        retVal = 1;
        return retVal;
    }

    if (dp[k][r][c] != -1) {
        retVal = dp[k][r][c];
        return retVal;
    }

    // cut in horizontal
    int nr;
    for (nr = r + 1; nr < row; nr++) {
        // cut if the upper piece contains at least one apple
        if (preSum[r][c] - preSum[nr][c] > 0) {
            retVal = (retVal + dfs(row, col, k - 1, nr, c, dp, preSum)) % MODULO;
        }
    }

    // cut in vertical
    int nc;
    for (nc = c + 1; nc < col; nc++) {
        // cut if the left piece contains at least one apple
        if (preSum[r][c] - preSum[r][nc] > 0) {
            retVal = (retVal + dfs(row, col, k - 1, r, nc, dp, preSum)) % MODULO;
        }
    }

    dp[k][r][c] = retVal;

    return retVal;
}
int ways(char** pizza, int pizzaSize, int k) {
    int retVal = 0;

    int x, y, z;
    int row = pizzaSize;
    int col = strlen(pizza[0]);

    int** preSum = (int**)calloc(row + 1, sizeof(int*));
    if (preSum == NULL) {
        perror("calloc");
        return retVal;
    }
    for (x = 0; x < (row + 1); ++x) {
        preSum[x] = (int*)calloc((col + 1), sizeof(int));
        if (preSum[x] == NULL) {
            perror("calloc");
            return retVal;
        }
    }
    for (x = row - 1; x >= 0; --x) {
        for (y = col - 1; y >= 0; --y) {
            preSum[x][y] = preSum[x][y + 1] + preSum[x + 1][y] - preSum[x + 1][y + 1] + (pizza[x][y] == 'A');
        }
    }

    int*** dp = (int***)calloc(k, sizeof(int**));
    if (dp == NULL) {
        perror("calloc");
        return retVal;
    }
    for (x = 0; x < k; ++x) {
        dp[x] = (int**)calloc(row, sizeof(int*));
        if (dp[x] == NULL) {
            perror("calloc");
            return retVal;
        }
        for (y = 0; y < row; ++y) {
            dp[x][y] = (int*)calloc(col, sizeof(int));
            if (dp[x][y] == NULL) {
                perror("calloc");
                return retVal;
            }
            for (z = 0; z < col; ++z) {
                dp[x][y][z] = -1;
            }
        }
    }

    retVal = dfs(row, col, k - 1, 0, 0, dp, preSum);

    for (x = 0; x < (row + 1); ++x) {
        free(preSum[x]);
        preSum[x] = NULL;
    }
    free(preSum);
    preSum = NULL;
    for (x = 0; x < k; ++x) {
        for (y = 0; y < row; ++y) {
            free(dp[x][y]);
            dp[x][y] = NULL;
        }
        free(dp[x]);
        dp[x] = NULL;
    }
    free(dp);
    dp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW_SIZE (50 + 2)
#define MAX_COL_SIZE (50 + 2)
    struct testCaseType {
        char pizza[MAX_ROW_SIZE][MAX_COL_SIZE];
        int pizzaSize;
        int k;
    } testCase[] = {{{"A..", "AAA", "..."}, 3, 3}, {{"A..", "AA.", "..."}, 3, 3}, {{"A..", "A..", "..."}, 3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: pizza = ["A..","AAA","..."], k = 3
     *  Output: 3
     *
     *  Input: pizza = ["A..","AA.","..."], k = 3
     *  Output: 1
     *
     *  Input: pizza = ["A..","A..","..."], k = 1
     *  Output: 1
     */

    char** pPizza = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pizza = [");
        for (j = 0; j < testCase[i].pizzaSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].pizza[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        pPizza = (char**)malloc(testCase[i].pizzaSize * sizeof(char*));
        if (pPizza == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pizzaSize; ++j) {
            pPizza[j] = (char*)malloc(MAX_COL_SIZE * sizeof(char));
            if (pPizza[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPizza[k]);
                    pPizza[k] = NULL;
                }
                return EXIT_FAILURE;
            }
            memset(pPizza[j], 0, (MAX_COL_SIZE * sizeof(char)));
            memcpy(pPizza[j], testCase[i].pizza[j], strlen(testCase[i].pizza[j]));
        }
        answer = ways(pPizza, testCase[i].pizzaSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pizzaSize; ++j) {
            free(pPizza[j]);
            pPizza[j] = NULL;
        }
        free(pPizza);
        pPizza = NULL;
    }

    return EXIT_SUCCESS;
}
