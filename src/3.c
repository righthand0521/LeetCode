#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int retVal = 0;

    // s consists of English letters, digits, symbols and spaces.
#define MAX_CHAR_RANGE (256)
    int hashTable[MAX_CHAR_RANGE];
    memset(hashTable, 0, sizeof(hashTable));

    int head = 0;
    int tail = 0;
    while ((*(s + head) != 0) && (*(s + tail) != 0)) {
        if ((hashTable[(int)(*(s + head))] != 0) && (hashTable[(int)(*(s + tail))] != 0)) {
            hashTable[(int)(*(s + head))] = 0;
            ++head;
        } else {
            hashTable[(int)(*(s + tail))] = 1;
            ++tail;
        }
        retVal = fmax(retVal, (tail - head));
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abcabcbb"}, {"bbbbb"}, {"pwwkew"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcabcbb"
     *  Output: 3
     *
     *  Input: s = "bbbbb"
     *  Output: 1
     *
     *  Input: s = "pwwkew"
     *  Output: 3
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = lengthOfLongestSubstring(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
