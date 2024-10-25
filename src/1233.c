#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareString(const void* str1, const void* str2) {
    // ascending order
    return strcmp(*(char**)str1, *(char**)str2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeSubfolders(char** folder, int folderSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (char**)malloc(folderSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    // Sort the folders alphabetically
    qsort(folder, folderSize, sizeof(char*), compareString);

    // Initialize the retVal vector and add the first folder
    pRetVal[(*returnSize)++] = folder[0];

    // Iterate through each folder and check if it's a sub-folder of the last added folder in the retVal
    int lastFolderSize;
    int i;
    for (i = 1; i < folderSize; ++i) {
        lastFolderSize = strlen(pRetVal[(*returnSize) - 1]);
        if (lastFolderSize < strlen(folder[i])) {
            if (strncmp(pRetVal[(*returnSize) - 1], folder[i], lastFolderSize) == 0) {
                if (folder[i][lastFolderSize] == '/') {
                    continue;
                }
            }
        }
        pRetVal[(*returnSize)++] = folder[i];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(4 * 10000)
    struct testCaseType {
        char* folder[MAX_SIZE];
        int folderSize;
        int returnSize;
    } testCase[] = {{{"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"}, 5, 0},
                    {{"/a", "/a/b/c", "/a/b/d"}, 3, 0},
                    {{"/a/b/c", "/a/b/ca", "/a/b/d"}, 3, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
     *  Output: ["/a","/c/d","/c/f"]
     *
     *  Input: folder = ["/a","/a/b/c","/a/b/d"]
     *  Output: ["/a"]
     *
     *  Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
     *  Output: ["/a/b/c","/a/b/ca","/a/b/d"]
     */

    char** pFolder = NULL;
    int pFolderLength;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: folder = [");
        for (j = 0; j < testCase[i].folderSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].folder[j]);
        }
        printf("]\n");

        pFolder = (char**)malloc(testCase[i].folderSize * sizeof(char*));
        if (pFolder == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].folderSize; ++j) {
            pFolderLength = strlen(testCase[i].folder[j]) + 1;
            pFolder[j] = (char*)malloc(pFolderLength * sizeof(char));
            if (pFolder[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pFolder[k]) {
                        free(pFolder[k]);
                        pFolder[k] = NULL;
                    }
                }
                free(pFolder);
                pFolder = NULL;
                return EXIT_FAILURE;
            }
            memset(pFolder[j], 0, (pFolderLength * sizeof(char)));
            memcpy(pFolder[j], testCase[i].folder[j], (pFolderLength * sizeof(char)));
        }
        pAnswer = removeSubfolders(pFolder, testCase[i].folderSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].folderSize; ++j) {
            if (pFolder[j]) {
                free(pFolder[j]);
                pFolder[j] = NULL;
            }
        }
        free(pFolder);
        pFolder = NULL;
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}