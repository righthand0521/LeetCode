#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPrime(int num) {
    int retVal = 0;

    if (num <= 1) {
        return retVal;
    }

    if ((num > 2) && (num % 2 == 0)) {
        return retVal;
    }

    int i;
    for (i = 3; i < num / 2; i += 2) {
        if (num % i == 0) {
            return retVal;
        }
    }
    retVal = 1;

    return retVal;
}
int countBits(int n) {
    int retVal = 0;

    while (n) {
        if (n & 1) {
            retVal++;
        }
        n >>= 1;
    }

    return retVal;
}
int countPrimeSetBits(int left, int right) {
    int retVal = 0;

    int setBits;
    int i;
    for (i = left; i <= right; ++i) {
        setBits = countBits(i);
        retVal += isPrime(setBits);
    }

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int left;
        int right;
    } testCase[] = {{6, 10}, {10, 15}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: left = %d, right = %d\n", testCase[i].left, testCase[i].right);

        answer = countPrimeSetBits(testCase[i].left, testCase[i].right);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
