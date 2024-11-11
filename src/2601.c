#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool primeSubOperation(int* nums, int numsSize) {
    bool retVal = false;

    int i, j;

    // Store the sieve array.
    int maxElement = nums[0];
    for (i = 1; i < numsSize; ++i) {
        maxElement = fmax(maxElement, nums[i]);
    }

    int sieve[maxElement + 1];
    for (i = 0; i < maxElement + 1; ++i) {
        sieve[i] = 1;
    }

    sieve[1] = 0;
    for (i = 2; i <= sqrt(maxElement + 1); i++) {
        if (sieve[i] == 1) {
            for (j = i * i; j <= maxElement; j += i) {
                sieve[j] = 0;
            }
        }
    }

    // Start by storing the currValue as 1, and the initial index as 0.
    int currValue = 1;
    int difference;
    i = 0;
    while (i < numsSize) {
        // Store the difference needed to make nums[i] equal to currValue.
        difference = nums[i] - currValue;
        // If difference is less than 0, then nums[i] is already less than currValue. Return false in this case.
        if (difference < 0) {
            return retVal;
        }

        // If the difference is prime or zero, then nums[i] can be made equal to currValue.
        // Otherwise, try for the next currValue.
        if ((sieve[difference] == 1) || (difference == 0)) {
            i++;
            currValue++;
        } else {
            currValue++;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 9, 6, 10}, 4}, {{6, 8, 11, 12}, 4}, {{5, 8, 3}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,9,6,10]
     *  Output: true
     *
     *  Input: nums = [6,8,11,12]
     *  Output: true
     *
     *  Input: nums = [5,8,3]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = primeSubOperation(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
