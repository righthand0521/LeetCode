#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passThePillow(int n, int time) {
    int retVal = 0;

    int direction = time / (n - 1);
    int index = time % (n - 1);
    if (direction % 2 == 0) {
        retVal = index + 1;
    } else if (direction % 2 == 1) {
        retVal = n - index;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int time;
    } testCase[] = {{4, 5}, {3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, time = 5
     *  Output: 2
     *
     *  Input: n = 3, time = 2
     *  Output: 3
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, time = %d\n", testCase[i].n, testCase[i].time);

        answer = passThePillow(testCase[i].n, testCase[i].time);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
