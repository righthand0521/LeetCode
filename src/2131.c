#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // words[i] consists of lowercase English letters.
int longestPalindrome(char** words, int wordsSize) {
    int retVal = 0;

    int frequencySize = MAX_LETTERS * MAX_LETTERS;  // words[i].length == 2
    int frequency[frequencySize];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; i < wordsSize; i++) {
        int idx = (words[i][0] - 'a') * 26 + (words[i][1] - 'a');
        frequency[idx]++;
    }

    bool middle = false;
    for (int i = 0; i < frequencySize; i++) {
        if (frequency[i] == 0) {
            continue;
        }
        int reverseWord = (i % 26) * 26 + (i / 26);
        if (i == reverseWord) {
            if (frequency[i] % 2 == 1) {
                middle = true;
            }
            retVal += (2 * (frequency[i] / 2 * 2));
        } else if (i > reverseWord) {
            retVal += (4 * fmin(frequency[i], frequency[reverseWord]));
        }
    }
    if (middle == true) {
        retVal += 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {{{"lc", "cl", "gg"}, 3}, {{"ab", "ty", "yt", "lc", "cl", "ab"}, 6}, {{"cc", "ll", "xx"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["lc","cl","gg"]
     *  Output: 6
     *
     *  Input: words = ["ab","ty","yt","lc","cl","ab"]
     *  Output: 8
     *
     *  Input: words = ["cc","ll","xx"]
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = longestPalindrome(testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
