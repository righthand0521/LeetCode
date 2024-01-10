#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxVowels(char* s, int k) {
    int retVal = 0;

#define MAX_VOWELS_SIZE (5)
    char vowels[MAX_VOWELS_SIZE] = {'a', 'e', 'i', 'o', 'u'};

    int i, j;

    int count = 0;
    for (i = 0; i < k; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
                break;
            }
        }
    }
    retVal = count;

    int sSize = strlen(s);
    for (i = k; i < sSize; ++i) {
        for (j = 0; j < MAX_VOWELS_SIZE; ++j) {
            if (s[i] == vowels[j]) {
                ++count;
            }

            if (s[i - k] == vowels[j]) {
                --count;
            }
        }
        retVal = fmax(retVal, count);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int k;
    } testCase[] = {{"abciiidef", 3}, {"aeiou", 2}, {"leetcode", 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abciiidef", k = 3
     *  Output: 3
     *
     *  Input: s = "aeiou", k = 2
     *  Output: 2
     *
     *  Input: s = "leetcode", k = 3
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        answer = maxVowels(testCase[i].s, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
