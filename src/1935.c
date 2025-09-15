#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canBeTypedWords(char* text, char* brokenLetters) {
    int retVal = 0;

    char* words[strlen(text)];
    int wordsSize = 0;
#define STRTOK_PATTERN (" ")
    char* p = strtok(text, STRTOK_PATTERN);
    while (p != NULL) {
        words[wordsSize++] = p;
        p = strtok(NULL, STRTOK_PATTERN);
    }

    for (int i = 0; i < wordsSize; ++i) {
        if (strpbrk(words[i], brokenLetters) == NULL) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char text[MAX_SIZE];
        char brokenLetters[MAX_SIZE];
    } testCase[] = {{"hello world", "ad"}, {"leet code", "lt"}, {"leet code", "e"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: text = "hello world", brokenLetters = "ad"
     *  Output: 1
     *
     *  Input: text = "leet code", brokenLetters = "lt"
     *  Output: 1
     *
     *  Input: text = "leet code", brokenLetters = "e"
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: text = \"%s\", brokenLetters = \"%s\"\n", testCase[i].text, testCase[i].brokenLetters);

        answer = canBeTypedWords(testCase[i].text, testCase[i].brokenLetters);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
