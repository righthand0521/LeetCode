#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSteps(char* s, char* t) {
    int retVal = 0;

    int sSize = strlen(s);  // s.length == t.length
    int i;

#define MAX_HASHTABLE_SIZE (26)  // s and t consist of lowercase English letters only.
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));
    for (i = 0; i < sSize; ++i) {
        hashTable[s[i] - 'a']++;
        hashTable[t[i] - 'a']--;
    }

    for (i = 0; i < MAX_HASHTABLE_SIZE; ++i) {
        if (hashTable[i] > 0) {
            retVal += hashTable[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"bab", "aba"}, {"leetcode", "practice"}, {"anagram", "mangaar"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "bab", t = "aba"
     *  Output: 1
     *
     *  Input: s = "leetcode", t = "practice"
     *  Output: 5
     *
     *  Input: s = "anagram", t = "mangaar"
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = minSteps(testCase[i].s, testCase[i].t);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
