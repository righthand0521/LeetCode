#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nextGreatestLetter(char* letters, int lettersSize, char target) {
    char retVal = letters[0];

    int i;
    for (i = 0; i < lettersSize; ++i) {
        if (letters[i] > target) {
            retVal = letters[i];
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char letters[MAX_SIZE];
        int lettersSize;
        char target;
    } testCase[] = {{{'c', 'f', 'j'}, 3, 'a'}, {{'c', 'f', 'j'}, 3, 'c'}, {{'x', 'x', 'y', 'y'}, 4, 'z'}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: letters = ["c","f","j"], target = "a"
     *  Output: "c"
     *
     *  Input: letters = ["c","f","j"], target = "c"
     *  Output: "f"
     *
     *  Input: letters = ["x","x","y","y"], target = "z"
     *  Output: "x"
     */

    char answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: letters = [");
        for (j = 0; j < testCase[i].lettersSize; ++j) {
            printf("%s\"%c\"", ((j == 0) ? "" : ","), testCase[i].letters[j]);
        }
        printf("], target = \"%c\"\n", testCase[i].target);

        answer = nextGreatestLetter(testCase[i].letters, testCase[i].lettersSize, testCase[i].target);
        printf("Output: \"%c\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
