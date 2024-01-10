#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largestVariance(char *s) {
    int retVal = 0;

    int i;

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
    int counter[MAX_LETTERS];
    memset(counter, 0, sizeof(counter));
    for (i = 0; i < strlen(s); ++i) {
        counter[s[i] - 'a']++;
    }

    char major, minor;
    int majorCount, minorCount;
    int restMinor;
    int c1, c2;
    for (c1 = 0; c1 < MAX_LETTERS; ++c1) {
        for (c2 = 0; c2 < MAX_LETTERS; ++c2) {
            // major and minor cannot be the same, and both must appear in s.
            if ((c1 == c2) || (counter[c1] == 0) || (counter[c2] == 0)) {
                continue;
            }

            // Find the maximum variance of major - minor.
            major = 'a' + c1;
            minor = 'a' + c2;
            majorCount = 0;
            minorCount = 0;

            // The remaining minor in the rest of s.
            restMinor = counter[c2];

            for (i = 0; i < strlen(s); ++i) {
                if (s[i] == major) {
                    majorCount++;
                }
                if (s[i] == minor) {
                    minorCount++;
                    restMinor--;
                }

                // Only update the variance (local_max) if there is at least one minor.
                if (minorCount > 0) {
                    retVal = fmax(retVal, majorCount - minorCount);
                }

                // We can discard the previous string if there is at least one remaining minor
                if ((majorCount < minorCount) && (restMinor > 0)) {
                    majorCount = 0;
                    minorCount = 0;
                }
            }
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aababbb"}, {"abcde"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aababbb"
     *  Output: 3
     *
     *  Input: s = "abcde"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = largestVariance(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
