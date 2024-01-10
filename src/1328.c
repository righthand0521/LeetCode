#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* breakPalindrome(char* palindrome) {
    char* pRetVal = "";

    int len = strlen(palindrome);
    // There is no way to replace a single character
    if (len == 1) {
        return pRetVal;
    }

    int head = 0;
    int tail = len - 1;
    while (head < tail) {
        // replace first to lexicographically smallest
        if (*(palindrome + head) != 'a') {
            *(palindrome + head) = 'a';
            break;
        }
        ++head;
        --tail;
    }
    // update last character to lexicographically smallest
    if (head >= tail) {
        *(palindrome + len - 1) = 'b';
    }
    pRetVal = palindrome;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char palindrome[MAX_SIZE];
    } testCase[] = {{"abccba"}, {"a"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: palindrome = \"%s\"\n", testCase[i].palindrome);

        pAnswer = breakPalindrome(testCase[i].palindrome);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
