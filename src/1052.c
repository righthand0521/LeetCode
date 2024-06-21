#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int minutes) {
    int retVal = 0;

    int i;

    // Calculate initial number of unrealized customers in first 'minutes' window
    int unrealizedCustomers = 0;
    for (i = 0; i < minutes; ++i) {
        unrealizedCustomers += customers[i] * grumpy[i];
    }
    int maxUnrealizedCustomers = unrealizedCustomers;

    // Slide the 'minutes' window across the rest of the customers array
    for (i = minutes; i < customersSize; ++i) {
        // Add current minute's unsatisfied customers if the owner is grumpy
        // and remove the customers that are out of the current window
        unrealizedCustomers += customers[i] * grumpy[i];
        unrealizedCustomers -= customers[i - minutes] * grumpy[i - minutes];

        // Update the maximum unrealized customers
        maxUnrealizedCustomers = fmax(maxUnrealizedCustomers, unrealizedCustomers);
    }

    // Start with maximum possible satisfied customers due to secret technique
    int totalCustomers = maxUnrealizedCustomers;

    // Add the satisfied customers during non-grumpy minutes
    for (i = 0; i < customersSize; ++i) {
        totalCustomers += customers[i] * (1 - grumpy[i]);
    }

    // Return the maximum number of satisfied customers
    retVal = totalCustomers;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int customers[MAX_SIZE];
        int customersSize;
        int grumpy[MAX_SIZE];
        int grumpySize;
        int minutes;
    } testCase[] = {{{1, 0, 1, 2, 1, 1, 7, 5}, 8, {0, 1, 0, 1, 0, 1, 0, 1}, 8, 3}, {{1}, 1, {0}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
     *  Output: 16
     *
     *  Input: customers = [1], grumpy = [0], minutes = 1
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: customers = [");
        for (j = 0; j < testCase[i].customersSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].customers[j]);
        }
        printf("], grumpy = [");
        for (j = 0; j < testCase[i].grumpySize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].grumpy[j]);
        }
        printf("], minutes = %d\n", testCase[i].minutes);

        answer = maxSatisfied(testCase[i].customers, testCase[i].customersSize, testCase[i].grumpy,
                              testCase[i].grumpySize, testCase[i].minutes);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
