#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minOperations(char** logs, int logsSize) {
    int retVal = 0;

    int i;
    for (i = 0; i < logsSize; ++i) {
        if (strcmp(logs[i], "../") == 0) {
            retVal = (retVal > 0) ? (retVal - 1) : (retVal);
        } else if (strcmp(logs[i], "./") == 0) {
            continue;
        } else {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* logs[MAX_SIZE];
        int logsSize;
    } testCase[] = {{{"d1/", "d2/", "../", "d21/", "./"}, 5},
                    {{"d1/", "d2/", "./", "d3/", "../", "d31/"}, 6},
                    {{"d1/", "../", "../", "../"}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: logs = ["d1/","d2/","../","d21/","./"]
     *  Output: 2
     *
     *  Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
     *  Output: 3
     *
     *  Input: logs = ["d1/","../","../","../"]
     *  Output: 0
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: logs = [");
        for (j = 0; j < testCase[i].logsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].logs[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].logs, testCase[i].logsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
