#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isAlienSorted(char** words, int wordsSize, char* order) {
    bool retVal = false;

    int i, j;

// order.length == 26, All characters in words[i] and order are English lowercase letters.
#define MAX_ORDER_SIZE (26)
    int orderMap[MAX_ORDER_SIZE];

    int len = strlen(order);
    for (i = 0; i < len; ++i) {
        orderMap[order[i] - 'a'] = i;
    }

    for (i = 0; i < wordsSize - 1; ++i) {
        for (j = 0; j < strlen(words[i]); ++j) {
            // substring between words[i] and words[i+1] are the same,
            // but the length of words[i] is greater than words[i+1]
            if (j >= strlen(words[i + 1])) {
                return retVal;
            }

            if (words[i][j] == words[i + 1][j]) {
                continue;
            }

            if (orderMap[words[i][j] - 'a'] > orderMap[words[i + 1][j] - 'a']) {
                return retVal;
            }
            break;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char* order;
    } testCase[] = {{{"hello", "leetcode"}, 2, "hlabcdefgijkmnopqrstuvwxyz"},
                    {{"word", "world", "row"}, 3, "worldabcefghijkmnpqstuvxyz"},
                    {{"apple", "app"}, 2, "abcdefghijklmnopqrstuvwxyz"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].words[j]);
        }
        printf("], order = \"%s\"\n", testCase[i].order);

        answer = isAlienSorted(testCase[i].words, testCase[i].wordsSize, testCase[i].order);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
