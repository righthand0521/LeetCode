#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canConstruct(char* s, int k) {
    bool retVal = false;

    int sSize = strlen(s);
    if (sSize < k) {
        return retVal;
    } else if (sSize == k) {
        retVal = true;
        return retVal;
    }

    int frequencySize = 26;  // s consists of lowercase English letters.
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }

    int oddCount = 0;
    for (int i = 0; i < frequencySize; ++i) {
        if (frequency[i] % 2 == 1) {
            oddCount++;
        }
    }

    if (oddCount <= k) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"annabelle", 2}, {"leetcode", 3}, {"true", 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "annabelle", k = 2
     *  Output: true
     *
     *  Input: s = "leetcode", k = 3
     *  Output: false
     *
     *  Input: s = "true", k = 4
     *  Output: true
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; i++) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = canConstruct(testCase[i].s, testCase[i].k);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
