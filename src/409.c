#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestPalindrome(char* s) {
    int retVal = 0;

#define MAX_FREQUENCY_SIZE (128)  // s consists of lowercase and/or uppercase English letters only.
    int frequency[MAX_FREQUENCY_SIZE];
    memset(frequency, 0, sizeof(frequency));
    int sSize = strlen(s);
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i];
        frequency[idx] += 1;
    }

    int value;
    for (i = 0; i < MAX_FREQUENCY_SIZE; ++i) {
        value = frequency[i];
        retVal += (value / 2 * 2);
        if ((value % 2 == 1) && (retVal % 2 == 0)) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"abccccdd"}, {"a"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abccccdd"
     *  Output: 7
     *
     *  Input: s = "a"
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestPalindrome(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
