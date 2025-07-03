#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char kthCharacter(int k) {
    char retVal;

    int ans = 0;
    while (k != 1) {
        int shift = 31 - __builtin_clz(k);
        if ((1 << shift) == k) {
            shift--;
        }
        k = k - (1 << shift);
        ans++;
    }
    retVal = 'a' + ans;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int k;
    } testCase[] = {{5}, {10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 5
     *  Output: "b"
     *
     *  Input: k = 10
     *  Output: "c"
     */

    char answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d\n", testCase[i].k);

        answer = kthCharacter(testCase[i].k);
        printf("Output: \"%c\"\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
