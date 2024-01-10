#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool makeEqual(char** words, int wordsSize) {
    bool retVal = true;

// words[i] consists of lowercase English letters.
#define MAX_LETTERS (26)

    int hashTable[MAX_LETTERS];
    memset(hashTable, 0, sizeof(hashTable));

    int len, idx;
    int i, j;
    for (i = 0; i < wordsSize; ++i) {
        len = strlen(words[i]);
        for (j = 0; j < len; ++j) {
            idx = words[i][j] - 'a';
            hashTable[idx] += 1;
        }
    }

    for (i = 0; i < MAX_LETTERS; ++i) {
        if (hashTable[i] % wordsSize != 0) {
            retVal = false;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {{{"abc", "aabc", "bc"}, 3}, {{"ab", "a"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["abc","aabc","bc"]
     *  Output: true
     *
     *  Input: words = ["ab","a"]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].words[j]);
        }
        printf("]\n");

        answer = makeEqual(testCase[i].words, testCase[i].wordsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
