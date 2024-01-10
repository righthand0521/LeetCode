#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isVowel(char c) {
    bool retVal = false;

    // The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases
    if ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u')) {
        retVal = true;
    } else if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U')) {
        retVal = true;
    }

    return retVal;
}
char* reverseVowels(char* s) {
    char* pRetVal = NULL;

    char tmp;
    int len = strlen(s);
    int left = 0;
    int right = len - 1;
    while (left < right) {
        while ((left < len) && (isVowel(s[left]) == false)) {
            ++left;
        }
        while ((right > 0) && (isVowel(s[right]) == false)) {
            --right;
        }

        if (left < right) {
            tmp = s[left];
            s[left++] = s[right];
            s[right--] = tmp;
        }
    }
    pRetVal = s;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"hello"}, {"leetcode"}, {".,"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "hello"
     *  Output: "holle"
     *
     *  Input: s = "leetcode"
     *  Output: "leotcede"
     *
     *  Input: s = ".,"
     *  Output: ".,"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = reverseVowels(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
