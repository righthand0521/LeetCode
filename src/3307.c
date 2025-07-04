#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char kthCharacter(long long k, int* operations, int operationsSize) {
    char retVal;

    int ans = 0;
    k--;
    for (int i = (int)log2(k); i >= 0; i--) {
        if ((k >> i) & 1) {
            ans += operations[i];
        }
    }
    retVal = 'a' + (ans % 26);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        long long k;
        int operations[MAX_SIZE];
        int operationsSize;
    } testCase[] = {{5, {0, 0, 0}, 3}, {10, {0, 1, 0, 1}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 5, operations = [0,0,0]
     *  Output: "a"
     *
     *  Input: k = 10, operations = [0,1,0,1]
     *  Output: "b"
     */

    char answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %lld, operations = [", testCase[i].k);
        for (j = 0; j < testCase[i].operationsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].operations[j]);
        }
        printf("]\n");

        answer = kthCharacter(testCase[i].k, testCase[i].operations, testCase[i].operationsSize);
        printf("Output: %c\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
