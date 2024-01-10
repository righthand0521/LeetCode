#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLastWord(char *s) {
    int len = strlen(s);
    if (len == 0) {
        return 0;
    }

    int i = 0;
    while (*(s + (len - 1) - i) == ' ') {
        *(s + (len - 1) - i) = '\0';
        i++;
    }
    len = strlen(s);
    if (len == 0) {
        return 0;
    }

    i = 0;
    while (*(s + (len - 1) - i) != ' ') {
        i++;
        if (i == len) {
            break;
        }
    }

    return i;
}

int main(int argc, char **argv) {
    char *testCase[] = {"Hello World", "   fly me   to   the moon  ", "luffy is still joyboy"};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

#define MAX_STRING (100000)
    char buf[MAX_STRING];

    int pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i]);

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s", testCase[i]);
        pAnswer = lengthOfLastWord(buf);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
