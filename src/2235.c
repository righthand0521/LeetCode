#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int num1, int num2) {
    int retVal = num1 + num2;

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num1;
        int num2;
    } testCase[] = {{12, 5}, {-10, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num1 = %d, num2 = %d\n", testCase[i].num1, testCase[i].num2);

        answer = sum(testCase[i].num1, testCase[i].num2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
