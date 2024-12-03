#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* addSpaces(char* s, int* spaces, int spacesSize) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + spacesSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    int spacesIdx = 0;
    int sIdx;
    for (sIdx = 0; sIdx < sSize; ++sIdx) {
        if ((spacesIdx < spacesSize) && (sIdx == spaces[spacesIdx])) {
            *(pRetVal + sIdx + spacesIdx) = ' ';
            spacesIdx++;
        }
        *(pRetVal + sIdx + spacesIdx) = s[sIdx];
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_STRING (3 * 100000)
#define MAX_SPACE (3 * 100000)
    struct testCaseType {
        char s[MAX_STRING];
        int spaces[MAX_SPACE];
        int spacesSize;
    } testCase[] = {{"LeetcodeHelpsMeLearn", {8, 13, 15}, 3},
                    {"icodeinpython", {1, 5, 7, 9}, 4},
                    {"spacing", {0, 1, 2, 3, 4, 5, 6}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
     *  Output: "Leetcode Helps Me Learn"
     *
     *  Input: s = "icodeinpython", spaces = [1,5,7,9]
     *  Output: "i code in py thon"
     *
     *  Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
     *  Output: " s p a c i n g"
     */

    char* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", spaces = [", testCase[i].s);
        for (j = 0; j < testCase[i].spacesSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].spaces[j]);
        }
        printf("]\n");

        pAnswer = addSpaces(testCase[i].s, testCase[i].spaces, testCase[i].spacesSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}