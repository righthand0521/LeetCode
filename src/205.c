#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isIsomorphic(char* s, char* t) {
    bool retVal = false;

    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize) {
        return retVal;
    }

#define MAX_HASHTABLE_SIZE (128)  // s and t consist of any valid ascii character.
#define HASHTABLE_INIT_VALUE (-1)
    int hashTableS[MAX_HASHTABLE_SIZE];
    int hashTableT[MAX_HASHTABLE_SIZE];

    int i;
    for (i = 0; i < MAX_HASHTABLE_SIZE; ++i) {
        hashTableS[i] = HASHTABLE_INIT_VALUE;
        hashTableT[i] = HASHTABLE_INIT_VALUE;
    }

    int si, ti;
    for (i = 0; i < sSize; ++i) {
        si = s[i];
        ti = t[i];
        if ((hashTableS[si] != HASHTABLE_INIT_VALUE) && (hashTableS[si] != ti)) {
            return retVal;
        } else if ((hashTableT[ti] != HASHTABLE_INIT_VALUE) && (hashTableT[ti] != si)) {
            return retVal;
        } else {
            hashTableS[si] = ti;
            hashTableT[ti] = si;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"egg", "add"},
                    {"foo", "bar"},
                    {"paper", "title"},
                    {"badc", "baba"},
                    {"abcdefghijklmnopqrstuvwxyzva", "abcdefghijklmnopqrstuvwxyzck"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "egg", t = "add"
     *  Output: true
     *
     *  Input: s = "foo", t = "bar"
     *  Output: false
     *
     *  Input: s = "paper", t = "title"
     *  Output: true
     *
     *  Input: s = "badc", t = "baba"
     *  Output: false
     *
     *  Input: s = "abcdefghijklmnopqrstuvwxyzva", t = "abcdefghijklmnopqrstuvwxyzck"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = isIsomorphic(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
