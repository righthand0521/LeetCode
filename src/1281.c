#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int subtractProductAndSum(int n) {
    int retVal = 0;

    int product = 1;
    int sum = 0;
    int mod;
    while (n > 0) {
        mod = n % 10;
        product *= mod;
        sum += mod;
        n /= 10;
    }
    retVal = product - sum;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{234}, {4421}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = subtractProductAndSum(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
