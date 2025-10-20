#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int finalValueAfterOperations(char** operations, int operationsSize) {
    int retVal = 0;

    for (int i = 0; i < operationsSize; i++) {
        // operations[i] will be either "++X", "X++", "--X", or "X--"
        if ((strcmp(operations[i], "++X") == 0) || (strcmp(operations[i], "X++") == 0)) {
            retVal++;
        } else {
            retVal--;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* operations[MAX_SIZE];
        int operationsSize;
    } testCase[] = {{{"--X", "X++", "X++"}, 3}, {{"++X", "++X", "X++"}, 3}, {{"X++", "++X", "--X", "X--"}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: operations = ["--X","X++","X++"]
     *  Output: 1
     *
     *  Input: operations = ["++X","++X","X++"]
     *  Output: 3
     *
     *  Input: operations = ["X++","++X","--X","X--"]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: operations = [");
        for (j = 0; j < testCase[i].operationsSize; ++j) {
            printf("\"%s\"%s", testCase[i].operations[j], (j == (testCase[i].operationsSize - 1) ? "" : ","));
        }
        printf("]\n");

        answer = finalValueAfterOperations(testCase[i].operations, testCase[i].operationsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
