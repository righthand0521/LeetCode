#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int minDeletions(char* s) {
    int retVal = 0;

#define MAX_FREQUENCY_SIZE (26)  // s contains only lowercase English letters.
    int frequency[MAX_FREQUENCY_SIZE];
    memset(frequency, 0, sizeof(frequency));

    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }
    qsort(frequency, MAX_FREQUENCY_SIZE, sizeof(int), compareInteger);

    int previousFrequency = frequency[0];
    int j;
    for (i = 1; i < MAX_FREQUENCY_SIZE; ++i) {
        for (j = frequency[i]; j > 0; --j) {
            if (j < previousFrequency) {
                previousFrequency = j;
                break;
            }
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aab"}, {"aaabbbcc"}, {"ceabaacb"}, {"abc"}, {"aaab"}, {"abcabc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aab"
     *  Output: 0
     *
     *  Input: s = "aaabbbcc"
     *  Output: 2
     *
     *  Input: s = "ceabaacb"
     *  Output: 2
     *
     *  Input: s = "abc"
     *  Output: 2
     *
     *  Input: s = "aaab"
     *  Output: 0
     *
     *  Input: s = "abcabc"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minDeletions(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
