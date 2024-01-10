#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mostPoints(int** questions, int questionsSize, int* questionsColSize) {
    long long retVal = 0;

    long long dp[questionsSize];
    memset(dp, 0, sizeof(dp));
    dp[questionsSize - 1] = questions[questionsSize - 1][0];
    int skip;
    int i;
    for (i = questionsSize - 2; i >= 0; --i) {
        dp[i] = questions[i][0];
        skip = questions[i][1];
        if (i + skip + 1 < questionsSize) {
            dp[i] += dp[i + skip + 1];
        }
        dp[i] = fmax(dp[i], dp[i + 1]);
    }
    retVal = dp[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int questions[MAX_SIZE][2];
        int questionsSize;
        int questionsColSize[MAX_SIZE];
    } testCase[] = {{{{3, 2}, {4, 3}, {4, 4}, {2, 5}}, 4, {2, 2, 2, 2}},
                    {{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: questions = [[3,2],[4,3],[4,4],[2,5]]
     *  Output: 5
     *
     *  Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
     *  Output: 7
     */

    int** pQuestions = NULL;
    long long answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: questions = [");
        for (j = 0; j < testCase[i].questionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].questionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].questions[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQuestions = (int**)malloc(testCase[i].questionsSize * sizeof(int*));
        if (pQuestions == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].questionsSize; ++j) {
            pQuestions[j] = (int*)malloc(testCase[i].questionsColSize[j] * sizeof(int));
            if (pQuestions[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pQuestions[k]);
                    pQuestions[k] = NULL;
                }
                free(pQuestions);
                pQuestions = NULL;
                return EXIT_FAILURE;
            }
            memset(pQuestions[j], 0, (testCase[i].questionsColSize[j] * sizeof(int)));
            memcpy(pQuestions[j], testCase[i].questions[j], (testCase[i].questionsColSize[j] * sizeof(int)));
        }
        answer = mostPoints(pQuestions, testCase[i].questionsSize, testCase[i].questionsColSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].questionsSize; ++j) {
            free(pQuestions[j]);
            pQuestions[j] = NULL;
        }
        free(pQuestions);
        pQuestions = NULL;
    }

    return EXIT_SUCCESS;
}
