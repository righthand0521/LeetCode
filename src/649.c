#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* predictPartyVictory(char* senate) {
    char* pRetVal = NULL;

#define MAX_RETURN_SIZE (8)
    pRetVal = (char*)malloc(MAX_RETURN_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_RETURN_SIZE * sizeof(char)));

    int senateSize = strlen(senate);
    int queueRadiant[senateSize];
    memset(queueRadiant, 0, sizeof(queueRadiant));
    int queueRadiantHead = 0;
    int queueRadiantTail = 0;
    int queueDire[senateSize];
    memset(queueDire, 0, sizeof(queueDire));
    int queueDireHead = 0;
    int queueDireTail = 0;

    int i;
    for (i = 0; i < senateSize; ++i) {
        if (senate[i] == 'R') {
            queueRadiant[queueRadiantHead++] = i;
        } else if (senate[i] == 'D') {
            queueDire[queueDireHead++] = i;
        }
    }

    int queueRadiantIdx, queueDireIdx;
    while ((queueRadiantHead > queueRadiantTail) && (queueDireHead > queueDireTail)) {
        queueRadiantIdx = queueRadiant[queueRadiantTail];
        queueDireIdx = queueDire[queueDireTail];

        if (queueRadiantIdx < queueDireIdx) {
            queueRadiant[queueRadiantHead++] = queueRadiantIdx + senateSize;
        } else if (queueRadiantIdx > queueDireIdx) {
            queueDire[queueDireHead++] = queueDireIdx + senateSize;
        }

        ++queueRadiantTail;
        ++queueDireTail;
    }

    if (queueRadiantHead > queueRadiantTail) {
        snprintf(pRetVal, (MAX_RETURN_SIZE * sizeof(char)), "%s", "Radiant");
    } else if (queueDireHead > queueDireTail) {
        snprintf(pRetVal, (MAX_RETURN_SIZE * sizeof(char)), "%s", "Dire");
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char senate[MAX_SIZE];
    } testCase[] = {{"RD"}, {"RDD"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: senate = "RD"
     *  Output: "Radiant"
     *
     *  Input: senate = "RDD"
     *  Output: "Dire"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: senate = \"%s\"\n", testCase[i].senate);

        pAnswer = predictPartyVictory(testCase[i].senate);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
