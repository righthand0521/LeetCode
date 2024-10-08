#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwaps(char* s) {
    int retVal = 0;

    int stackSize = 0;
    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        if (s[i] == '[') {
            // If character is opening bracket, increment the stack size.
            stackSize++;
        } else if (stackSize > 0) {
            // If the character is closing bracket, and we have an opening bracket, decrease the stack size.
            stackSize--;
        }
    }
    retVal = (stackSize + 1) / 2;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e6)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"][]["}, {"]]][[["}, {"[]"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "][]["
     *  Output: 1
     *
     *  Input: s = "]]][[["
     *  Output: 2
     *
     *  Input: s = "[]"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minSwaps(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
