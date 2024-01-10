#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool arrayStringsAreEqual(char** word1, int word1Size, char** word2, int word2Size) {
    bool retVal = false;

    int c1 = 0;
    int c2 = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < word1Size) && (idx2 < word2Size)) {
        // compare characters between word1 and word2
        if (word1[idx1][c1] != word2[idx2][c2]) {
            return retVal;
        }

        // word1 shift, if go to the end, change to next one.
        ++c1;
        if (word1[idx1][c1] == 0) {
            c1 = 0;
            ++idx1;
        }

        // word2 shift, if go to the end, change to next one.
        ++c2;
        if (word2[idx2][c2] == 0) {
            c2 = 0;
            ++idx2;
        }
    }

    if ((idx1 == word1Size) && (idx2 == word2Size)) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* word1[MAX_SIZE];
        int word1Size;
        char* word2[MAX_SIZE];
        int word2Size;
    } testCase[] = {
        {{"ab", "c"}, 2, {"a", "bc"}, 2}, {{"a", "cb"}, 2, {"ab", "c"}, 2}, {{"abc", "d", "defg"}, 3, {"abcddefg"}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
     *  Output: true
     *
     *  Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
     *  Output: false
     *
     *  Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
     *  Output: true
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word1 = [");
        for (j = 0; j < testCase[i].word1Size; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].word1[j]);
        }
        printf("]");
        printf(", word2 = [");
        for (j = 0; j < testCase[i].word2Size; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].word2[j]);
        }
        printf("]\n");

        answer =
            arrayStringsAreEqual(testCase[i].word1, testCase[i].word1Size, testCase[i].word2, testCase[i].word2Size);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
