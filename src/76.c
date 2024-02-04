#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minWindow(char* s, char* t) {
    char* pRetVal = "";

    int sSize = strlen(s);
    int tSize = strlen(t);

    int i;

#define ASCII_SIZE (128)      // s and t consist of uppercase and lowercase English letters.
    int hashSet[ASCII_SIZE];  // use hash set to record character in t
    memset(hashSet, 0, sizeof(hashSet));
    for (i = 0; i < tSize; ++i) {
        ++hashSet[(unsigned char)t[i]];
    }

    /* Process
     *  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  | ABC           |
     *  |------------------------------------------------------------------------------------------|---------------|
     *  |   A  |   D  |   O  |   B  |   E  |   C  |   O  |   D  |   E  |   B  |   A  |   N  |   C  |               |
     *  | head |      |      |      |      | tail |      |      |      |      |      |      |      | => ADOBEC     |
     *  |      | head |      |      |      | tail |      |      |      |      |      |      |      | -X-> DOBEC    |
     *  |      | head |      |      |      |      |      |      |      |      | tail |      |      | => DOBECODEBA |
     *  |      |      | head |      |      |      |      |      |      |      | tail |      |      | => OBECODEBA  |
     *  |      |      |      | head |      |      |      |      |      |      | tail |      |      | => BECODEBA   |
     *  |      |      |      |      | head |      |      |      |      |      | tail |      |      | => ECODEBA    |
     *  |      |      |      |      |      | head |      |      |      |      | tail |      |      | => CODEBA     |
     *  |      |      |      |      |      |      | head |      |      |      | tail |      |      | -X-> ODEBA    |
     *  |      |      |      |      |      |      | head |      |      |      |      |      | tail | => ODEBANC    |
     *  |      |      |      |      |      |      |      | head |      |      |      |      | tail | => DEBANC     |
     *  |      |      |      |      |      |      |      |      | head |      |      |      | tail | => EBANC      |
     *  |      |      |      |      |      |      |      |      |      | head |      |      | tail | => BANC       |
     */
    int count = 0;
    int head = 0;
    int retHead = 0;
    int retTail = 0;
    int minLen = INT_MAX;
    for (i = 0; i < sSize; ++i) {
        // update hash set by character in s
        --hashSet[(unsigned char)s[i]];

        // if character both in t and s
        if (hashSet[(unsigned char)s[i]] >= 0) {
            ++count;
        }

        while (count == tSize) {
            // update head and tail according to Minimum record
            if ((i - head + 1) < minLen) {
                minLen = i - head + 1;
                retHead = head;
                retTail = i;
            }

            // update hash set by character in s
            ++hashSet[(unsigned char)s[head]];

            // if character in s
            if (hashSet[(unsigned char)s[head]] > 0) {
                --count;
            }

            // move head
            head++;
        }
    }
    if (minLen != INT_MAX) {
        s[retTail + 1] = 0;
        pRetVal = &(s[retHead]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"a", "aa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ADOBECODEBANC", t = "ABC"
     *  Output: "BANC"
     *
     *  Input: s = "a", t = "a"
     *  Output: "a"
     *
     *  Input: s = "a", t = "aa"
     *  Output: ""
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        pAnswer = minWindow(testCase[i].s, testCase[i].t);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
