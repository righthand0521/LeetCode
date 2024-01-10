#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int *)malloc(asteroidsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (asteroidsSize * sizeof(int)));

    int currentAsteroidSize, previousAsteroidSize;
    int i;
    for (i = 0; i < asteroidsSize; ++i) {
        currentAsteroidSize = abs(asteroids[i]);
        while (((*returnSize) != 0) && (pRetVal[(*returnSize) - 1] > 0) && (asteroids[i] < 0)) {
            previousAsteroidSize = abs(pRetVal[(*returnSize) - 1]);
            if (previousAsteroidSize > currentAsteroidSize) {
                currentAsteroidSize = -1;
                break;
            } else if (previousAsteroidSize == currentAsteroidSize) {
                currentAsteroidSize = -1;
                (*returnSize)--;
                break;
            } else if (previousAsteroidSize < currentAsteroidSize) {
                (*returnSize)--;
            }
        }
        if (currentAsteroidSize != -1) {
            pRetVal[(*returnSize)++] = asteroids[i];
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int asteroids[MAX_SIZE];
        int asteroidsSize;
        int returnSize;
    } testCase[] = {
        {{5, 10, -5}, 3, 0}, {{8, -8}, 2, 0}, {{10, 2, -5}, 3, 0}, {{-2, -1, 1, 2}, 4, 0}, {{1, -2, -2, -2}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: asteroids = [5,10,-5]
     *  Output: [5,10]
     *
     *  Input: asteroids = [8,-8]
     *  Output: []
     *
     *  Input: asteroids = [10,2,-5]
     *  Output: [10]
     *
     *  Input: asteroids = [-2,-1,1,2]
     *  Output: [-2,-1,1,2]
     *
     *  Input: asteroids = [1,-2,-2,-2]
     *  Output: [-2,-2,-2]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: asteroids = [");
        for (j = 0; j < testCase[i].asteroidsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].asteroids[j]);
        }
        printf("]\n");

        pAnswer = asteroidCollision(testCase[i].asteroids, testCase[i].asteroidsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
