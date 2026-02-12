#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestBalanced(char* s) {
    int retVal = 0;

    int sSize = strlen(s);

#define MAX_CHAR (26)  // s consists of lowercase English letters.
    int hashTable[MAX_CHAR];
    bool flag;
    int c;
    for (int i = 0; i < sSize; i++) {
        memset(hashTable, 0, sizeof(hashTable));
        for (int j = i; j < sSize; j++) {
            flag = true;
            c = s[j] - 'a';
            hashTable[c]++;
            for (int k = 0; k < MAX_CHAR; k++) {
                if (hashTable[k] > 0 && hashTable[k] != hashTable[c]) {
                    flag = false;
                    break;
                }
            }

            if (flag == true) {
                retVal = fmax(retVal, j - i + 1);
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"abbac"}, {"zzabccy"}, {"aba"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abbac"
     *  Output: 4
     *
     *  Input: s = "zzabccy"
     *  Output: 4
     *
     *  Input: s = "aba"
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = longestBalanced(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
