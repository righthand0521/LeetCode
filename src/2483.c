#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bestClosingTime(char *customers) {
    int retVal = 0;

    /* At any index, the penalty is the sum of prefix count of 'N' and suffix count of 'Y'.
     *  Y Y N Y     N N N N N     Y Y Y Y
     *  3 2 1 1 0   0 0 0 0 0 0   4 3 2 1 0
     *  0 0 0 1 1   0 1 2 3 4 5   0 0 0 0 0
     */
    int customersSize = strlen(customers);
    int penalty = 0;
    int i;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            ++penalty;
        }
    }
    int minPenalty = penalty;
    for (i = 0; i < customersSize; ++i) {
        if (customers[i] == 'Y') {
            --penalty;
        } else if (customers[i] == 'N') {
            ++penalty;
        }

        if (minPenalty > penalty) {
            minPenalty = penalty;
            retVal = i + 1;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char customers[MAX_SIZE];
    } testCase[] = {{"YYNY"}, {"NNNNN"}, {"YYYY"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: customers = "YYNY"
     *  Output: 2
     *
     *  Input: customers = "NNNNN"
     *  Output: 0
     *
     *  Input: customers = "YYYY"
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: customers = \"%s\"\n", testCase[i].customers);

        answer = bestClosingTime(testCase[i].customers);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
