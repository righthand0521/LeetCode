#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxDistance(int* colors, int colorsSize) {
    int retVal = 1;

    int i, j;
    for (i = 0; i < colorsSize; ++i) {
        for (j = colorsSize - 1; j > i; --j) {
            if (colors[i] != colors[j]) {
                retVal = (retVal > (j - i)) ? retVal : (j - i);
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int colors[MAX_SIZE];
        int colorsSize;
    } testCase[] = {{{1, 1, 1, 6, 1, 1, 1}, 7}, {{1, 8, 3, 8, 3}, 5}, {{0, 1}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: colors = [");
        for (j = 0; j < testCase[i].colorsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].colors[j]);
        }
        printf("]\n");

        answer = maxDistance(testCase[i].colors, testCase[i].colorsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
