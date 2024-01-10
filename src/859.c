#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool buddyStrings(char* s, char* goal) {
    bool retVal = false;

    int sSize = strlen(s);
    int goalSize = strlen(goal);
    if (sSize != goalSize) {
        return retVal;
    }

    int i;

    int frequency[26];
    memset(frequency, 0, sizeof(frequency));
    if (strcmp(s, goal) == 0) {
        // If we have 2 same characters in string 's', we can swap them and still strings will remain equal.
        for (i = 0; i < sSize; ++i) {
            frequency[s[i] - 'a'] += 1;
            if (frequency[s[i] - 'a'] == 2) {
                retVal = true;
                return retVal;
            }
        }

        // Otherwise, if we swap any two chanacters it will make strings unequal.
        return retVal;
    }

    int firstIndex = -1;
    int secondIndex = -1;
    for (i = 0; i < sSize; ++i) {
        if (s[i] != goal[i]) {
            if (firstIndex == -1) {
                firstIndex = i;
            } else if (secondIndex == -1) {
                secondIndex = i;
            } else {
                // We have atleast 3 indices with differnet characters,
                // thus, we can never make strings equal with only one swap.
                return retVal;
            }
        }
    }

    if (secondIndex == -1) {
        // We can't swap if character at only one index is different.
        return retVal;
    }

    // All characters of both the string are same except two indices.
    retVal = ((s[firstIndex] == goal[secondIndex]) && (s[secondIndex] == goal[firstIndex]));

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char goal[MAX_SIZE];
    } testCase[] = {{"ab", "ba"}, {"ab", "ab"}, {"aa", "aa"}, {"ab", "babbb"}, {"abcaa", "abcbb"}, {"abcd", "abcd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ab", goal = "ba"
     *  Output: true
     *
     *  Input: s = "ab", goal = "ab"
     *  Output: false
     *
     *  Input: s = "aa", goal = "aa"
     *  Output: true
     *
     *  Input: s = "ab", goal = "babbb"
     *  Output: false
     *
     *  Input: s = "abcaa", goal = "abcbb
     *  Output: false
     *
     *  Input: s = "abcd", goal = "abcd"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", goal = \"%s\"\n", testCase[i].s, testCase[i].goal);

        answer = buddyStrings(testCase[i].s, testCase[i].goal);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
