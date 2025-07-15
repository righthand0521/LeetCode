#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* word) {
    bool retVal = false;

    int wordSize = strlen(word);
    if (wordSize < 3) {
        return retVal;
    }

    bool hasVowel = false;
    bool hasConsonant = false;
    for (int i = 0; i < wordSize; ++i) {
        char c = word[i];
        if (isalpha(c)) {
            c = tolower(c);
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                hasVowel = true;
            } else {
                hasConsonant = true;
            }
        } else if (isdigit(c)) {
            continue;
        } else {
            return retVal;
        }
    }
    retVal = hasVowel && hasConsonant;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char word[MAX_SIZE];
    } testCase[] = {{"234Adas"}, {"b3"}, {"a3$e"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "234Adas"
     *  Output: true
     *
     *  Input: word = "b3"
     *  Output: false
     *
     *  Input: word = "a3$e"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = isValid(testCase[i].word);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
