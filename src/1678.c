#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* interpret(char* command) {
    int idx = 0;
    int i = -1;
    while (command[++i]) {
        if (command[i] == 'G') {
            command[idx++] = 'G';
        } else if (command[i] == ')') {
            if (command[i - 1] == '(') {
                command[idx++] = 'o';
            } else if (command[i - 1] == 'l') {
                command[idx++] = 'a';
                command[idx++] = 'l';
            }
        }
    }
    command[idx] = 0;

    return command;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char command[MAX_SIZE];
    } testCase[] = {{"G()(al)"}, {"G()()()()(al)"}, {"(al)G(al)()()G"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: command = \"%s\"\n", testCase[i].command);

        pAnswer = interpret(testCase[i].command);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
