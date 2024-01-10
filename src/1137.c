#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tribonacci(int n) {
    int retVal = 0;

#define TRIBONACCI_0 (0)
#define TRIBONACCI_1 (1)
#define TRIBONACCI_2 (1)
    if (n == 0) {
        retVal = TRIBONACCI_0;
        return retVal;
    } else if (n == 1) {
        retVal = TRIBONACCI_1;
        return retVal;
    } else if (n == 2) {
        retVal = TRIBONACCI_2;
        return retVal;
    }

#define MAX_SIZE (4)
    int TRIBONACCI[MAX_SIZE] = {TRIBONACCI_0, TRIBONACCI_1, TRIBONACCI_2, 0};
    int i;
    for (i = 3; i <= n; ++i) {
        TRIBONACCI[i % MAX_SIZE] =
            TRIBONACCI[(i - 1) % MAX_SIZE] + TRIBONACCI[(i - 2) % MAX_SIZE] + TRIBONACCI[(i - 3) % 4];
        retVal = TRIBONACCI[i % MAX_SIZE];
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{4}, {25}, {5}, {6}, {7}, {8}, {9}, {0}, {1}, {2}, {37}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4
     *  Output: 4
     *
     *  Input: n = 25
     *  Output: 1389537
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = tribonacci(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
