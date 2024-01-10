#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minWindow(char* s, char* t) {
    char* pRetVal = "";

    int sLen = strlen(s);
    int tLen = strlen(t);

    // s and t consist of uppercase and lowercase English letters.
#define ASCII_SIZE (128)
    int asciiSet[ASCII_SIZE] = {0};

    // use hash set to record character in t
    while (*t) {
        ++asciiSet[(unsigned char)*t];
        ++t;
    }

    int count = 0;
    int head = 0;
    int retHead = 0;
    int retTail = 0;
    int minLen = INT_MAX;
    int i;
    for (i = 0; i < sLen; ++i) {
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

        // update hash set by character in s
        --asciiSet[(unsigned char)s[i]];

        // if character both in t and s
        if (asciiSet[(unsigned char)s[i]] >= 0) {
            ++count;
        }

        while (count == tLen) {
            // update head and tail according to Minimum record
            if ((i - head + 1) < minLen) {
                minLen = i - head + 1;
                retHead = head;
                retTail = i;
            }

            // update hash set by character in s
            ++asciiSet[(unsigned char)s[head]];

            // if character in s
            if (asciiSet[(unsigned char)s[head]] > 0) {
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
    struct testCaseType {
        char* s;
        char* t;
    } testCase[] = {{"ADOBECODEBANC", "ABC"}, {"a", "a"}, {"a", "aa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pInputS = NULL;
    char* pInputT = NULL;
    int mallocSize;
    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        mallocSize = (strlen(testCase[i].s) + 1) * sizeof(char);
        pInputS = (char*)malloc(mallocSize);
        if (pInputS == NULL) {
            perror("malloc");
            return EXIT_SUCCESS;
        }
        memset(pInputS, 0, mallocSize);
        memcpy(pInputS, testCase[i].s, mallocSize);
        mallocSize = (strlen(testCase[i].t) + 1) * sizeof(char);
        pInputT = (char*)malloc(mallocSize);
        if (pInputT == NULL) {
            perror("malloc");
            free(pInputS);
            pInputS = NULL;
            return EXIT_SUCCESS;
        }
        memset(pInputT, 0, mallocSize);
        memcpy(pInputT, testCase[i].t, mallocSize);
        pAnswer = minWindow(pInputS, pInputT);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
        free(pInputS);
        pInputS = NULL;
        free(pInputT);
        pInputT = NULL;
    }

    return EXIT_SUCCESS;
}
