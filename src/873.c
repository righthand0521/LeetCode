#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lenLongestFibSubseq(int* arr, int arrSize) {
    int retVal = 0;

    // dp[prev][curr] stores length of Fibonacci sequence ending at indexes prev,curr
    int dp[arrSize][arrSize];
    memset(dp, 0, sizeof(dp));

    // Find all possible pairs that sum to arr[curr]
    int curr, start, end, pairSum;
    for (curr = 2; curr < arrSize; curr++) {
        // Use two pointers to find pairs that sum to arr[curr]
        start = 0;
        end = curr - 1;
        while (start < end) {
            pairSum = arr[start] + arr[end];
            if (pairSum > arr[curr]) {
                end--;
            } else if (pairSum < arr[curr]) {
                start++;
            } else {
                // Found a valid pair, update dp
                dp[end][curr] = dp[start][end] + 1;
                retVal = fmax(retVal, dp[end][curr]);
                end--;
                start++;
            }
        }
    }

    // Add 2 to include first two numbers, or return 0 if no sequence found
    if (retVal != 0) {
        retVal += 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7, 8}, 8}, {{1, 3, 7, 11, 12, 14, 18}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,3,4,5,6,7,8]
     *  Output: 5
     *
     *  Input: arr = [1,3,7,11,12,14,18]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = lenLongestFibSubseq(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
