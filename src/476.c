#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t findComplement(int num) {
    int i = 31;
    while ((num & (uint32_t)1 << i) == 0) {
        i--;
    }

    while (i >= 0) {
        num ^= 1 << i--;
    }

    return num;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num;
    } testCase[] = {{5}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    uint32_t answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].num);

        answer = findComplement(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
