#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkIfExist(int* arr, int arrSize) {
    bool retVal = false;

    /* -10^3 <= arr[i] <= 10^3
     *          arr[i]:  -1000 ...   0  ... 1000
     *  HashTable[idx]: 0~1999 ... 2000 ... 2001~4000
     */
#define HASHTABLE_IDX_SHIFT (2000)
#define HASHTABLE_MAX_SIZE (HASHTABLE_IDX_SHIFT + 1 + HASHTABLE_IDX_SHIFT)
    int HashTable[HASHTABLE_MAX_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    for (i = 0; i < arrSize; ++i) {
        if (HashTable[arr[i] * 2 + HASHTABLE_IDX_SHIFT] != 0) {
            retVal = true;
            break;
        }

        if ((arr[i] % 2 == 0) && (HashTable[arr[i] / 2 + HASHTABLE_IDX_SHIFT] != 0)) {
            retVal = true;
            break;
        }

        ++HashTable[arr[i] + HASHTABLE_IDX_SHIFT];
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{10, 2, 5, 3}, 4},
                    {{3, 1, 7, 11}, 4},
                    {{-2, 0, 10, -19, 4, 6, -8}, 7},
                    {{0, 0}, 2},
                    {{-10, 12, -20, -8, 15}, 5},
                    {{7, 1, 14, 11}, 4},
                    {{-778, -481, 842,  495, 44,  1000, -572, 977, 240, -116, 673,  997, -958, -539, -964,
                      -187, -701, -928, 472, 965, -672, -88,  443, 36,  388,  -127, 115, 704,  -549, 1000,
                      998,  291,  633,  423, 57,  -77,  -543, 72,  328, -938, -192, 382, 179},
                     43}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = [10,2,5,3]
     *  Output: true
     *
     *  Input: arr = [3,1,7,11]
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr[j]);
        }
        printf("]\n");

        answer = checkIfExist(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
