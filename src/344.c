#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* s, int sSize) {
    char tmp;
    int idx;
    for (idx = 0; idx < sSize / 2; ++idx) {
        tmp = s[idx];
        s[idx] = s[sSize - idx - 1];
        s[sSize - idx - 1] = tmp;
    }
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int sSize;
    } testCase[] = {{"hello", 5}, {"Hannah", 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = ["h","e","l","l","o"]
     *  Output: ["o","l","l","e","h"]
     *
     *  Input: s = ["H","a","n","n","a","h"]
     *  Output: ["h","a","n","n","a","H"]
     */

    char* pInput = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = [");
        for (j = 0; j < testCase[i].sSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", testCase[i].s[j]);
        }
        printf("]\n");

        pInput = (char*)malloc(testCase[i].sSize * sizeof(char));
        memset(pInput, 0, testCase[i].sSize * sizeof(char));
        memcpy(pInput, testCase[i].s, testCase[i].sSize * sizeof(char));
        reverseString(pInput, testCase[i].sSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].sSize; ++j) {
            printf("%s\"%c\"", (j == 0) ? "" : ",", pInput[j]);
        }
        printf("]\n");

        printf("\n");

        free(pInput);
        pInput = NULL;
    }

    return EXIT_SUCCESS;
}
