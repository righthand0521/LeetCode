#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canArrange(int* arr, int arrSize, int k) {
    bool retVal = false;

    int remainderCount[k];
    memset(remainderCount, 0, sizeof(remainderCount));

    int remainder;
    int i;
    for (i = 0; i < arrSize; ++i) {
        remainder = (arr[i] % k + k) % k;
        remainderCount[remainder]++;
    }

    for (i = 0; i < arrSize; ++i) {
        remainder = (arr[i] % k + k) % k;
        if (remainder == 0) {
            if (remainderCount[remainder] % 2 == 1) {
                return retVal;
            }
        } else if (remainderCount[remainder] != remainderCount[k - remainder]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{1, 2, 3, 4, 5, 10, 6, 7, 8, 9}, 10, 5}, {{1, 2, 3, 4, 5, 6}, 6, 7}, {{1, 2, 3, 4, 5, 6}, 6, 10}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
     *  Output: true
     *
     *  Input: arr = [1,2,3,4,5,6], k = 7
     *  Output: true
     *
     *  Input: arr = [1,2,3,4,5,6], k = 10
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = canArrange(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
