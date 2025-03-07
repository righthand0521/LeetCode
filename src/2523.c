#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_PRIME (1)
void sieve(int upperLimit, int* sieveArray) {
    // 0 and 1 are not prime
    sieveArray[0] = NOT_PRIME;
    sieveArray[1] = NOT_PRIME;

    for (int number = 2; number * number <= upperLimit; number++) {
        if (sieveArray[number] == NOT_PRIME) {
            continue;
        }

        // Mark all multiples of 'number' as non-prime
        for (int multiple = number * number; multiple <= upperLimit; multiple += number) {
            sieveArray[multiple] = NOT_PRIME;
        }
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestPrimes(int left, int right, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)calloc(2, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal[0] = -1;
    pRetVal[1] = -1;
    (*returnSize) = 2;

    // Step 1: Get all prime numbers up to 'right' using sieve
    int upperLimit = right;
    int* sieveArray = (int*)calloc((upperLimit + 1), sizeof(int));
    if (sieveArray == NULL) {
        perror("calloc");
        return pRetVal;
    }
    sieve(upperLimit, sieveArray);

    int primeNumbersSize = 0;
    int primeNumbers[right - left + 1];  // Store all primes in the range [left, right]
    memset(primeNumbers, 0, sizeof(primeNumbers));
    for (int num = left; num <= right; num++) {
        // If number is prime add to the primeNumbers list
        if (sieveArray[num] != NOT_PRIME) {
            primeNumbers[primeNumbersSize++] = num;
        }
    }

    // Step 2: Find the closest prime pair
    if (primeNumbersSize < 2) {
        free(sieveArray);
        sieveArray = NULL;
        return pRetVal;
    }

    int minDifference = INT_MAX;
    for (int index = 1; index < primeNumbersSize; index++) {
        int difference = primeNumbers[index] - primeNumbers[index - 1];
        if (difference < minDifference) {
            minDifference = difference;
            pRetVal[0] = primeNumbers[index - 1];
            pRetVal[1] = primeNumbers[index];
        }
    }

    //
    free(sieveArray);
    sieveArray = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int left;
        int right;
        int returnSize;
    } testCase[] = {{10, 19, 0}, {4, 6, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: left = 10, right = 19
     *  Output: [11,13]
     *
     *  Input: left = 4, right = 6
     *  Output: [-1,-1]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: left  = %d, right = %d\n", testCase[i].left, testCase[i].right);

        pAnswer = closestPrimes(testCase[i].left, testCase[i].right, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%d%s", pAnswer[j], (j == testCase[i].returnSize - 1 ? "" : ","));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
