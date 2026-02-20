#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qsort_compareString(const void* str1, const void* str2) {
    // descending order
    return strcmp(*(char**)str2, *(char**)str1);
}
char* helper(char* s, int start, int end) {
    char* pRetVal = NULL;

    int len = end - start + 1;
    if (len <= 2) {
        pRetVal = (char*)malloc((len + 1) * sizeof(char));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        memset(pRetVal, 0, (len + 1) * sizeof(char));
        strncpy(pRetVal, s + start, len);
        pRetVal[len] = '\0';

        return pRetVal;
    }

    int cnt = 0;
    int left = start;
    char** subs = (char**)malloc(len * sizeof(char*));
    int subsSize = 0;
    char* helpReturn = NULL;
    int helpReturnSize = 0;
    for (int i = start; i <= end; ++i) {
        if (s[i] == '1') {
            ++cnt;
            continue;
        }

        --cnt;
        if (cnt != 0) {
            continue;
        }

        helpReturn = helper(s, left + 1, i - 1);
        if (helpReturn == NULL) {
            for (int j = 0; j < subsSize; ++j) {
                free(subs[j]);
                subs[j] = NULL;
            }
            free(subs);
            subs = NULL;
            return pRetVal;
        }
        helpReturnSize = strlen(helpReturn);

        subs[subsSize] = (char*)malloc(sizeof(char) * (helpReturnSize + 3));
        sprintf(subs[subsSize], "%s%s%s", "1", helpReturn, "0");
        free(helpReturn);
        helpReturn = NULL;
        left = i + 1;
        subsSize++;
    }
    qsort(subs, subsSize, sizeof(char*), qsort_compareString);

    pRetVal = (char*)malloc((len + 1) * sizeof(char));
    int pos = 0;
    for (int i = 0; i < subsSize; i++) {
        pos += sprintf(pRetVal + pos, "%s", subs[i]);
        free(subs[i]);
        subs[i] = NULL;
    }
    pRetVal[pos] = '\0';

    //
    free(subs);
    subs = NULL;

    return pRetVal;
}
char* makeLargestSpecial(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    pRetVal = helper(s, 0, sSize - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
    } testCase[] = {{"11011000"}, {"10"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "11011000"
     *  Output: "11100100"
     *
     *  Input: s = "10"
     *  Output: "10"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = makeLargestSpecial(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
