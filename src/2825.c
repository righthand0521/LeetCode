#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canMakeSubsequence(char* str1, char* str2) {
    bool retVal = false;

    int str1Size = strlen(str1);
    int str2Size = strlen(str2);

    int str1Index = 0;
    int str2Index = 0;
    for (str1Index = 0; (str1Index < str1Size && str2Index < str2Size); ++str1Index) {
        if (str1[str1Index] == str2[str2Index]) {
            str2Index++;
        } else if (str1[str1Index] + 1 == str2[str2Index]) {
            str2Index++;
        } else if (str1[str1Index] - 25 == str2[str2Index]) {
            str2Index++;
        }
    }

    if (str2Index == str2Size) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char str1[MAX_SIZE];
        char str2[MAX_SIZE];
    } testCase[] = {{"abc", "ad"}, {"zc", "ad"}, {"ab", "d"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: str1 = "abc", str2 = "ad"
     *  Output: true
     *
     *  Input: str1 = "zc", str2 = "ad"
     *  Output: true
     *
     *  Input: str1 = "ab", str2 = "d"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: str1 = \"%s\", str2 = \"%s\"\n", testCase[i].str1, testCase[i].str2);

        answer = canMakeSubsequence(testCase[i].str1, testCase[i].str2);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
