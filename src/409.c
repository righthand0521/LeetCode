#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestPalindrome(char* s) {
    int retVal = 0;

#define ASCII_SIZE (128)
    int asciiTable[ASCII_SIZE] = {0};

    while (*s) {
        ++asciiTable[(unsigned char)(*s)];
        if (asciiTable[(unsigned char)(*s)] == 2) {
            retVal += 2;
            asciiTable[(unsigned char)(*s)] = 0;
        }
        ++s;
    }

    int i;
    for (i = 0; i < ASCII_SIZE; ++i) {
        if (asciiTable[i] == 1) {
            ++retVal;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"abccccdd"}, {"a"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestPalindrome(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
