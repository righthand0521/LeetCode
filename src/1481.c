#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    int times;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->times;
    int pb = ((pair*)b)->times;

    // ascending order
    return (pa > pb);
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findLeastNumOfUniqueInts(int* arr, int arrSize, int k) {
    int retVal = 0;

    int i;

    qsort(arr, arrSize, sizeof(int), compareInteger);
    int previous = arr[0];
    int occurrencesSize = 1;
    for (i = 1; i < arrSize; ++i) {
        if (previous != arr[i]) {
            previous = arr[i];
            occurrencesSize++;
        }
    }

    pair occurrences[occurrencesSize];
    memset(occurrences, 0, sizeof(occurrences));
    occurrencesSize = 0;
    occurrences[occurrencesSize].number = arr[0];
    occurrences[occurrencesSize].times += 1;
    for (i = 1; i < arrSize; ++i) {
        if (occurrences[occurrencesSize].number != arr[i]) {
            occurrencesSize++;
            occurrences[occurrencesSize].number = arr[i];
        }
        occurrences[occurrencesSize].times += 1;
    }
    occurrencesSize++;
    qsort(occurrences, occurrencesSize, sizeof(pair), compareStruct);

    for (i = 0; i < occurrencesSize; ++i) {
        k -= occurrences[i].times;
        if (k < 0) {
            retVal++;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
        int k;
    } testCase[] = {{{5, 5, 4}, 3, 1}, {{4, 3, 1, 1, 3, 3, 2}, 7, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [5,5,4], k = 1
     *  Output: 1
     *
     *  Input: arr = [4,3,1,1,3,3,2], k = 3
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = findLeastNumOfUniqueInts(testCase[i].arr, testCase[i].arrSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
