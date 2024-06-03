#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int appendCharacters(char* s, char* t) {
    int retVal = 0;

    int sSize = strlen(s);
    int tSize = strlen(t);

    int idxS = 0;
    int idxT = 0;
    while ((idxS < sSize) && (idxT < tSize)) {
        if (s[idxS] == t[idxT]) {
            idxT += 1;
        }
        idxS += 1;
    }
    retVal = tSize - idxT;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"coaching", "coding"}, {"abcde", "a"}, {"z", "abcde"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "coaching", t = "coding"
     *  Output: 4
     *
     *  Input: s = "abcde", t = "a"
     *  Output: 0
     *
     *  Input: s = "z", t = "abcde"
     *  Output: 5
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = appendCharacters(testCase[i].s, testCase[i].t);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
