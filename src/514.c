#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Find the minimum steps between two indexes of ring
int countSteps(int curr, int next, int ringLength) {
    int retVal = 0;

    int stepsBetween = abs(curr - next);
    int stepsAround = ringLength - stepsBetween;
    retVal = fmin(stepsBetween, stepsAround);

    return retVal;
}
int findRotateSteps(char* ring, char* key) {
    int retVal = 0;

    int ringSize = strlen(ring);
    int keySize = strlen(key);

    // For each occurrence of the character at key_index of key in ring
    // Stores minimum steps to the character from ringIndex of ring
    int curr[ringSize];
    int prev[ringSize];
    memset(prev, 0, sizeof(prev));
    int i;
    int keyIndex, ringIndex, charIndex;
    for (keyIndex = keySize - 1; keyIndex >= 0; keyIndex--) {
        memset(curr, 0, sizeof(curr));
        for (i = 0; i < ringSize; ++i) {
            curr[i] = INT_MAX;
        }
        for (ringIndex = 0; ringIndex < ringSize; ringIndex++) {
            for (charIndex = 0; charIndex < ringSize; charIndex++) {
                if (ring[charIndex] == key[keyIndex]) {
                    curr[ringIndex] =
                        fmin(curr[ringIndex], 1 + countSteps(ringIndex, charIndex, ringSize) + prev[charIndex]);
                }
            }
        }
        memset(prev, 0, sizeof(prev));
        memcpy(prev, curr, sizeof(prev));
    }
    retVal = prev[0];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char ring[MAX_SIZE];
        char key[MAX_SIZE];
    } testCase[] = {{"godding", "gd"}, {"godding", "godding"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: ring = "godding", key = "gd"
     *  Output: 4
     *
     *  Input: ring = "godding", key = "godding"
     *  Output: 13
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ring = \"%s\", key = \"%s\"\n", testCase[i].ring, testCase[i].key);

        answer = findRotateSteps(testCase[i].ring, testCase[i].key);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
