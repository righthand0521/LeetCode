#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    bool* pRetVal = NULL;

    (*returnSize) = candiesSize;
    pRetVal = (bool*)malloc((*returnSize) * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, false, ((*returnSize) * sizeof(bool)));

    int i;
    int maxCandy = candies[0];
    for (i = 1; i < candiesSize; ++i) {
        maxCandy = fmax(maxCandy, candies[i]);
    }
    for (i = 0; i < candiesSize; ++i) {
        if (candies[i] + extraCandies >= maxCandy) {
            pRetVal[i] = true;
        } else {
            pRetVal[i] = false;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int candies[MAX_SIZE];
        int candiesSize;
        int extraCandies;
        int returnSize;
    } testCase[] = {{{2, 3, 5, 1, 3}, 5, 3, 0}, {{4, 2, 1, 1, 2}, 5, 1, 0}, {{12, 1, 12}, 3, 10, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: candies = [2,3,5,1,3], extraCandies = 3
     *  Output: [true,true,true,false,true]
     *
     *  Input: candies = [4,2,1,1,2], extraCandies = 1
     *  Output: [true,false,false,false,false]
     *
     *  Input: candies = [12,1,12], extraCandies = 10
     *  Output: [true,false,true]
     */

    bool* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: candies = [");
        for (j = 0; j < testCase[i].candiesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].candies[j]);
        }
        printf("], extraCandies = %d\n", testCase[i].extraCandies);

        pAnswer = kidsWithCandies(testCase[i].candies, testCase[i].candiesSize, testCase[i].extraCandies,
                                  &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", (pAnswer[j] == true ? "true" : "false"));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
