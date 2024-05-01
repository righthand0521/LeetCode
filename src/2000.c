#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reversePrefix(char* word, char ch) {
    char* pRetVal = word;

    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        if (word[i] == ch) {
            break;
        }
    }
    if (i == wordSize) {
        return pRetVal;
    }

    char tmp;
    int left = 0;
    int right = i;
    while (left < right) {
        tmp = word[right];
        word[right--] = word[left];
        word[left++] = tmp;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (250)
    struct testCaseType {
        char word[MAX_SIZE];
        char ch;
    } testCase[] = {{"abcdefd", 'd'}, {"xyxzxe", 'z'}, {"abcd", 'z'}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "abcdefd", ch = "d"
     *  Output: "dcbaefd"
     *
     *  Input: word = "xyxzxe", ch = "z"
     *  Output: "zxyxxe"
     *
     *  Input: word = "abcd", ch = "z"
     *  Output: "abcd"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\", ch = \"%c\"\n", testCase[i].word, testCase[i].ch);

        pAnswer = reversePrefix(testCase[i].word, testCase[i].ch);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
