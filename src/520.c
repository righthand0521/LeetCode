#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool detectCapitalUse(char* word) {
    bool retVal = true;

    int len = strlen(word);
    if (len == 1) {
        return retVal;
    }

    int i;
    // All letters in this word are capitals
    if (isupper(word[0]) && isupper(word[1])) {
        for (i = 2; i < len; ++i) {
            retVal = isupper(word[i]);
            if (retVal == false) {
                return retVal;
            }
        }

        return retVal;
    }
    // All letters in this word are not capitals or Only the first letter in this word is capital
    for (i = 1; i < len; ++i) {
        retVal = islower(word[i]);
        if (retVal == false) {
            return retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
    } testCase[] = {{"USA"}, {"FlaG"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].word);

        answer = detectCapitalUse(testCase[i].word);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}