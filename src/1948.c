#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** deleteDuplicateFolder(char*** paths, int pathsSize, int* pathsColSize, int* returnSize,
                              int** returnColumnSizes) {
    char*** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    // TODO: Delete Duplicate Folders in System

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_X_SIZE (int)(2 * 100)
#define MAX_Y_SIZE (500)
#define MAX_Z_SIZE (10)
    struct testCaseType {
        char paths[MAX_X_SIZE][MAX_Y_SIZE][MAX_Z_SIZE];
        int pathsSize;
        int pathsColSize[MAX_X_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{"a"}, {"c"}, {"d"}, {"a", "b"}, {"c", "b"}, {"d", "a"}}, 6, {1, 1, 1, 2, 2, 2}, 0, NULL},
                    {{{"a"}, {"c"}, {"a", "b"}, {"c", "b"}, {"a", "b", "x"}, {"a", "b", "x", "y"}, {"w"}, {"w", "y"}},
                     8,
                     {1, 1, 2, 2, 3, 4, 1, 2},
                     0,
                     NULL},
                    {{{"a", "b"}, {"c", "d"}, {"c"}, {"a"}}, 4, {2, 2, 1, 1}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
     *  Output: [["d"],["d","a"]]
     *
     *  Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
     *  Output: [["c"],["c","b"],["a"],["a","b"]]
     *
     *  Input: paths = [["a","b"],["c","d"],["c"],["a"]]
     *  Output: [["c"],["c","d"],["a"],["a","b"]]
     */

    char*** pPaths = NULL;
    char*** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: paths = [");
        for (j = 0; j < testCase[i].pathsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pathsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0 ? "" : ","), testCase[i].paths[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPaths = (char***)malloc(testCase[i].pathsSize * sizeof(char***));
        if (pPaths == NULL) {
            perror("malloc");
            goto exit_free;
        }
        for (j = 0; j < testCase[i].pathsSize; ++j) {
            pPaths[j] = (char**)malloc(testCase[i].pathsColSize[j] * sizeof(char**));
            if (pPaths[j] == NULL) {
                perror("malloc");
                goto exit_free;
            }
            for (k = 0; k < testCase[i].pathsColSize[j]; ++k) {
                int len = strlen(testCase[i].paths[j][k]) + 1;
                pPaths[j][k] = (char*)malloc(len * sizeof(char));
                if (pPaths[j][k] == NULL) {
                    perror("malloc");
                    goto exit_free;
                }
                memset(pPaths[j][k], 0, (len * sizeof(char)));
                memcpy(pPaths[j][k], testCase[i].paths[j][k], ((len - 1) * sizeof(char)));
            }
        }

        pAnswer = deleteDuplicateFolder(pPaths, testCase[i].pathsSize, testCase[i].pathsColSize,
                                        &testCase[i].returnSize, &(testCase[i].returnColumnSizes));
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0 ? "" : ","), pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

    exit_free:
        for (j = 0; j < testCase[i].pathsSize; ++j) {
            if (pPaths[j] == NULL) {
                continue;
            }
            for (k = 0; k < testCase[i].pathsColSize[j]; ++k) {
                if (pPaths[j][k] == NULL) {
                    continue;
                }
                free(pPaths[j][k]);
                pPaths[j][k] = NULL;
            }
            free(pPaths[j]);
            pPaths[j] = NULL;
        }
        if (pPaths == NULL) {
            continue;
        }
        free(pPaths);
        pPaths = NULL;
    }

    return EXIT_SUCCESS;
}
