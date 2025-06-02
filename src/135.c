#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int candy(int* ratings, int ratingsSize) {
    int retVal = 0;

    int left[ratingsSize];
    memset(left, 0, sizeof(left));
    for (int i = 0; i < ratingsSize; i++) {
        if ((i > 0) && (ratings[i] > ratings[i - 1])) {
            left[i] = left[i - 1] + 1;
        } else {
            left[i] = 1;
        }
    }

    int right = 0;
    for (int i = ratingsSize - 1; i >= 0; i--) {
        if ((i < ratingsSize - 1) && (ratings[i] > ratings[i + 1])) {
            right++;
        } else {
            right = 1;
        }
        retVal += fmax(left[i], right);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 10000)
    struct testCaseType {
        int ratings[MAX_SIZE];
        int ratingsSize;
    } testCase[] = {{{1, 0, 2}, 3}, {{1, 2, 2}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: ratings = [1,0,2]
     *  Output: 5
     *
     *  Input: ratings = [1,2,2]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ratings = [");
        for (j = 0; j < testCase[i].ratingsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].ratings[j]);
        }
        printf("]\n");

        answer = candy(testCase[i].ratings, testCase[i].ratingsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
