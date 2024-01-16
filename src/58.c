#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLastWord(char *s) {
    int retVal = 0;

    int sSize = strlen(s);
    int i;
    for (i = sSize - 1; i >= 0; --i) {
        if (s[i] != ' ') {
            ++retVal;
        } else {
            if (retVal != 0) {
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"Hello World"}, {"   fly me   to   the moon  "}, {"luffy is still joyboy"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "Hello World"
     *  Output: 5
     *
     *  Input: s = "   fly me   to   the moon  "
     *  Output: 4
     *
     *  Input: s = "luffy is still joyboy"
     *  Output: 6
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = lengthOfLastWord(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
