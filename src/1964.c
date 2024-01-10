#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (1)
#define DYNAMIC_PROGRAMMING (1)  // Time Limit Exceeded
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* longestObstacleCourseAtEachPosition(int* obstacles, int obstaclesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = obstaclesSize;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

#if (BINARY_SEARCH)
    printf("BINARY_SEARCH\n");

    int greedy[obstaclesSize];
    memset(greedy, 0, sizeof(greedy));
    greedy[0] = obstacles[0];

    pRetVal[0] = 1;
    int position = 1;

    int left, right, middle;
    int i;
    for (i = 1; i < obstaclesSize; ++i) {
        if (obstacles[i] >= greedy[position - 1]) {
            greedy[position++] = obstacles[i];
            pRetVal[i] = position;
            continue;
        }

        left = 0;
        right = position - 1;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (obstacles[i] >= greedy[middle]) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        greedy[right] = obstacles[i];
        pRetVal[i] = right + 1;
    }
#elif (DYNAMIC_PROGRAMMING)
    printf("DYNAMIC_PROGRAMMING: Time Limit Exceeded\n");

    int dp[obstaclesSize];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 0; i < obstaclesSize; ++i) {
        dp[i] = 1;
        for (j = 0; j < i; ++j) {
            if (obstacles[j] <= obstacles[i]) {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }
    memcpy(pRetVal, dp, ((*returnSize) * sizeof(int)));
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int obstacles[MAX_SIZE];
        int obstaclesSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 2}, 4, 0}, {{2, 2, 1}, 3, 0}, {{3, 1, 5, 6, 4, 2}, 6, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: obstacles = [1,2,3,2]
     *  Output: [1,2,3,3]
     *
     *  Input: obstacles = [2,2,1]
     *  Output: [1,2,1]
     *
     *  Input: obstacles = [3,1,5,6,4,2]
     *  Output: [1,1,2,3,2,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: obstacles = [");
        for (j = 0; j < testCase[i].obstaclesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].obstacles[j]);
        }
        printf("]\n");

        pAnswer = longestObstacleCourseAtEachPosition(testCase[i].obstacles, testCase[i].obstaclesSize,
                                                      &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        ;
    }

    return EXIT_SUCCESS;
}
