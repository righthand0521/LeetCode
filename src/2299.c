#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool strongPasswordCheckerII(char* password) {
    bool retVal = false;

#define STRONG_PASSWORD_LENGTH (8)
#define STRONG_PASSWORD_SPECIAL_CHARACTERS "!@#$%^&*()-+"
#define STRONG_PASSWORD_LOWERCASE_BIT (0)
#define STRONG_PASSWORD_UPPERCASE_BIT (1)
#define STRONG_PASSWORD_DIGIT_BIT (2)
#define STRONG_PASSWORD_SPECIAL_BIT (3)

    int len = strlen(password);
    if (len < STRONG_PASSWORD_LENGTH) {
        return retVal;
    }

    int resultBit = 0;
    int idx;
    int i;
    for (i = 0; i < len; ++i) {
        // It does not contain 2 of the same character in adjacent positions.
        if (password[i] == password[i + 1]) {
            return retVal;
        }

        if ((password[i] >= 'a') && (password[i] <= 'z')) {
            resultBit |= (1 << STRONG_PASSWORD_LOWERCASE_BIT);
        } else if ((password[i] >= 'A') && (password[i] <= 'Z')) {
            resultBit |= (1 << STRONG_PASSWORD_UPPERCASE_BIT);
        } else if ((password[i] >= '0') && (password[i] <= '9')) {
            resultBit |= (1 << STRONG_PASSWORD_DIGIT_BIT);
        } else {
            idx = 0;
            while (STRONG_PASSWORD_SPECIAL_CHARACTERS[idx] != 0) {
                if (password[i] == STRONG_PASSWORD_SPECIAL_CHARACTERS[idx++]) {
                    resultBit |= (1 << STRONG_PASSWORD_SPECIAL_BIT);
                    break;
                }
            }
        }
    }
    if (resultBit == ((1 << STRONG_PASSWORD_LOWERCASE_BIT) | (1 << STRONG_PASSWORD_UPPERCASE_BIT) |
                      (1 << STRONG_PASSWORD_DIGIT_BIT) | (1 << STRONG_PASSWORD_SPECIAL_BIT))) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char password[MAX_SIZE];
    } testCase[] = {{"IloveLe3tcode!"}, {"Me+You--IsMyDream"}, {"1aB!"}, {"aA0!bB1@@3rbHkB8Puvl"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: password = \"%s\"\n", testCase[i].password);

        answer = strongPasswordCheckerII(testCase[i].password);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
