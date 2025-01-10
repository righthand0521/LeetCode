#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTER (26)
void count(char* word, int* pReturnCountArray) {
    int wordSize = strlen(word);
    for (int i = 0; i < wordSize; ++i) {
        pReturnCountArray[word[i] - 'a'] += 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordSubsets(char** words1, int words1Size, char** words2, int words2Size, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int* pCountArray = (int*)malloc(sizeof(int) * MAX_LETTER);
    if (pCountArray == NULL) {
        return pRetVal;
    }
    int i, j;

    int bmax[MAX_LETTER];
    memset(bmax, 0, sizeof(bmax));
    for (i = 0; i < words2Size; ++i) {
        memset(pCountArray, 0, (sizeof(int) * MAX_LETTER));
        count(words2[i], pCountArray);
        for (j = 0; j < MAX_LETTER; ++j) {
            bmax[j] = fmax(bmax[j], pCountArray[j]);
        }
    }

    pRetVal = (char**)malloc(sizeof(char*) * words1Size);
    if (pRetVal == NULL) {
        free(pCountArray);
        pCountArray = NULL;
        return pRetVal;
    }

    int x, y;
    for (i = 0; i < words1Size; ++i) {
        memset(pCountArray, 0, (sizeof(int) * MAX_LETTER));
        count(words1[i], pCountArray);
        for (j = 0; j < MAX_LETTER; ++j) {
            x = pCountArray[j];
            y = bmax[j];
            if (x < y) {
                break;
            }
        }
        if (j == MAX_LETTER) {
            pRetVal[(*returnSize)++] = words1[i];
        }
    }

    free(pCountArray);
    pCountArray = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* words1[MAX_SIZE];
        int words1Size;
        char* words2[MAX_SIZE];
        int words2Size;
        int returnSize;
    } testCase[] = {{{"amazon", "apple", "facebook", "google", "leetcode"}, 5, {"e", "o"}, 2, 0},
                    {{"amazon", "apple", "facebook", "google", "leetcode"}, 5, {"l", "e"}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
     *  Output: ["facebook","google","leetcode"]
     *
     *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
     *  Output: ["apple","google","leetcode"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words1 = [");
        for (j = 0; j < testCase[i].words1Size; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words1[j]);
        }
        printf("], words2 = [");
        for (j = 0; j < testCase[i].words2Size; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words2[j]);
        }
        printf("]\n");

        pAnswer = wordSubsets(testCase[i].words1, testCase[i].words1Size, testCase[i].words2, testCase[i].words2Size,
                              &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
