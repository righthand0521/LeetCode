#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 26
int find(int* pRecord, int x) {
    if (x != pRecord[x]) {
        pRecord[x] = find(pRecord, pRecord[x]);
    }

    return pRecord[x];
}
bool equationsPossible(char** equations, int equationsSize) {
    bool retVal = false;

    int RECORD[MAX_SIZE];
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        RECORD[i] = i;
    }

    for (i = 0; i < equationsSize; ++i) {
        if (equations[i][1] == '=') {
            RECORD[find(RECORD, equations[i][0] - 'a')] = find(RECORD, equations[i][3] - 'a');
        }
    }

    for (i = 0; i < equationsSize; ++i) {
        if (equations[i][1] == '!') {
            if (find(RECORD, equations[i][0] - 'a') == find(RECORD, equations[i][3] - 'a')) {
                return retVal;
            }
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_EQUATIONSSIZE (500)
    struct testCaseType {
        char* equations[MAX_EQUATIONSSIZE];
        int equationsSize;
    } testCase[] = {{{"a==b", "b!=a"}, 2}, {{"b==a", "a==b"}, 2}, {{"a!=a"}, 1}, {{"c==c", "f!=a", "f==b", "b==c"}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: equations = [");
        for (j = 0; j < testCase[i].equationsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", testCase[i].equations[j]);
        }
        printf("]\n");

        answer = equationsPossible(testCase[i].equations, testCase[i].equationsSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
