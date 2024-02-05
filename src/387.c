#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int firstUniqChar(char* s) {
    int retVal = -1;

#define MAX_HASHTABLE_SIZE (26)  // s consists of only lowercase English letters.
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int sSize = strlen(s);
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        ++hashTable[idx];
    }

    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (hashTable[idx] == 1) {
            retVal = i;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"leetcode"}, {"loveleetcode"}, {"aabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leetcode"
     *  Output: 0
     *
     *  Input: s = "loveleetcode"
     *  Output: 2
     *
     *  Input: s = "aabb"
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = firstUniqChar(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
