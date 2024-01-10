#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int characterReplacement(char* s, int k) {
    int retVal = 0;

    // s consists of only uppercase English letters.
#define MAX_RECORD (26)
    int Record[MAX_RECORD];
    memset(Record, 0, sizeof(Record));

    int maxRecord = 0;
    int sSize = strlen(s);
    int left = 0;
    int right = 0;
    while (right < sSize) {
        Record[s[right] - 'A']++;

        maxRecord = fmax(maxRecord, Record[s[right] - 'A']);
        if (right - left + 1 - maxRecord > k) {
            Record[s[left] - 'A']--;
            left++;
        }

        right++;
    }
    retVal = right - left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"ABAB", 2}, {"AABABBA", 1}, {"ABAA", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ABAB", k = 2
     *  Output: 4
     *
     *  Input: s = "AABABBA", k = 1
     *  Output: 4
     *
     *  Input: s = "ABAA", k = 0
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = characterReplacement(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
