#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canChoose(int** groups, int groupsSize, int* groupsColSize, int* nums, int numsSize) {
    bool retVal = false;

    int i;
    int idx = 0;
    int row = 0;
    while ((idx < numsSize) && (row < groupsSize)) {
        if (idx + groupsColSize[row] > numsSize) {
            return retVal;
        }

        for (i = 0; i < groupsColSize[row]; ++i) {
            if (groups[row][i] != nums[idx + i]) {
                ++idx;
                break;
            }
        }
        if (i < groupsColSize[row]) {
            continue;
        }

        idx += groupsColSize[row];
        ++row;
    }

    if (row == groupsSize) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int groups[MAX_SIZE][MAX_SIZE];
        int groupsSize;
        int groupsColSize[MAX_SIZE];
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{{1, -1, -1}, {3, -2, 0}}, 2, {3, 3}, {1, -1, 0, 1, -1, -1, 3, -2, 0}, 9},
                    {{{10, -2}, {1, 2, 3, 4}}, 2, {2, 4}, {1, 2, 3, 4, 10, -2}, 6},
                    {{{1, 2, 3}, {3, 4}}, 2, {3, 2}, {7, 7, 1, 2, 3, 4, 7, 7}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGroups = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: groups = [");
        for (j = 0; j < testCase[i].groupsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].groupsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].groups[j][k]);
            }
            printf("]");
        }
        printf("], nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        pGroups = (int**)malloc(testCase[i].groupsSize * sizeof(int*));
        if (pGroups == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].groupsSize; ++j) {
            pGroups[j] = (int*)malloc(testCase[i].groupsColSize[j] * sizeof(int));
            if (pGroups[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGroups[k]);
                    pGroups[k] = NULL;
                }
                free(pGroups);
                pGroups = NULL;
                return EXIT_FAILURE;
            }
            memset(pGroups[j], 0, testCase[i].groupsColSize[j] * sizeof(int));
            memcpy(pGroups[j], testCase[i].groups[j], testCase[i].groupsColSize[j] * sizeof(int));
        }
        answer = canChoose(pGroups, testCase[i].groupsSize, testCase[i].groupsColSize, testCase[i].nums,
                           testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].groupsSize; ++j) {
            free(pGroups[j]);
        }
        free(pGroups);
        pGroups = NULL;
    }

    return EXIT_SUCCESS;
}
