#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSymmetricIntegers(int low, int high) {
    int retVal = 0;

    // 1 <= low <= high <= 10^4
    for (int num = low; num <= high; ++num) {
        if (num < 100) {
            if (num % 11 == 0) {
                retVal++;
            }
        } else if ((1000 <= num) && (num < 10000)) {
            int left = num / 1000 + (num % 1000) / 100;
            int right = (num % 100) / 10 + num % 10;
            if (left == right) {
                retVal++;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int low;
        int high;
    } testCase[] = {{1, 100}, {1200, 1230}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: low = 1, high = 100
     *  Output: 9
     *
     *  Input: low = 1200, high = 1230
     *  Output: 4
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: low = %d, high = %d\n", testCase[i].low, testCase[i].high);

        answer = countSymmetricIntegers(testCase[i].low, testCase[i].high);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
