#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfBeams(char** bank, int bankSize) {
    int retVal = 0;

    int previous = 0;
    int count, len;
    int i, j;
    for (i = 0; i < bankSize; ++i) {
        count = 0;
        len = strlen(bank[i]);
        for (j = 0; j < len; ++j) {
            if (bank[i][j] == '1') {
                count++;
            }
        }

        if (count != 0) {
            retVal += (previous * count);
            previous = count;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char* bank[MAX_SIZE];
        int bankSize;
    } testCase[] = {{{"011001", "000000", "010100", "001000"}, 4}, {{"000", "111", "000"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: bank = ["011001","000000","010100","001000"]
     *  Output: 8
     *
     *  Input: bank = ["000","111","000"]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: bank = [");
        for (j = 0; j < testCase[i].bankSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].bank[j]);
        }
        printf("]\n");

        answer = numberOfBeams(testCase[i].bank, testCase[i].bankSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
