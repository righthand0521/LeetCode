#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minZeroArray(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int retVal = 0;

    int sum = 0;
    int differenceArray[numsSize + 1];
    memset(differenceArray, 0, sizeof(differenceArray));
    int differenceArrayIdx;
    int left, right, val;
    for (int index = 0; index < numsSize; index++) {
        // Iterate through queries while current index of nums cannot equal zero
        while (sum + differenceArray[index] < nums[index]) {
            retVal++;
            // Zero array isn't formed after all queries are processed
            if (retVal > queriesSize) {
                retVal = -1;
                return retVal;
            }

            // Process start and end of range
            left = queries[retVal - 1][0];
            right = queries[retVal - 1][1];
            val = queries[retVal - 1][2];
            if (right >= index) {
                differenceArrayIdx = fmax(left, index);
                differenceArray[differenceArrayIdx] += val;
                differenceArray[right + 1] -= val;
            }
        }

        sum += differenceArray[index];  // Update prefix sum at current index
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int queries[MAX_SIZE][3];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
    } testCase[] = {{{2, 0, 2}, 3, {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}}, 3, {3, 3, 3}},
                    {{4, 3, 2, 1}, 4, {{1, 3, 2}, {0, 2, 1}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
     *  Output: 2
     *
     *  Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
     *  Output: -1
     */

    int** pQueries = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pQueries[k]) {
                        free(pQueries[k]);
                        pQueries[k] = NULL;
                    }
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        answer = minZeroArray(testCase[i].nums, testCase[i].numsSize, pQueries, testCase[i].queriesSize,
                              testCase[i].queriesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
