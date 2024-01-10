#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPrefixes(char** words, int wordsSize, char* s) {
    int retVal = 0;

    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (strncmp(words[i], s, strlen(words[i])) == 0) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char* s;
    } testCase[] = {{{"a", "b", "c", "ab", "bc", "abc"}, 6, "abc"}, {{"a", "a"}, 2, "aa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], s = \"%s\"\n", testCase[i].s);

        answer = countPrefixes(testCase[i].words, testCase[i].wordsSize, testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
