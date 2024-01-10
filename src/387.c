#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int firstUniqChar(char* s) {
#if 1
    int retVal = -1;

// only lowercase English letters
#define MAX_SIZE 26
    int lettersCount[MAX_SIZE] = {0};
    int idx;

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        idx = *(s + i) - 'a';
        // count the number each appear letters of string s
        ++lettersCount[idx];
    }

    for (i = 0; i < len; ++i) {
        idx = *(s + i) - 'a';
        // traverse string s to check which letter first appear only once
        if (lettersCount[idx] == 1) {
            retVal = i;
            break;
        }
    }
#else
    int retVal = INT_MAX;

// only lowercase English letters
#define MAX_SIZE 26
    int HASHTABLE[MAX_SIZE] = {0};
    int idx;

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        idx = *(s + i) - 'a';
        if (HASHTABLE[idx] == -1) {
            // has been repeated
            continue;
        } else if (HASHTABLE[idx] != 0) {
            // repeating character
            HASHTABLE[idx] = -1;
        } else if (HASHTABLE[idx] == 0) {
            // first appear
            HASHTABLE[idx] = i + 1;
        }
    }

    for (i = 0; i < MAX_SIZE; ++i) {
        if ((HASHTABLE[i] == -1) || (HASHTABLE[i] == 0)) {
            continue;
        }
        // update which letters appear first
        retVal = (retVal < HASHTABLE[i]) ? retVal : HASHTABLE[i];
    }
    retVal = (retVal == INT_MAX) ? (-1) : (retVal - 1);
#endif

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"leetcode"}, {"loveleetcode"}, {"aabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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
