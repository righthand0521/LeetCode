#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canDistribute(int x, int* quantities, int quantitiesSize, int n) {
    bool retVal = false;

    int j = 0;
    int remaining = quantities[j];
    int i;
    for (i = 0; i < n; i++) {
        if (remaining > x) {
            remaining -= x;
            continue;
        }

        j++;
        if (j == quantitiesSize) {
            retVal = true;
            break;
        }
        remaining = quantities[j];
    }

    return retVal;
}
int minimizedMaximum(int n, int* quantities, int quantitiesSize) {
    int retVal = 0;

    int maxElement = quantities[0];
    for (int i = 1; i < quantitiesSize; ++i) {
        if (maxElement < quantities[i]) {
            maxElement = quantities[i];
        }
    }

    int middle;
    int left = 0;
    int right = maxElement;
    while (left < right) {
        middle = (left + right) / 2;
        if (canDistribute(middle, quantities, quantitiesSize, n) == true) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int quantities[MAX_SIZE];
        int quantitiesSize;
    } testCase[] = {{6, {11, 6}, 2}, {7, {15, 10, 10}, 3}, {1, {100000}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, quantities = [11,6]
     *  Output: 3
     *
     *  Input: n = 7, quantities = [15,10,10]
     *  Output: 5
     *
     *  Input: n = 1, quantities = [100000]
     *  Output: 100000
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, quantities = [", testCase[i].n);
        for (j = 0; j < testCase[i].quantitiesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].quantities[j]);
        }
        printf("]\n");

        answer = minimizedMaximum(testCase[i].n, testCase[i].quantities, testCase[i].quantitiesSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
