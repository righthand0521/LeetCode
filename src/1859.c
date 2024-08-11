#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *sortSentence(char *s) {
    char *pRetVal = NULL;

    int sSize = strlen(s);

    pRetVal = (char *)calloc(sSize + 1, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

#define MAX_WORDS (9)  //  The number of words in s is between 1 and 9.
    char buf[MAX_WORDS][sSize];
    memset(buf, 0, sizeof(buf));

    int idx = 0;
    char tmp[sSize];
    memset(tmp, 0, sizeof(tmp));
    int len = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        if (s[i] == ' ') {
            continue;
        } else if (isdigit(s[i])) {
            idx = (s[i] - '0') - 1;
            snprintf(buf[idx], sSize, "%s", tmp);
            memset(tmp, 0, sizeof(tmp));
            len = 0;
        } else {
            tmp[len++] = s[i];
        }
    }

    idx = 0;
    for (i = 0; i < MAX_WORDS; ++i) {
        if (strlen(buf[i]) == 0) {
            continue;
        }
        idx += snprintf(pRetVal + idx, ((sSize + 1) * sizeof(char)), "%s ", buf[i]);
    }
    pRetVal[strlen(pRetVal) - 1] = '\0';

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"is2 sentence4 This1 a3"}, {"Myself2 Me1 I4 and3"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "is2 sentence4 This1 a3"
     *  Output: "This is a sentence"
     *
     *  Input: s = "Myself2 Me1 I4 and3"
     *  Output: "Me Myself and I"
     */

    char *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sentence = \"%s\"\n", testCase[i].s);

        pAnswer = sortSentence(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
