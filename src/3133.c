#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long minEnd(int n, int x) {
    long long retVal = x;

    --n;  // Reducing n by 1 to exclude x from the iteration

    // Step 1: Iterate over each bit position with mask starting at 1 and shifting left
    long long mask;
    for (mask = 1; n > 0; mask <<= 1) {
        // Step 2: If the corresponding bit in x is 0
        if ((mask & x) == 0) {
            retVal |= ((n & 1) * mask);  // Set the bit in result based on the least significant bit of n
            n >>= 1;                     // Shift n to the right by 1 to process the next bit
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int x;
    } testCase[] = {{3, 4}, {2, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, x = 4
     *  Output: 6
     *
     *  Input: n = 2, x = 7
     *  Output: 15
     */

    long long answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, x = %d\n", testCase[i].n, testCase[i].x);

        answer = minEnd(testCase[i].n, testCase[i].x);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
