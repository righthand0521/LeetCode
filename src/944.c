#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDeletionSize(char** strs, int strsSize) {
    int retVal = 0;

    int len = strlen(strs[0]);
    int i, j;
    for (i = 0; i < len; ++i) {
        for (j = 1; j < strsSize; ++j) {
            if (strs[j - 1][i] > strs[j][i]) {
                ++retVal;
                break;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
    } testCase[] = {{{"cba", "daf", "ghi"}, 3}, {{"a", "b"}, 2}, {{"zyx", "wvu", "tsr"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs = [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].strs[j]);
        }
        printf("]\n");

        answer = minDeletionSize(testCase[i].strs, testCase[i].strsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
