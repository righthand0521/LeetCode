#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumRecolors(char* blocks, int k) {
    int retVal = k;

    int blocksSize = strlen(blocks);
    int left = 0;
    int numWhites = 0;
    for (int right = 0; right < blocksSize; right++) {
        if (blocks[right] == 'W') {
            numWhites++;
        }

        if (right - left + 1 == k) {
            retVal = fmin(retVal, numWhites);

            if (blocks[left] == 'W') {
                numWhites--;
            }

            left++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char blocks[MAX_SIZE];
        int k;
    } testCase[] = {{"WBBWWBBWBW", 7}, {"WBWBBBW", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: blocks = "WBBWWBBWBW", k = 7
     *  Output: 3
     *
     *  Input: blocks = "WBWBBBW", k = 2
     *  Output: 0
     */

    int answer = 0;
    for (int i = 0; i < numberOfTestCase; ++i) {
        printf("Input: blocks = \"%s\", k = %d\n", testCase[i].blocks, testCase[i].k);

        answer = minimumRecolors(testCase[i].blocks, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
