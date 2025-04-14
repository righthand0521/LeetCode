#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countGoodTriplets(int* arr, int arrSize, int a, int b, int c) {
    int retVal = 0;

    for (int i = 0; i < arrSize; ++i) {
        for (int j = i + 1; j < arrSize; ++j) {
            for (int k = j + 1; k < arrSize; ++k) {
                if ((abs(arr[i] - arr[j]) <= a) && (abs(arr[j] - arr[k]) <= b) && (abs(arr[i] - arr[k]) <= c)) {
                    ++retVal;
                }
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int a;
        int b;
        int c;
    } testCase[] = {{{3, 0, 1, 1, 9, 7}, 6, 7, 2, 3}, {{1, 1, 2, 2, 3}, 5, 0, 0, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
     *  Output: 4
     *
     *  Input: arr = [1,1,2,2,3], a = 0, b = 0, c = 1
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], a = %d, b = %d, c = %d\n", testCase[i].a, testCase[i].b, testCase[i].c);

        answer = countGoodTriplets(testCase[i].arr, testCase[i].arrSize, testCase[i].a, testCase[i].b, testCase[i].c);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
