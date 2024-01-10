#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find(int* f, int x) {
    int retVal = x;

    if (f[x] == x) {
        return retVal;
    }
    f[x] = find(f, f[x]);
    retVal = f[x];

    return retVal;
}
bool check(char* a, char* b, int len) {
    bool retVal = false;

    int num = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (a[i] == b[i]) {
            continue;
        }
        num++;
        if (num > 2) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
int numSimilarGroups(char** strs, int strsSize) {
    int retVal = 0;

    int i, j;

    int f[strsSize];
    for (int i = 0; i < strsSize; ++i) {
        f[i] = i;
    }

    int fi, fj, len;
    for (i = 0; i < strsSize; ++i) {
        for (j = i + 1; j < strsSize; ++j) {
            fi = find(f, i);
            fj = find(f, j);
            if (fi == fj) {
                continue;
            }

            len = strlen(strs[i]);
            if (check(strs[i], strs[j], len)) {
                f[fi] = fj;
            }
        }
    }

    for (i = 0; i < strsSize; ++i) {
        if (f[i] == i) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
    } testCase[] = {{{"tars", "rats", "arts", "star"}, 4}, {{"omv", "ovm"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["tars","rats","arts","star"]
     *  Output: 2
     *
     *  Input: strs = ["omv","ovm"]
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs = [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].strs[j]);
        }
        printf("]\n");

        answer = numSimilarGroups(testCase[i].strs, testCase[i].strsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
