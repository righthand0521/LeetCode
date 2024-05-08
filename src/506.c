#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // descending order
    if (p1[1] == p2[1]) {
        return (p1[1] < p2[1]);
    }

    return (p1[1] < p2[1]);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findRelativeRanks(int *score, int scoreSize, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;

    int sortScore[scoreSize][2];
    memset(sortScore, 0, sizeof(sortScore));
    int i;
    for (i = 0; i < scoreSize; ++i) {
        sortScore[i][0] = i;
        sortScore[i][1] = score[i];
    }
    qsort(sortScore, scoreSize, sizeof(sortScore[0]), compareIntArray);

#define MAX_RETURN_COL_SIZE (16)
    pRetVal = (char **)malloc(scoreSize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < scoreSize; ++i) {
        pRetVal[i] = (char *)malloc(MAX_RETURN_COL_SIZE * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[(*returnSize)], 0, (MAX_RETURN_COL_SIZE * sizeof(char)));
    }
    (*returnSize) = scoreSize;

    for (i = 0; i < scoreSize; ++i) {
        if (i == 0) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Gold Medal");
        } else if (i == 1) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Silver Medal");
        } else if (i == 2) {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%s", "Bronze Medal");
        } else {
            snprintf(pRetVal[sortScore[i][0]], MAX_RETURN_COL_SIZE, "%d", i + 1);
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int score[MAX_SIZE];
        int scoreSize;
        int returnSize;
    } testCase[] = {{{5, 4, 3, 2, 1}, 5, 0}, {{10, 3, 8, 9, 4}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: score = [5,4,3,2,1]
     *  Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
     *
     *  Input: score = [10,3,8,9,4]
     *  Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
     */

    char **pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: score = [");
        for (j = 0; j < testCase[i].scoreSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].score[j]);
        }
        printf("]\n");

        pAnswer = findRelativeRanks(testCase[i].score, testCase[i].scoreSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
