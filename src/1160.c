#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countCharacters(char **words, int wordsSize, char *chars) {
    int retVal = 0;

    int i, j, idx;

    // words[i] and chars consist of lowercase English letters.
    int charsCount[26];
    memset(charsCount, 0, sizeof(charsCount));

    int charsSize = strlen(chars);
    for (i = 0; i < charsSize; ++i) {
        idx = chars[i] - 'a';
        charsCount[idx]++;
    }

    int check[26];
    int count, wordSize;
    for (i = 0; i < wordsSize; ++i) {
        memset(check, 0, sizeof(check));
        memcpy(check, charsCount, sizeof(check));
        count = 0;

        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            idx = words[i][j] - 'a';
            if (check[idx] == 0) {
                break;
            }
            check[idx]--;
            count++;
        }

        if (count == wordSize) {
            retVal += count;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *words[MAX_SIZE];
        int wordsSize;
        char *chars;
    } testCase[] = {{{"cat", "bt", "hat", "tree"}, 4, "atach"}, {{"hello", "world", "leetcode"}, 3, "welldonehoneyr"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["cat","bt","hat","tree"], chars = "atach"
     *  Output: 6
     *
     *  Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
     *  Output: 10
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], chars = \"%s\"\n", testCase[i].chars);

        answer = countCharacters(testCase[i].words, testCase[i].wordsSize, testCase[i].chars);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
