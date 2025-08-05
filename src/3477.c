#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int retVal = 0;

    int unset;
    for (int i = 0; i < fruitsSize; ++i) {
        unset = 1;
        for (int j = 0; j < basketsSize; ++j) {
            if (fruits[i] <= baskets[j]) {
                baskets[j] = 0;
                unset = 0;
                break;
            }
        }
        retVal += unset;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int fruits[MAX_SIZE];
        int fruitsSize;
        int baskets[MAX_SIZE];
        int basketsSize;
    } testCase[] = {{{4, 2, 5}, 3, {3, 5, 4}, 3}, {{3, 6, 1}, 3, {6, 4, 7}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: fruits = [4,2,5], baskets = [3,5,4]
     *  Output: 1
     *
     *  Input: fruits = [3,6,1], baskets = [6,4,7]
     *  Output: 0
     */

    int i, j;
    int answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: fruits = [");
        for (j = 0; j < testCase[i].fruitsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].fruits[j]);
        }
        printf("], baskets = [");
        for (j = 0; j < testCase[i].basketsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].baskets[j]);
        }
        printf("]\n");

        answer = numOfUnplacedFruits(testCase[i].fruits, testCase[i].fruitsSize, testCase[i].baskets,
                                     testCase[i].basketsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
