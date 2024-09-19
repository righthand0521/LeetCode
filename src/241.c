#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeBaseCases(char* expression, int*** dp, int** dpSize) {
    int expressionSize = strlen(expression);

    int dig1, dig2, number;
    int i;
    for (i = 0; i < expressionSize; ++i) {
        if (isdigit(expression[i]) == 0) {
            continue;
        }

        dig1 = expression[i] - '0';
        if ((i + 1 < expressionSize) && (isdigit(expression[i + 1]))) {
            dig2 = expression[i + 1] - '0';
            number = dig1 * 10 + dig2;
            dp[i][i + 1][dpSize[i][i + 1]] = number;
            dpSize[i][i + 1] += 1;
        }

        dp[i][i][dpSize[i][i]] = dig1;
        dpSize[i][i] += 1;
    }
}
void processSubexpression(char* expression, int*** dp, int** dpSize, int start, int end) {
    int leftSize, rightSize;
    int i, j;
    int split;
    for (split = start; split <= end; split++) {
        if (isdigit(expression[split])) {
            continue;
        }

        leftSize = dpSize[start][split - 1];
        rightSize = dpSize[split + 1][end];
        for (i = 0; i < leftSize; ++i) {
            for (j = 0; j < rightSize; ++j) {
                switch (expression[split]) {
                    case '+':
                        dp[start][end][dpSize[start][end]] = dp[start][split - 1][i] + dp[split + 1][end][j];
                        dpSize[start][end] += 1;
                        break;
                    case '-':
                        dp[start][end][dpSize[start][end]] = dp[start][split - 1][i] - dp[split + 1][end][j];
                        dpSize[start][end] += 1;
                        break;
                    case '*':
                        dp[start][end][dpSize[start][end]] = dp[start][split - 1][i] * dp[split + 1][end][j];
                        dpSize[start][end] += 1;
                        break;
                }
            }
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* expression, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    int expressionSize = strlen(expression);
    int maxReturnSize = 1 << expressionSize;

    int*** dp = (int***)malloc(expressionSize * sizeof(int**));
    for (i = 0; i < expressionSize; ++i) {
        dp[i] = (int**)malloc(expressionSize * sizeof(int*));
        for (j = 0; j < expressionSize; ++j) {
            dp[i][j] = (int*)malloc(maxReturnSize * sizeof(int));
            memset(dp[i][j], 0, (maxReturnSize * sizeof(int)));
        }
    }
    int** dpSize = (int**)malloc(expressionSize * sizeof(int*));
    for (i = 0; i < expressionSize; ++i) {
        dpSize[i] = (int*)malloc(expressionSize * sizeof(int));
        memset(dpSize[i], 0, (expressionSize * sizeof(int)));
    }
    initializeBaseCases(expression, dp, dpSize);

    int length, start, end;
    for (length = 3; length <= expressionSize; length++) {
        for (start = 0; start + length - 1 < expressionSize; start++) {
            end = start + length - 1;
            processSubexpression(expression, dp, dpSize, start, end);
        }
    }

    pRetVal = (int*)malloc(maxReturnSize * sizeof(int));
    memset(pRetVal, 0, (maxReturnSize * sizeof(int)));
    (*returnSize) = dpSize[0][expressionSize - 1];
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = dp[0][expressionSize - 1][i];
    }

    //
    for (i = 0; i < expressionSize; ++i) {
        for (j = 0; j < expressionSize; ++j) {
            free(dp[i][j]);
            dp[i][j] = NULL;
        }
        free(dp[i]);
        dp[i] = NULL;
    }
    free(dp);
    dp = NULL;
    //
    for (i = 0; i < expressionSize; ++i) {
        free(dpSize[i]);
        dpSize[i] = NULL;
    }
    free(dpSize);
    dpSize = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char expression[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"2-1-1", 0}, {"2*3-4*5", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: expression = "2-1-1"
     *  Output: [0,2]
     *
     *  Input: expression = "2*3-4*5"
     *  Output: [-34,-14,-10,-10,10]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: expression = \"%s\"\n", testCase[i].expression);

        pAnswer = diffWaysToCompute(testCase[i].expression, &testCase[i].returnSize);
        printf("Output = [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer != NULL) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
