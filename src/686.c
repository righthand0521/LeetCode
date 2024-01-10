#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(int* next, char* pattern) {
    int patternSize = strlen(pattern);

    int j = 0;
    for (int i = 1; i < patternSize; ++i) {
        while ((j > 0) && (pattern[i] != pattern[j])) {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j;
    }
}
int strStr(char* haystack, char* needle) {
    int retVal = -1;

    int needleSize = strlen(needle);
    if (needleSize == 0) {
        retVal = 0;
        return retVal;
    }
    int next[needleSize];
    memset(next, 0, sizeof(next));
    kmp(next, needle);

    int haystackSize = strlen(haystack);
    int haystackIdx = 0;
    int needleIdx = 0;
    while (haystackIdx - needleIdx < haystackSize) {
        while ((needleIdx > 0) && (haystack[haystackIdx % haystackSize] != needle[needleIdx])) {
            needleIdx = next[needleIdx - 1];
        }

        if (haystack[haystackIdx % haystackSize] == needle[needleIdx]) {
            ++needleIdx;
        }

        if (needleIdx == needleSize) {
            retVal = haystackIdx - needleSize + 1;
            break;
        }

        ++haystackIdx;
    }

    return retVal;
}
int repeatedStringMatch(char* a, char* b) {
    int retVal = -1;

    int aSize = strlen(a);
    int bSize = strlen(b);
    int index = strStr(a, b);
    if (index == -1) {
        retVal = -1;
    } else if (aSize - index >= bSize) {
        retVal = 1;
    } else {
        retVal = (bSize + index - aSize - 1) / aSize + 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char a[MAX_SIZE];
        char b[MAX_SIZE];
    } testCase[] = {{"abcd", "cdabcdab"}, {"a", "aa"}, {"aaac", "aac"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: a = "abcd", b = "cdabcdab"
     *  Output: 3
     *
     *  Input: a = "a", b = "aa"
     *  Output: 2
     *
     *  Input: a = "aaac", b = "aac"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: a = \"%s\", b = \"%s\"\n", testCase[i].a, testCase[i].b);

        answer = repeatedStringMatch(testCase[i].a, testCase[i].b);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
