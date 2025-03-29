#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
typedef struct {
    int value;
    int index;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->value;
    int pb = ((pair*)b)->value;

    // ascending order
    return (pa > pb);
}
long long powerOfModulo(long long base, long long exponent) {
    long long retVal = 1;

    // Calculate the exponentiation using binary exponentiation
    while (exponent > 0) {
        // If the exponent is odd, multiply the result by the base
        if (exponent % 2 == 1) {
            retVal = ((retVal * base) % MODULO);
        }

        // Square the base and halve the exponent
        base = (base * base) % MODULO;
        exponent /= 2;
    }

    return retVal;
}
int maximumScore(int* nums, int numsSize, int k) {
    int retVal = 0;

    // Calculate the prime score for each number in nums
    int primeScores[numsSize];
    memset(primeScores, 0, sizeof(primeScores));
    for (int index = 0; index < numsSize; index++) {
        int num = nums[index];
        // Check for prime factors from 2 to sqrt(n)
        for (int factor = 2; factor <= sqrt(num); factor++) {
            if (num % factor != 0) {
                continue;
            }
            // Increment prime score for each prime factor
            primeScores[index]++;
            // Remove all occurrences of the prime factor from num
            while (num % factor == 0) {
                num /= factor;
            }
        }
        // If num is still greater than or equal to 2, it's a prime factor
        if (num >= 2) {
            primeScores[index]++;
        }
    }

    // Initialize next and previous dominant index arrays
    int nextDominant[numsSize];
    memset(nextDominant, 0, sizeof(nextDominant));
    int prevDominant[numsSize];
    memset(prevDominant, 0, sizeof(prevDominant));
    for (int i = 0; i < numsSize; i++) {
        nextDominant[i] = numsSize;
        prevDominant[i] = -1;
    }
    // Stack to store indices for monotonic decreasing prime score
    int decreasingPrimeScoreStack[numsSize];
    int decreasingPrimeScoreStackTop = -1;
    // Calculate the next and previous dominant indices for each number
    for (int index = 0; index < numsSize; index++) {
        // While the stack is not empty and the current prime score is greater than the stack's top
        while ((decreasingPrimeScoreStackTop >= 0) &&
               (primeScores[decreasingPrimeScoreStack[decreasingPrimeScoreStackTop]] < primeScores[index])) {
            int topIndex = decreasingPrimeScoreStack[decreasingPrimeScoreStackTop];
            decreasingPrimeScoreStackTop--;
            // Set the next dominant element for the popped index
            nextDominant[topIndex] = index;
        }
        // If the stack is not empty, set the previous dominant element for the current index
        if (decreasingPrimeScoreStackTop >= 0) {
            prevDominant[index] = decreasingPrimeScoreStack[decreasingPrimeScoreStackTop];
        }
        // Push the current index onto the stack
        decreasingPrimeScoreStack[++decreasingPrimeScoreStackTop] = index;
    }

    // Calculate the number of subarrays in which each element is dominant
    long long numOfSubarrays[numsSize];
    memset(numOfSubarrays, 0, sizeof(numOfSubarrays));
    for (int index = 0; index < numsSize; index++) {
        numOfSubarrays[index] = (long long)(nextDominant[index] - index) * (index - prevDominant[index]);
    }

    // Priority queue to process elements in decreasing order of their value
    pair processingQueue[numsSize];
    memset(processingQueue, 0, sizeof(processingQueue));
    int processingQueueIndex = 0;
    // Push each number and its index onto the priority queue
    for (int index = 0; index < numsSize; index++) {
        processingQueue[index].value = nums[index];
        processingQueue[index].index = index;
        processingQueueIndex++;
    }
    qsort(processingQueue, numsSize, sizeof(pair), compareStruct);

    // Process elements while there are operations left
    long long score = 1;
    while (k > 0) {
        // Get the element with the maximum value from the queue
        processingQueueIndex--;
        long long num = processingQueue[processingQueueIndex].value;
        int index = processingQueue[processingQueueIndex].index;
        // Calculate the number of operations to apply on the current element
        long long operations = fmin((long long)k, numOfSubarrays[index]);
        // Update the score by raising the element to the power of operations
        score = (score * powerOfModulo(num, operations)) % MODULO;
        // Reduce the remaining operations count
        k -= operations;
    }
    retVal = score;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{8, 3, 9, 3, 8}, 5, 2}, {{19, 12, 14, 6, 10, 18}, 6, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [8,3,9,3,8], k = 2
     *  Output: 81
     *
     *  Input: nums = [19,12,14,6,10,18], k = 3
     *  Output: 4788
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maximumScore(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
