#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countOrders(int n) {
    int retVal = 0;

    // https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/solutions/516968/java-c-python-easy-and-concise/
    long combinatorics = 1;
    int i;
    for (i = 1; i <= n; ++i) {
        combinatorics = combinatorics * ((i * 2 - 1) * i) % MODULO;
    }
    retVal = combinatorics;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {2}, {3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 1
     *
     *  Input: n = 2
     *  Output: 6
     *
     *  Input: n = 3
     *  Output: 90
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = countOrders(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
