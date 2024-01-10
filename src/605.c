#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
    bool retVal = false;

    int i;
    for (i = 0; i < flowerbedSize; ++i) {
        if (flowerbed[i] == 1) {
            continue;
        }

        if (i == 0) {
            if ((flowerbedSize == 1) || (flowerbed[i + 1] == 0)) {
                --n;
                flowerbed[i] = 1;
            }
        } else if (i == flowerbedSize - 1) {
            if (flowerbed[i - 1] == 0) {
                --n;
                flowerbed[i] = 1;
            }
        } else {
            if ((flowerbed[i - 1] == 0) && (flowerbed[i + 1] == 0)) {
                --n;
                flowerbed[i] = 1;
            }
        }
    }
    if (n <= 0) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (20000)
    struct testCaseType {
        int flowerbed[MAX_SIZE];
        int flowerbedSize;
        int n;
    } testCase[] = {
        {{1, 0, 0, 0, 1}, 5, 1}, {{1, 0, 0, 0, 1}, 5, 2}, {{0}, 1, 0}, {{0}, 1, 1}, {{1}, 1, 0}, {{1}, 1, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: flowerbed = [1,0,0,0,1], n = 1
     *  Output: true
     *
     *  Input: flowerbed = [1,0,0,0,1], n = 2
     *  Output: false
     *
     *  Input: flowerbed = [0], n = 0
     *  Output: true
     *
     *  Input: flowerbed = [0], n = 1
     *  Output: true
     *
     *  Input: flowerbed = [1], n = 0
     *  Output: true
     *
     *  Input: flowerbed = [1], n = 1
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: flowerbed = [");
        for (j = 0; j < testCase[i].flowerbedSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].flowerbed[j]);
        }
        printf("], n = %d\n", testCase[i].n);

        answer = canPlaceFlowers(testCase[i].flowerbed, testCase[i].flowerbedSize, testCase[i].n);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
