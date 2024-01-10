#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
long long dfs(int* nums, int numsSize, long long** table) {
    int retVal = 1;

    if (numsSize < 3) {
        return retVal;
    }

    int leftNodesSize = 0;
    int leftNodes[numsSize];
    memset(leftNodes, 0, sizeof(leftNodes));
    int rightNodesSize = 0;
    int rightNodes[numsSize];
    memset(rightNodes, 0, sizeof(rightNodes));

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[0]) {
            leftNodes[leftNodesSize++] = nums[i];
        } else {
            rightNodes[rightNodesSize++] = nums[i];
        }
    }

    long long leftWays = dfs(leftNodes, leftNodesSize, table) % MODULO;
    long long rightWays = dfs(rightNodes, rightNodesSize, table) % MODULO;
    retVal = (((leftWays * rightWays) % MODULO) * table[numsSize - 1][leftNodesSize]) % MODULO;

    return retVal;
}
int numOfWays(int* nums, int numsSize) {
    int retVal = 0;

    long long** pTable = (long long**)malloc((numsSize + 1) * sizeof(long long*));
    if (pTable == NULL) {
        perror("malloc");
        return retVal;
    }

    int i, j;
    for (i = 0; i < numsSize + 1; ++i) {
        pTable[i] = (long long*)malloc((i + 1) * sizeof(long long));
        if (pTable[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pTable[j]);
                pTable[j] = NULL;
            }
            free(pTable);
            pTable = NULL;
            return retVal;
        }
        memset(pTable[i], 0, ((i + 1) * sizeof(long long)));
        for (j = 0; j < i + 1; ++j) {
            pTable[i][j] = 1;
        }

        for (j = 1; j < i; ++j) {
            pTable[i][j] = (pTable[i - 1][j - 1] + pTable[i - 1][j]) % MODULO;
        }
    }
    retVal = (dfs(nums, numsSize, pTable) - 1) % MODULO;

    for (i = 0; i < numsSize + 1; ++i) {
        free(pTable[i]);
        pTable[i] = NULL;
    }
    free(pTable);
    pTable = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 3}, 3}, {{3, 4, 5, 1, 2}, 5}, {{1, 2, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,3]
     *  Output: 1
     *
     *  Input: nums = [3,4,5,1,2]
     *  Output: 5
     *
     *  Input: nums = [1,2,3]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = numOfWays(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
