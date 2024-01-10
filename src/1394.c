#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findLucky(int* arr, int arrSize) {
    int retVal = -1;

#define MAX_HASH_SIZE (500 + 1)
    int HashTable[MAX_HASH_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    for (i = 0; i < arrSize; ++i) {
        ++HashTable[arr[i]];
    }

    for (i = (MAX_HASH_SIZE - 1); i > 0; --i) {
        if (i == HashTable[i]) {
            retVal = i;
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{2, 2, 3, 4}, 4}, {{1, 2, 2, 3, 3, 3}, 6}, {{2, 2, 2, 3, 3}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = findLucky(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
