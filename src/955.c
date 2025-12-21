#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDeletionSize(char** strs, int strsSize) {
    int retVal = 0;

    if (strsSize <= 1) {
        return retVal;
    }

    int strSize = strlen(strs[0]);

    // # cuts[i] is True : we don't need to check col[i] <= col[i+1]
    bool cuts[strsSize - 1];
    memset(cuts, false, sizeof(cuts));

    bool needDelete;
    for (int j = 0; j < strSize; ++j) {
        needDelete = false;

        // Evaluate whether we can keep this column
        for (int i = 0; i < strsSize - 1; ++i) {
            if ((cuts[i] == false) && (strs[i][j] > strs[i + 1][j])) {
                // Can't keep the column - delete and continue
                retVal += 1;
                needDelete = true;
                break;
            }
        }
        if (needDelete == true) {
            continue;
        }

        // Update 'cuts' information
        for (int i = 0; i < strsSize - 1; ++i) {
            if (strs[i][j] < strs[i + 1][j]) {
                cuts[i] = true;
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
    } testCase[] = {{{"ca", "bb", "ac"}, 3}, {{"xc", "yb", "za"}, 3}, {{"zyx", "wvu", "tsr"}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["ca","bb","ac"]
     *  Output: 1
     *
     *  Input: strs = ["xc","yb","za"]
     *  Output: 0
     *
     *  Input: strs = ["zyx","wvu","tsr"]
     *  Output: 3
     */

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
