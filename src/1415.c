#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getHappyString(int n, int k) {
    char* pRetVal = NULL;

    //
    int returnSize = n + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    // Calculate the total number of happy strings of length n
    int total = 3 * (1 << (n - 1));

    // If k is greater than the total number of happy strings, return an empty string
    if (k > total) {
        return pRetVal;
    }

    // Initialize result with 'a' characters
    for (int i = 0; i < n; ++i) {
        pRetVal[i] = 'a';
    }
    //  Define mappings for the next smallest and greatest valid characters
    char nextSmallest[] = {'b', 'a', 'a'};
    char nextGreatest[] = {'c', 'c', 'b'};
    // Calculate the starting indices for strings beginning with 'a', 'b', and 'c'
    int startA = 1;
    int startB = startA + (1 << (n - 1));
    int startC = startB + (1 << (n - 1));
    // Determine the first character based on the value of k
    if (k < startB) {
        pRetVal[0] = 'a';
        k -= startA;
    } else if (k < startC) {
        pRetVal[0] = 'b';
        k -= startB;
    } else {
        pRetVal[0] = 'c';
        k -= startC;
    }

    // Iterate through the remaining positions in the result string
    for (int charIndex = 1; charIndex < n; charIndex++) {
        // Calculate the midpoint of the group for the current character position
        int midpoint = (1 << (n - charIndex - 1));
        // Determine the next character based on the value of k
        if (k < midpoint) {
            pRetVal[charIndex] = nextSmallest[pRetVal[charIndex - 1] - 'a'];
        } else {
            pRetVal[charIndex] = nextGreatest[pRetVal[charIndex - 1] - 'a'];
            k -= midpoint;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{1, 3}, {1, 4}, {3, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1, k = 3
     *  Output: "c"
     *
     *  Input: n = 1, k = 4
     *  Output: ""
     *
     *  Input: n = 3, k = 9
     *  Output: "cab"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        pAnswer = getHappyString(testCase[i].n, testCase[i].k);
        if (pAnswer != NULL) {
            printf("Output: \"%s\"\n", pAnswer);
        } else {
            printf("Output: \"\"\n");
        }

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
