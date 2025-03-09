#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfAlternatingGroups(int* colors, int colorsSize, int k) {
    int retVal = 0;

    int index;
    int alternatingElementsCount = 1;
    int lastColor = colors[0];
    for (int i = 1; i < colorsSize + k - 1; i++) {
        index = i % colorsSize;

        // Check if current color is the same as last color
        if (colors[index] == lastColor) {
            // Pattern breaks, reset sequence length
            alternatingElementsCount = 1;
            lastColor = colors[index];
            continue;
        }

        // Extend alternating sequence
        alternatingElementsCount += 1;

        // If sequence length reaches at least k, count it
        if (alternatingElementsCount >= k) {
            retVal++;
        }

        lastColor = colors[index];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int colors[MAX_SIZE];
        int colorsSize;
        int k;
    } testCase[] = {{{0, 1, 0, 1, 0}, 5, 3}, {{0, 1, 0, 0, 1, 0, 1}, 7, 6}, {{1, 1, 0, 1}, 4, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: colors = [0,1,0,1,0], k = 3
     *  Output: 3
     *
     *  Input: colors = [0,1,0,0,1,0,1], k = 6
     *  Output: 2
     *
     *  Input: colors = [1,1,0,1], k = 4
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = [");
        for (j = 0; j < testCase[i].colorsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].colors[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = numberOfAlternatingGroups(testCase[i].colors, testCase[i].colorsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
