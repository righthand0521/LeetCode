#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canChange(char* start, char* target) {
    bool retVal = true;

    int startSize = strlen(start);
    int startIndex = 0;
    int targetIndex = 0;
    while ((startIndex < startSize) || (targetIndex < startSize)) {
        // Skip underscores in start
        while ((startIndex < startSize) && (start[startIndex] == '_')) {
            startIndex++;
        }
        // Skip underscores in target
        while ((targetIndex < startSize) && (target[targetIndex] == '_')) {
            targetIndex++;
        }

        // If one string is exhausted, both should be exhausted
        if ((startIndex == startSize) || (targetIndex == startSize)) {
            retVal = (startIndex == startSize) && (targetIndex == startSize);
            break;
        }

        // Check if the pieces match and follow movement rules
        if (start[startIndex] != target[targetIndex]) {
            retVal = false;
            break;
        } else if ((start[startIndex] == 'L') && (startIndex < targetIndex)) {
            retVal = false;
            break;
        } else if ((start[startIndex] == 'R') && (startIndex > targetIndex)) {
            retVal = false;
            break;
        }

        startIndex++;
        targetIndex++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char start[MAX_SIZE];
        char target[MAX_SIZE];
    } testCase[] = {{"_L__R__R_", "L______RR"}, {"R_L_", "__LR"}, {"_R", "R_"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: start = "_L__R__R_", target = "L______RR"
     *  Output: true
     *
     *  Input: start = "R_L_", target = "__LR"
     *  Output: false
     *
     *  Input: start = "_R", target = "R_"
     *  Output: false
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: start = \"%s\", target = \"%s\"\n", testCase[i].start, testCase[i].target);

        answer = canChange(testCase[i].start, testCase[i].target);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
