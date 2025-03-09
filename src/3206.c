#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfAlternatingGroups(int* colors, int colorsSize) {
    int retVal = 0;

    for (int i = 0; i < colorsSize; ++i) {
        if (colors[i] == colors[(i - 1 + colorsSize) % colorsSize]) {
            continue;
        } else if (colors[i] == colors[(i + 1) % colorsSize]) {
            continue;
        }
        retVal++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int colors[MAX_SIZE];
        int colorsSize;
    } testCase[] = {{{1, 1, 1}, 3}, {{0, 1, 0, 0, 1}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: colors = [1,1,1]
     *  Output: 0
     *
     *  Input: colors = [0,1,0,0,1]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = [");
        for (j = 0; j < testCase[i].colorsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].colors[j]);
        }
        printf("]\n");

        answer = numberOfAlternatingGroups(testCase[i].colors, testCase[i].colorsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
