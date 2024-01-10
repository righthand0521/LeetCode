#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validMountainArray(int* arr, int arrSize) {
    bool retVal = false;

    if (arrSize < 3) {
        return retVal;
    }

#if 1
    int i = 0;
    while (i < (arrSize - 1)) {
        if (arr[i + 1] <= arr[i]) {
            break;
        }
        ++i;
    }
    if (i == 0) {
        return retVal;
    }

    int j = arrSize - 1;
    while (j > 0) {
        if (arr[j] >= arr[j - 1]) {
            break;
        }
        --j;
    }
    if (j == arrSize - 1) {
        return retVal;
    }

    retVal = (i == j) ? true : false;
#else
    int i;
    for (i = 1; i < arrSize; ++i) {
        if (arr[i] == arr[i - 1]) {
            return retVal;
        } else if (arr[i] < arr[i - 1]) {
            break;
        }
    }
    if ((i == arrSize) || (i == 1)) {
        return retVal;
    }

    while (i < arrSize) {
        if (arr[i] >= arr[i - 1]) {
            return retVal;
        }
        ++i;
    }
    retVal = true;
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 1}, 2},
                    {{3, 5, 5}, 3},
                    {{0, 3, 2, 1}, 4},
                    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
                    {{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10},
                    {{1, 1, 1, 1, 1, 1, 1, 2, 1}, 9}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = validMountainArray(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
