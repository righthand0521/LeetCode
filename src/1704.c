#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool halvesAreAlike(char* s) {
    bool retVal = true;

    int count = 0;
    int head = 0;
    int tail = strlen(s) - 1;
    while (head < tail) {
        if ((*(s + head) == 'a') || (*(s + head) == 'e') || (*(s + head) == 'i') || (*(s + head) == 'o') ||
            (*(s + head) == 'u') || (*(s + head) == 'A') || (*(s + head) == 'E') || (*(s + head) == 'I') ||
            (*(s + head) == 'O') || (*(s + head) == 'U')) {
            ++count;
        }

        if ((*(s + tail) == 'a') || (*(s + tail) == 'e') || (*(s + tail) == 'i') || (*(s + tail) == 'o') ||
            (*(s + tail) == 'u') || (*(s + tail) == 'A') || (*(s + tail) == 'E') || (*(s + tail) == 'I') ||
            (*(s + tail) == 'O') || (*(s + tail) == 'U')) {
            --count;
        }

        ++head;
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
