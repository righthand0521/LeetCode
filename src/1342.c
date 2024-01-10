#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfSteps(int num) {
    int retVal = 0;

    while (num > 0) {
        num = ((num % 2) == 0) ? (num >> 1) : (num - 1);
        ++retVal;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{14}, {8}, {123}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = %d\n", testCase[i].num);

        answer = numberOfSteps(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
