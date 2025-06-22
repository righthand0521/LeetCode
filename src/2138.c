#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** divideString(char* s, int k, char fill, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    int numberOfStrings = (sSize + k - 1) / k;

    pRetVal = (char**)malloc(numberOfStrings * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (int i = 0; i < numberOfStrings; ++i) {
        pRetVal[i] = (char*)malloc((k + 1) * sizeof(char));
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
    }

    int start, end;
    for (int i = 0; i < numberOfStrings; ++i) {
        start = i * k;
        end = start + k;
        if (end > sSize) {
            end = sSize;
        }
        strncpy(pRetVal[i], s + start, end - start);
        if (end - start < k) {
            memset(pRetVal[i] + (end - start), fill, k - (end - start));
        }
        pRetVal[i][k] = '\0';

        (*returnSize)++;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
        int k;
        char fill;
        int returnSize;
    } testCase[] = {{"abcdefghi", 3, 'x', 0}, {"abcdefghij", 3, 'x', 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcdefghi", k = 3, fill = "x"
     *  Output: ["abc","def","ghi"]
     *
     *  Input: s = "abcdefghij", k = 3, fill = "x"
     *  Output: ["abc","def","ghi","jxx"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s =  \"%s\", k = %d, fill = \"%c\"\n", testCase[i].s, testCase[i].k, testCase[i].fill);

        pAnswer = divideString(testCase[i].s, testCase[i].k, testCase[i].fill, &testCase[i].returnSize);
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
