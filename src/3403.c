#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* lastSubstring(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int i = 0;
    int j = 1;
    while (j < sSize) {
        int k = 0;
        while ((j + k < sSize) && (s[i + k] == s[j + k])) {
            k++;
        }

        if ((j + k < sSize) && (s[i + k] < s[j + k])) {
            int t = i;
            i = j;
            j = fmax(j + 1, t + k + 1);
        } else {
            j = j + k + 1;
        }
    }
    pRetVal = s + i;

    return pRetVal;
}
char* answerString(char* word, int numFriends) {
    char* pRetVal = word;

    if (numFriends == 1) {
        return pRetVal;
    }

    char* last = lastSubstring(word);
    int lastSize = strlen(last);
    int wordSize = strlen(word);
    int len = fmin(lastSize, wordSize - numFriends + 1);
    last[len] = '\0';

    pRetVal = last;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 1000)
    struct testCaseType {
        char word[MAX_SIZE];
        int numFriends;
    } testCase[] = {{"dbca", 2}, {"gggg", 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "dbca", numFriends = 2
     *  Output: "dbc"
     *
     *  Input: word = "gggg", numFriends = 4
     *  Output: "g"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\", numFriends = %d\n", testCase[i].word, testCase[i].numFriends);

        pAnswer = answerString(testCase[i].word, testCase[i].numFriends);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        // free(pAnswer);
        // pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
