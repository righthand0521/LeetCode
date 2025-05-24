#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(wordsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, wordsSize * sizeof(int));

    int wordSize;
    for (int i = 0; i < wordsSize; ++i) {
        wordSize = strlen(words[i]);
        for (int j = 0; j < wordSize; ++j) {
            if (words[i][j] == x) {
                pRetVal[(*returnSize)++] = i;
                break;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char x;
        int returnSize;
    } testCase[] = {{{"leet", "code"}, 2, 'e', 0},
                    {{"abc", "bcd", "aaaa", "cbc"}, 4, 'a', 0},
                    {{"abc", "bcd", "aaaa", "cbc"}, 4, 'z', 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["leet","code"], x = "e"
     *  Output: [0,1]
     *
     *  Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
     *  Output: [0,2]
     *
     *  Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
     *  Output: []
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], x = \"%c\"\n", testCase[i].x);

        pAnswer = findWordsContaining(testCase[i].words, testCase[i].wordsSize, testCase[i].x, &testCase[i].returnSize);
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
