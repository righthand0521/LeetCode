#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool squareIsWhite(char* coordinates) {
    bool retVal = false;

    if (strlen(coordinates) != 2) {
        return retVal;
    }

    int row = coordinates[0] - 'a';
    int col = coordinates[1] - '0';
    if (((row % 2) == 0) && ((col % 2) == 0)) {
        retVal = true;
    } else if (((row % 2) == 1) && ((col % 2) == 1)) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* coordinates;
    } testCase[] = {{"a1"}, {"h3"}, {"c7"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: coordinates = "a1"
     *  Output: false
     *
     *  Input: coordinates = "h3"
     *  Output: true
     *
     *  Input: coordinates = "c7"
     *  Output: false
     */

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: coordinates = \"%s\"\n", testCase[i].coordinates);

        answer = squareIsWhite(testCase[i].coordinates);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
