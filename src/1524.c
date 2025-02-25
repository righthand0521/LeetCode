#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)  // Since the answer can be very large, return it modulo 10^9 + 7.
int numOfSubarrays(int* arr, int arrSize) {
    int retVal = 0;

    int prefixSum = 0;
    int oddCount = 0;
    int evenCount = 1;  // evenCount starts as 1 since the initial sum (0) is even
    for (int i = 0; i < arrSize; ++i) {
        prefixSum += arr[i];
        if (prefixSum % 2 == 0) {  // If current prefix sum is even, add the number of odd subarrays
            retVal += oddCount;
            evenCount++;
        } else {  // If current prefix sum is odd, add the number of even subarrays
            retVal += evenCount;
            oddCount++;
        }

        retVal %= MODULO;  // To handle large results
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 3, 5}, 3}, {{2, 4, 6}, 3}, {{1, 2, 3, 4, 5, 6, 7}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,3,5]
     *  Output: 4
     *
     *  Input: arr = [2,4,6]
     *  Output: 0
     *
     *  Input: arr = [1,2,3,4,5,6,7]
     *  Output: 16
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = numOfSubarrays(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
