#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countOperations(int num1, int num2) {
    int retVal = 0;

    int tmp;
    while ((num1 != 0) && (num2 != 0)) {
        retVal += (num1 / num2);
        num1 %= num2;
        tmp = num1;
        num1 = num2;
        num2 = tmp;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int num1;
        int num2;
    } testCase[] = {{2, 3}, {10, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num1 = 2, num2 = 3
     *  Output: 3
     *
     *  Input: num1 = 10, num2 = 10
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num1 = %d, num2 = %d\n", testCase[i].num1, testCase[i].num2);

        answer = countOperations(testCase[i].num1, testCase[i].num2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
