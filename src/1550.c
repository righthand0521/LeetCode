#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool threeConsecutiveOdds(int* arr, int arrSize) {
    bool retVal = false;

    int consecutiveOdds = 0;
    int i;
    for (i = 0; i < arrSize; ++i) {
        if (arr[i] % 2 == 0) {
            consecutiveOdds = 0;
        } else {
            consecutiveOdds += 1;
            if (consecutiveOdds == 3) {
                retVal = true;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 6, 4, 1}, 4}, {{1, 2, 34, 3, 4, 5, 7, 23, 12}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,6,4,1]
     *  Output: false
     *
     *  Input: arr = [1,2,34,3,4,5,7,23,12]
     *  Output: true
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("]\n");

        answer = threeConsecutiveOdds(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
