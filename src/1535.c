#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getWinner(int* arr, int arrSize, int k) {
    int retVal = 0;

    int winRounds = 0;
    int winIdx = 0;
    int nextIdx;
    for (nextIdx = 1; nextIdx < arrSize; ++nextIdx) {  // 2 <= arr.length <= 10^5
        if (arr[winIdx] > arr[nextIdx]) {
            winRounds += 1;
        } else if (arr[winIdx] < arr[nextIdx]) {
            winIdx = nextIdx;
            winRounds = 1;
        } else if (arr[winIdx] == arr[nextIdx]) {
            // arr contains distinct integers.
            continue;
        }

        if (winRounds == k) {
            break;
        }
    }
    retVal = arr[winIdx];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{2, 1, 3, 5, 4, 6, 7}, 7, 2},
                    {{3, 2, 1}, 3, 10},
                    {{1, 11, 22, 33, 44, 55, 66, 77, 88, 99}, 10, 1000000000},
                    {{1, 25, 35, 42, 68, 70}, 6, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,1,3,5,4,6,7], k = 2
     *  Output: 5
     *
     *  Input: arr = [3,2,1], k = 10
     *  Output: 3
     *
     *  Input: arr = [1,11,22,33,44,55,66,77,88,99], k = 1000000000
     *  Output: 99
     *
     *  Input: arr = [1,25,35,42,68,70], k = 1
     *  Output: 25
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = getWinner(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
