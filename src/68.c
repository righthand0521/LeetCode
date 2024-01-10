#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillWords(char** words, int iNum, char* pRet, int iLen, int maxWidth) {
    int iAveNum = 0;
    int iresNum = 0;
    int iSpaceNum = maxWidth - iLen;
    if (iNum > 1) {
        iAveNum = iSpaceNum / (iNum - 1);
        iresNum = iSpaceNum % (iNum - 1);
    }

    int i;
    for (i = 0; i < maxWidth; i++) {
        pRet[i] = ' ';
    }
    int ipos = 0;
    for (i = 0; i < iNum; i++) {
        memcpy(&pRet[ipos], words[i], strlen(words[i]));
        ipos += strlen(words[i]) + iAveNum;
        if (iresNum > 0) {
            ipos += 1;
            iresNum -= 1;
        }
    }
}
void fillWordsLastRow(char** words, int iNum, char* pRet, int maxWidth) {
    int i;
    for (i = 0; i < maxWidth; i++) {
        pRet[i] = ' ';
    }
    int ipos = 0;
    for (i = 0; i < iNum; i++) {
        memcpy(&pRet[ipos], words[i], strlen(words[i]));
        ipos += strlen(words[i]) + 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    //
    if ((NULL == words) || (0 == wordsSize)) {
        return pRetVal;
    }

    //
    pRetVal = (char**)malloc(wordsSize * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (wordsSize * sizeof(char*)));
    int returnColumnSize = maxWidth + 1;

    //
    int iPos = 0;
    int iTmpNum = 0;
    int iTmpLen = 0;
    int iRetSize = 0;
    int i, j;
    for (i = 0; i < wordsSize; i++) {
        if (iTmpLen + strlen(words[i]) + iTmpNum > maxWidth) {
            pRetVal[iRetSize] = (char*)malloc(returnColumnSize * sizeof(char));
            if (pRetVal[iRetSize] == NULL) {
                perror("malloc");
                for (j = 0; j < i; ++j) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
                free(pRetVal);
                pRetVal = NULL;
                return pRetVal;
            }
            memset(pRetVal[iRetSize], 0, (returnColumnSize * sizeof(char)));

            fillWords(&words[iPos], iTmpNum, pRetVal[iRetSize], iTmpLen, maxWidth);
            iPos = i;
            iTmpNum = 0;
            iTmpLen = 0;
            iRetSize += 1;
        }

        iTmpNum += 1;
        iTmpLen += strlen(words[i]);
    }
    //
    if (iPos <= wordsSize - 1) {
        pRetVal[iRetSize] = (char*)malloc(returnColumnSize * sizeof(char));
        if (pRetVal[iRetSize] == NULL) {
            perror("malloc");
            for (j = 0; j < iRetSize; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[iRetSize], 0, (returnColumnSize * sizeof(char)));

        fillWordsLastRow(&words[iPos], iTmpNum, pRetVal[iRetSize], maxWidth);
        iRetSize += 1;
    }
    //
    (*returnSize) = iRetSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int maxWidth;
        int returnSize;
    } testCase[] = {{{"This", "is", "an", "example", "of", "text", "justification."}, 7, 16, 0},
                    {{"What", "must", "be", "acknowledgment", "shall", "be"}, 6, 16, 0},
                    {{"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a",
                      "computer.", "Art", "is", "everything", "else", "we", "do"},
                     18,
                     20,
                     0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
     *  Output:
     *  [
     *     "This    is    an",
     *     "example  of text",
     *     "justification.  "
     *  ]
     *
     *  Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
     *  Output:
     *  [
     *    "What   must   be",
     *    "acknowledgment  ",
     *    "shall be        "
     *  ]
     *
     *  Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.",
     *  "Art","is","everything","else","we","do"], maxWidth = 20
     *  Output:
     *  [
     *    "Science  is  what we",
     *    "understand      well",
     *    "enough to explain to",
     *    "a  computer.  Art is",
     *    "everything  else  we",
     *    "do                  "
     *  ]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], maxWidth = %d\n", testCase[i].maxWidth);

        pAnswer = fullJustify(testCase[i].words, testCase[i].wordsSize, testCase[i].maxWidth, &testCase[i].returnSize);
        printf("Output:\n[\n");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s  \"%s\"", (j == 0) ? "" : ",\n", pAnswer[j]);
        }
        printf("\n]\n");

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
