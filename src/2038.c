#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool winnerOfGame(char *colors) {
    bool retVal = false;

    int colorsSize = strlen(colors);

    int Alice = 0;
    int Bob = 0;
    int i;
    for (i = 1; i < colorsSize - 1; ++i) {
        // The number of moves available to Alice is the number of times the substring "AAA" appears.
        // The number of moves available to Bob is the number of times the substring "BBB" appears.
        if ((colors[i] == colors[i - 1]) && (colors[i] == colors[i + 1])) {
            if (colors[i] == 'A') {
                Alice++;
            } else if (colors[i] == 'B') {
                Bob++;
            }
        }
    }
    if (Alice > Bob) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char colors[MAX_SIZE];
    } testCase[] = {{"AAABABB"}, {"AA"}, {"ABBBBBBBAAA"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: colors = "AAABABB"
     *  Output: true
     *
     *  Input: colors = "AA"
     *  Output: false
     *
     *  Input: colors = "ABBBBBBBAAA"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = \"%s\"\n", testCase[i].colors);

        answer = winnerOfGame(testCase[i].colors);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
