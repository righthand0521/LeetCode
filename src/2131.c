#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0  // Time Limit Exceeded
#define MAX_WORD_LENGTH (4)
bool search(char** pRecord, int pRecordSize, char* pSearch)
{
    int i;
    for (i=0; i<pRecordSize; ++i)
    {
        // printf("%2d: %s; %s\n", i, pRecord[i], pSearch);
        if (strcmp(pRecord[i], pSearch) == 0)
        {
            memset(pRecord[i], 0, MAX_WORD_LENGTH*sizeof(char));
            return true;
        }
    }

    return false;
}
int longestPalindrome(char ** words, int wordsSize){
    int retVal = 0;

    int i, j;

    char** pRecord = (char**)malloc(wordsSize*sizeof(char*));
    if (pRecord == NULL)
    {
        perror("malloc");
        return retVal;
    }
    for (i=0; i<wordsSize; ++i)
    {
        pRecord[i] = (char*)malloc(MAX_WORD_LENGTH*sizeof(char));
        if (pRecord[i] == NULL)
        {
            perror("malloc");
            for (j=0; j<i; ++j)
            {
                free(pRecord[j]);
                pRecord[j] = NULL;
            }
            free(pRecord);
            pRecord = NULL;
            return retVal;
        }
        memset(pRecord[i], 0, MAX_WORD_LENGTH*sizeof(char));
    }

    bool isHit = false;
    for (i=0; i<wordsSize; ++i)
    {
        isHit = search(pRecord, i+1, words[i]);
        if (isHit == false)
        {
            pRecord[i][0] = words[i][1];
            pRecord[i][1] = words[i][0];
            continue;
        }
        retVal += 4;
    }
    for (i=0; i<wordsSize; ++i)
    {
        //printf("%2d: %s\n", i, pRecord[i]);
        if (strlen(pRecord[i]) == 0)
        {
            continue;
        }

        if (pRecord[i][0] == pRecord[i][1])
        {
            retVal += 2;
            break;
        }
    }

    for (i=0; i<wordsSize; ++i)
    {
        free(pRecord[i]);
        pRecord[i] = NULL;
    }
    free(pRecord);
    pRecord = NULL;

    return retVal;
}
#else
int longestPalindrome(char** words, int wordsSize) {
    int retVal = 0;

    // words[i] consists of lowercase English letters.
#define MAX_LETTERS (26)
#define MAX_RECORD (MAX_LETTERS * MAX_LETTERS)
    int RECORD[MAX_RECORD] = {0};

    int index;
    int i;
    for (i = 0; i < wordsSize; ++i) {
        index = ((words[i][0] - 'a') * MAX_LETTERS) + (words[i][1] - 'a');
        if (RECORD[index] == 0) {
            index = ((words[i][1] - 'a') * MAX_LETTERS) + (words[i][0] - 'a');
            ++RECORD[index];
            continue;
        }
        retVal += 4;
        --RECORD[index];
    }

    for (i = 0; i < MAX_LETTERS; ++i) {
        index = (i * MAX_LETTERS) + i;
        if (RECORD[index] != 0) {
            retVal += 2;
            break;
        }
    }

    return retVal;
}
#endif

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {{{"lc", "cl", "gg"}, 3}, {{"ab", "ty", "yt", "lc", "cl", "ab"}, 6}, {{"cc", "ll", "xx"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["lc","cl","gg"]
     *  Output: 6
     *
     *  Input: words = ["ab","ty","yt","lc","cl","ab"]
     *  Output: 8
     *
     *  Input: words = ["cc","ll","xx"]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = longestPalindrome(testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
