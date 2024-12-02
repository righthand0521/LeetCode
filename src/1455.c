#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPrefixOfWord(char* sentence, char* searchWord) {
    int retVal = -1;

    int len = strlen(searchWord);
    int idx = 0;
#define SEPARATED " "
    char* pStr = strtok(sentence, SEPARATED);
    while (pStr != NULL) {
        ++idx;
        if (strncmp(pStr, searchWord, len) == 0) {
            retVal = idx;
            break;
        }

        pStr = strtok(NULL, SEPARATED);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SENTENCE_SIZE (100)
#define MAX_SEARCHWORD_SIZE (10)
    struct testCaseType {
        char sentence[MAX_SENTENCE_SIZE];
        char searchWord[MAX_SEARCHWORD_SIZE];
    } testCase[] = {
        {"i love eating burger", "burg"}, {"this problem is an easy problem", "pro"}, {"i am tired", "you"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: sentence = "i love eating burger", searchWord = "burg"
     *  Output: 4
     *
     *  Input: sentence = "this problem is an easy problem", searchWord = "pro"
     *  Output: 2
     *
     *  Input: sentence = "i am tired", searchWord = "you"
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sentence = \"%s\", searchWord = \"%s\"\n", testCase[i].sentence, testCase[i].searchWord);

        answer = isPrefixOfWord(testCase[i].sentence, testCase[i].searchWord);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
