#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hammingDistance(int x, int y) {
    int retVal = 0;

    int n = x ^ y;
    while (n > 0) {
        retVal += (n & 0x1);
        n >>= 1;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int x;
        int y;
    } testCase[] = {{1, 4}, {3, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d, y = %d\n", testCase[i].x, testCase[i].y);

        answer = hammingDistance(testCase[i].x, testCase[i].y);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
