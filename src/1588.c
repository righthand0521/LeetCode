#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_BRUTE_FORCE (0)      // Time Complexity: O(n^3), Space Complexity: O(1).
#define ARRAY_TWO_LOOP (0)         // Time Complexity: O(n^2), Space Complexity: O(1).
#define MATH_INDEX_OCCURRENCE (1)  // Time Complexity: O(n), Space Complexity: O(1).
int sumOddLengthSubarrays(int* arr, int arrSize) {
    int retVal = 0;

#if (ARRAY_BRUTE_FORCE)
    printf("Approach 1: Brute Force\n");

    int sum, idx;
    int start, end;
    for (start = 0; start < arrSize; ++start) {
        for (end = start; end < arrSize; ++end) {
            if (((end - start + 1) % 2) == 0) {
                continue;
            }
            sum = 0;
            for (idx = start; idx <= end; ++idx) {
                sum += arr[idx];
            }
            retVal += sum;
        }
    }
#elif (ARRAY_TWO_LOOP)
    printf("Approach 2: Two Loops\n");

    int sum;
    int start, end;
    for (start = 0; start < arrSize; ++start) {
        sum = 0;
        for (end = start; end < arrSize; ++end) {
            sum += arr[end];
            if (((end - start + 1) % 2) == 1) {
                retVal += sum;
            }
        }
    }
#elif (MATH_INDEX_OCCURRENCE)
    printf("Approach 3: Check the occurrence of each index\n");

    int oddLeft, oddRight;
    int evenLeft, evenRight;
    int head, tail;
    int i;
    for (i = 0; i < arrSize; ++i) {
        head = i;
        tail = arrSize - i - 1;

        oddLeft = (head / 2) + 1;
        oddRight = (tail / 2) + 1;
        evenLeft = (head + 1) / 2;
        evenRight = (tail + 1) / 2;

        retVal += (arr[i] * (oddLeft * oddRight));
        retVal += (arr[i] * (evenLeft * evenRight));
    }
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 4, 2, 5, 3}, 5}, {{1, 2}, 2}, {{10, 11, 12}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = sumOddLengthSubarrays(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
