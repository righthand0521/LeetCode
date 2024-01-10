#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
char *smallestSubsequence(char *s) {
    char *pRetVal = NULL;

    //
    pRetVal = (char *)malloc((MAX_LETTERS + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloe");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_LETTERS + 1) * sizeof(char)));
    int returnSize = 0;

    //
    int sSize = strlen(s);
    int i;
    int appears[MAX_LETTERS];
    memset(appears, 0, sizeof(appears));
    for (i = 0; i < sSize; ++i) {
        appears[s[i] - 'a']++;
    }
    int visit[MAX_LETTERS];
    memset(visit, 0, sizeof(visit));

    //
    int idx;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';

        if (visit[idx] == 0) {
            while ((returnSize > 0) && (pRetVal[returnSize - 1] > s[i])) {
                if (appears[pRetVal[returnSize - 1] - 'a'] > 0) {
                    visit[pRetVal[returnSize - 1] - 'a'] = 0;
                    returnSize -= 1;
                } else {
                    break;
                }
            }
            visit[idx] = 1;
            pRetVal[returnSize] = s[i];
            returnSize += 1;
        }
        appears[idx] -= 1;
    }
    pRetVal[returnSize] = '\0';

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"bcabc"}, {"cbacdcbc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "bcabc"
     *  Output: "abc"
     *
     *  Input: s = "cbacdcbc"
     *  Output: "acdb"
     */

    char *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = smallestSubsequence(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
