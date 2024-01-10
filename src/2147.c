#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int numberOfWays(char* corridor) {
    int retVal = 0;

    int corridorSize = strlen(corridor);

    long answer = 1;
    int count = 0;
    int previous = -1;
    for (int i = 0; i < corridorSize; ++i) {
        if (corridor[i] == 'S') {
            count++;

            if ((count >= 3) && (count % 2 == 1)) {
                answer = (answer * (i - previous)) % MODULO;
            }

            previous = i;
        }
    }

    if ((count < 2) || (count % 2 == 1)) {
        answer = 0;
    }
    retVal = answer;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char corridor[MAX_SIZE];
    } testCase[] = {{"SSPPSPS"}, {"PPSPSP"}, {"S"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: corridor = "SSPPSPS"
     *  Output: 3
     *
     *  Input: corridor = "PPSPSP"
     *  Output: 1
     *
     *  Input: corridor = "S"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: corridor = \"%s\"\n", testCase[i].corridor);

        answer = numberOfWays(testCase[i].corridor);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
