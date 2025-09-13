#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxFreqSum(char* s) {
    int retVal = 0;

#define ALPHABET_SIZE (26)  // s consists of lowercase English letters only.
    int frequency[ALPHABET_SIZE];
    memset(frequency, 0, sizeof(frequency));
    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        frequency[s[i] - 'a']++;
    }

    char c;
    int vowel = 0;
    int consonant = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (frequency[i] <= 0) {
            continue;
        }

        c = 'a' + i;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vowel = fmax(vowel, frequency[i]);
        } else {
            consonant = fmax(consonant, frequency[i]);
        }
    }
    retVal = vowel + consonant;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"successes"}, {"aeiaeia"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "successes"
     *  Output: 6
     *
     *  Input: s = "aeiaeia"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxFreqSum(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
