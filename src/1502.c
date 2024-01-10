#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
bool canMakeArithmeticProgression(int* arr, int arrSize) {
    bool retVal = false;

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int i;
    for (i = 2; i < arrSize; ++i) {
        if ((arr[i] - arr[i - 1]) != (arr[i - 1] - arr[i - 2])) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{3, 5, 1}, 3}, {{1, 2, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [3,5,1]
     *  Output: true
     *
     *  Input: arr = [1,2,4]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = canMakeArithmeticProgression(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
