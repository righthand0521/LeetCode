#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool halvesAreAlike(char* s) {
    bool retVal = true;

    char* vowels = "aeiouAEIOU";

    int count = 0;
    int head = 0;
    int tail = strlen(s) - 1;
    while (head < tail) {
        if (strchr(vowels, s[head])) {
            ++count;
        }
        ++head;

        if (strchr(vowels, s[tail])) {
            --count;
        }
        --tail;
    }

    if (count != 0) {
        retVal = false;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"book"}, {"textbook"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "book"
     *  Output: true
     *
     *  Input: s = "textbook"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = halvesAreAlike(testCase[i].s);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
