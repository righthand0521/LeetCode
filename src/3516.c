#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findClosest(int x, int y, int z) {
    int retVal = 0;

    int diffX = abs(z - x);
    int diffY = abs(z - y);
    if (diffX < diffY) {
        retVal = 1;
    } else if (diffX > diffY) {
        retVal = 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int x;
        int y;
        int z;
    } testCase[] = {{2, 7, 4}, {2, 5, 6}, {1, 5, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: x = 2, y = 7, z = 4
     *  Output: 1
     *
     *  Input: x = 2, y = 5, z = 6
     *  Output: 2
     *
     *  Input: x = 1, y = 5, z = 3
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d, y = %d, z = %d\n", testCase[i].x, testCase[i].y, testCase[i].z);

        answer = findClosest(testCase[i].x, testCase[i].y, testCase[i].z);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
