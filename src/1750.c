#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumLength(char* s) {
    int retVal = 0;

    int len = strlen(s);
    char sameChar;
    int head = 0;
    int tail = len - 1;
    while ((head < tail) && (s[head] == s[tail])) {
        sameChar = s[head];

        while ((head <= tail) && (s[head] == sameChar)) {
            ++head;
        }

        while ((head <= tail) && (s[tail] == sameChar)) {
            --tail;
        }
    }
    retVal = tail - head + 1;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"ca"}, {"cabaabac"}, {"aabccabba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumLength(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
