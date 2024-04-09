#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    int retVal = 0;

    int i;
    for (i = 0; i < ticketsSize; ++i) {
        if (i <= k) {
            retVal += fmin(tickets[i], tickets[k]);
        } else {
            retVal += fmin(tickets[i], (tickets[k] - 1));
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int tickets[MAX_SIZE];
        int ticketsSize;
        int k;
    } testCase[] = {{{2, 3, 2}, 3, 2}, {{5, 1, 1, 1}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: tickets = [2,3,2], k = 2
     *  Output: 6
     *
     *  Input: tickets = [5,1,1,1], k = 0
     *  Output: 8
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: tickets = [");
        for (j = 0; j < testCase[i].ticketsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].tickets[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = timeRequiredToBuy(testCase[i].tickets, testCase[i].ticketsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
