#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    bool retVal = false;

    int diffX = abs(fx - sx);
    int diffY = abs(fy - sy);

    if ((diffX == 0) && (diffY == 0)) {
        if (t != 1) {
            retVal = true;
        }
    } else {
        if ((t - fmin(diffX, diffY)) >= (fmax(diffX, diffY) - fmin(diffX, diffY))) {
            retVal = true;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int sx;
        int sy;
        int fx;
        int fy;
        int t;
    } testCase[] = {{2, 4, 7, 7, 6}, {3, 1, 7, 3, 3}, {1, 2, 1, 2, 1}, {1, 1, 1, 1, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
     *  Output: true
     *
     *  Input: sx = 3, sy = 1, fx = 7, fy = 3, t = 3
     *  Output: false
     *
     *  Input: sx = 1, sy = 2, fx = 1, fy = 2, t = 1
     *  Output: false
     *
     *  Input: sx = 1, sy = 1, fx = 1, fy = 1, t = 3
     *  Output: true
     */

    bool answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: sx = %d, sy = %d, fx = %d, fy = %d, t = %d\n", testCase[i].sx, testCase[i].sy, testCase[i].fx,
               testCase[i].fy, testCase[i].t);

        answer = isReachableAtTime(testCase[i].sx, testCase[i].sy, testCase[i].fx, testCase[i].fy, testCase[i].t);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
