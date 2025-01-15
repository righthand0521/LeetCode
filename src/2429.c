#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isSet(int x, int bit) {
    bool retVal = x & (1 << bit);

    return retVal;
}
int setBit(int x, int bit) {
    int retVal = x | (1 << bit);

    return retVal;
}
int unsetBit(int x, int bit) {
    int retVal = x & (~(1 << bit));

    return retVal;
}
int minimizeXor(int num1, int num2) {
    int retVal = num1;

    int targetSetBitsCount = __builtin_popcount(num2);
    int setBitsCount = __builtin_popcount(retVal);
    int currentBit = 0;

    while (setBitsCount < targetSetBitsCount) {
        if (isSet(retVal, currentBit) == false) {
            retVal = setBit(retVal, currentBit);
            setBitsCount++;
        }
        currentBit++;
    }

    while (setBitsCount > targetSetBitsCount) {
        if (isSet(retVal, currentBit) == true) {
            retVal = unsetBit(retVal, currentBit);
            setBitsCount--;
        }
        currentBit++;
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int num1;
        int num2;
    } testCase[] = {{3, 5}, {1, 12}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num1 = 3, num2 = 5
     *  Output: 3
     *
     *  Input: num1 = 1, num2 = 12
     *  Output: 3
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num1 = %d, num2 = %d\n", testCase[i].num1, testCase[i].num2);

        answer = minimizeXor(testCase[i].num1, testCase[i].num2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
