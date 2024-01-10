#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bulbSwitch(int n) {
    /*      1   2   3   4   5   6   7   8   9   10
     *    +---+
     *  1 | V | V   V   V   V   V   V   V   V   V   =>  1
     *    +---+---+
     *  2 | V   X | V   X   V   X   V   X   V   X   =>  1
     *    +-------+---+
     *  3 | V   X   X | X   V   V   V   X   X   X   =>  1
     *    +-----------+---+
     *  4 | V   X   X   V | V   V   V   V   X   X   =>  2
     *    +---------------+---+
     *  5 | V   X   X   V   X | V   V   V   X   V   =>  2
     *    +-------------------+---+
     *  6 | V   X   X   V   X   X | V   V   X   V   =>  2
     *    +-----------------------+---+
     *  7 | V   X   X   V   X   X   X | V   X   V   =>  2
     *    +---------------------------+---+
     *  8 | V   X   X   V   X   X   X   X | X   V   =>  2
     *    +-------------------------------+---+
     *  9 | V   X   X   V   X   X   X   X   V | V   =>  3
     *    +-----------------------------------+---+
     * 10 | V   X   X   V   X   X   X   X   V   X | =>  3
     *    +---------------------------------------+
     */
    int retVal = sqrt(n + 0.5);

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{3}, {0}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: 1
     *
     *  Input: n = 0
     *  Output: 0
     *
     *  Input: n = 1
     *  Output: 1
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i].n);

        answer = bulbSwitch(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
