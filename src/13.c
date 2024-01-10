#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int romanToInt(char *s) {
    int retVal = 0;

    int romanMapping[26];  // s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
    romanMapping['I' - 'A'] = 1;
    romanMapping['V' - 'A'] = 5;
    romanMapping['X' - 'A'] = 10;
    romanMapping['L' - 'A'] = 50;
    romanMapping['C' - 'A'] = 100;
    romanMapping['D' - 'A'] = 500;
    romanMapping['M' - 'A'] = 1000;

    // III = I + I + I = 1 + 1 + 1 = 3
    // LVIII = L + V + I + I + I = 50 + 5 + 1 + 1 + 1 = 58
    // MCMXCIV = M + C + M + X + C + I + V = 1000 - 100 + 1000 - 10 + 100 - 1 + 5 = 1994
    int currentValue, nextValue;
    int sSize = strlen(s);
    int i;
    for (i = 0; i < sSize - 1; ++i) {
        currentValue = romanMapping[s[i] - 'A'];
        nextValue = romanMapping[s[i + 1] - 'A'];
        if (currentValue < nextValue) {
            retVal -= currentValue;
        } else {
            retVal += currentValue;
        }
    }
    currentValue = romanMapping[s[sSize - 1] - 'A'];
    retVal += currentValue;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (15)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"III"}, {"LVIII"}, {"MCMXCIV"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "III"
     *  Output: 3
     *
     *  Input: s = "LVIII"
     *  Output: 58
     *
     *  Input: s = "MCMXCIV"
     *  Output: 1994
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = romanToInt(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
