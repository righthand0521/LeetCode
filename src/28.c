#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KMP_START_IDX (-1)
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(int* next, char* pattern) {
    int patternSize = strlen(pattern);

    int j = KMP_START_IDX;
    next[0] = j;
    int i;
    for (i = 1; i < patternSize; ++i) {
        while ((j >= 0) && (pattern[i] != pattern[j + 1])) {
            j = next[j];
        }

        if (pattern[i] == pattern[j + 1]) {
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
    int needleIdx = KMP_START_IDX;
    int haystackIdx = 0;
    for (haystackIdx = 0; haystackIdx < haystackSize; ++haystackIdx) {
        while ((needleIdx >= 0) && (haystack[haystackIdx] != needle[needleIdx + 1])) {
            needleIdx = next[needleIdx];
        }

        if (haystack[haystackIdx] == needle[needleIdx + 1]) {
            ++needleIdx;
        }

        if (needleIdx == needleSize - 1) {
            retVal = haystackIdx - needleSize + 1;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char haystack[MAX_SIZE];
        char needle[MAX_SIZE];
    } testCase[] = {{"sadbutsad", "sad"}, {"leetcode", "leeto"}, {"mississippi", "issip"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: haystack = "sadbutsad", needle = "sad"
     *  Output: 0
     *
     *  Input: haystack = "leetcode", needle = "leeto"
     *  Output: -1
     *
     *  Input: haystack = "mississippi", needle = "issip"
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: haystack = \"%s\", needle = \"%s\"\n", testCase[i].haystack, testCase[i].needle);

        answer = strStr(testCase[i].haystack, testCase[i].needle);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
