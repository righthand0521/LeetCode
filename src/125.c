#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char *s) {
    int retVal = true;

    int len = strlen(s);
    if (len == 0) {
        return retVal;
    }

    char *pHead = s;
    char *pTail = s + len - 1;
    while (pHead < pTail) {
        // A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
        // and removing all non - alphanumeric characters, it reads the same forward and backward.
        // Alphanumeric characters include letters and numbers.
        if (isalnum(*pHead) == 0) {
            pHead++;
            continue;
        }
        if (isalnum(*pTail) == 0) {
            pTail--;
            continue;
        }

        if (isupper(*pHead)) {
            *pHead += 32;
        }
        if (isupper(*pTail)) {
            *pTail += 32;
        }
        if ((*pHead - *pTail) != 0) {
            retVal = false;
            break;
        }
        pHead++;
        pTail--;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"A man, a plan, a canal: Panama"}, {"race a car"}, {" "}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "A man, a plan, a canal: Panama"
     *  Output: true
     *
     *  Input: s = "race a car"
     *  Output: false
     *
     *  Input: s = " "
     *  Output: true
     */

    bool pAnswer = true;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = isPalindrome(testCase[i].s);
        printf("Output: %s\n", pAnswer ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
