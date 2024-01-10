#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maximumElementAfterDecrementingAndRearranging(int* arr, int arrSize) {
    int retVal = 1;

    qsort(arr, arrSize, sizeof(int), compareInteger);

    int i;
    for (i = 1; i < arrSize; ++i) {
        if (arr[i] - retVal >= 1) {
            retVal += 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 2, 1, 2, 1}, 4},
                    {{100, 1, 1000}, 3},
                    {{1, 2, 3, 4, 5}, 5},
                    {{100, 1, 3, 3, 3, 3, 3}, 7},
                    {{73, 98, 9}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [2,2,1,2,1]
     *  Output: 2
     *
     *  Input: arr = [100,1,1000]
     *  Output: 3
     *
     *  Input: arr = [1,2,3,4,5]
     *  Output: 5
     *
     *  Input: arr = [100,1,3,3,3,3,3]
     *  Output: 4
     *
     *  Input: arr = [73,98,9]
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

        answer = maximumElementAfterDecrementingAndRearranging(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
