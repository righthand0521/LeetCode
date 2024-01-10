#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize) {
    char *retVal = NULL;

    retVal = strs[0];  // 1 <= strs.length <= 200
    int retValLength = strlen(retVal);
    int i, j;
    for (i = 1; i < strsSize; ++i) {
        for (j = 0; j < retValLength; ++j) {
            if ((j == (int)strlen(strs[i])) || (retVal[j] != strs[i][j])) {
                retValLength = j;
                break;
            }
        }
    }
    retVal[retValLength] = '\0';

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char strs[MAX_SIZE][MAX_SIZE];
        int strsSize;
    } testCase[] = {{{"flower", "flow", "flight"}, 3}, {{"dog", "racecar", "car"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["flower","flow","flight"]
     *  Output: "fl"
     *
     *  Input: strs = ["dog","racecar","car"]
     *  Output: ""
     */

    char **pStrs = NULL;
    char *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs = [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].strs[j]);
        }
        printf("]\n");

        pStrs = (char **)malloc(testCase[i].strsSize * sizeof(char *));
        if (pStrs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].strsSize; ++j) {
            pStrs[j] = (char *)malloc(MAX_SIZE * sizeof(char));
            if (pStrs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pStrs[k]);
                    pStrs[k] = NULL;
                }
                free(pStrs);
                pStrs = NULL;
                return EXIT_FAILURE;
            }
            memset(pStrs[j], 0, (MAX_SIZE * sizeof(char)));
            memcpy(pStrs[j], testCase[i].strs[j], (MAX_SIZE * sizeof(char)));
        }
        pAnswer = longestCommonPrefix(pStrs, testCase[i].strsSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        for (j = 0; j < testCase[i].strsSize; ++j) {
            free(pStrs[j]);
            pStrs[j] = NULL;
        }
        free(pStrs);
        pStrs = NULL;
    }

    return EXIT_SUCCESS;
}
