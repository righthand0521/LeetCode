#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isUgly(int n) {
    bool retVal = false;

    if (n <= 0) {
        return retVal;
    }

    int factors[] = {2, 3, 5};
    int factorsSize = sizeof(factors) / sizeof(factors[0]);

    int i;
    for (i = 0; i < factorsSize; ++i) {
        while (n % factors[i] == 0) {
            n /= factors[i];
        }
    }

    if (n == 1) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{6}, {1}, {14}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = true;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = isUgly(testCase[i].n);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
