#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pushDominoes(char* dominoes) {
    char* pRetVal = dominoes;

    char left = 'L', right;
    int dominoesSize = strlen(dominoes);
    int i = 0, j, k;
    while (i < dominoesSize) {
        j = i;
        while ((j < dominoesSize) && (pRetVal[j] == '.')) {
            j++;
        }

        right = (j < dominoesSize) ? (pRetVal[j]) : ('R');
        if (left == right) {
            while (i < j) {
                pRetVal[i++] = right;
            }
        } else if ((left == 'R') && (right == 'L')) {
            k = j - 1;
            while (i < k) {
                pRetVal[i++] = 'R';
                pRetVal[k--] = 'L';
            }
        }

        left = right;
        i = j + 1;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char dominoes[MAX_SIZE];
    } testCase[] = {{"RR.L"}, {".L.R...LR..L.."}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: dominoes = "RR.L"
     *  Output: "RR.L"
     *
     *  Input: dominoes = ".L.R...LR..L.."
     *  Output: "LL.RR.LLRRLL.."
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: dominoes = \"%s\"\n", testCase[i].dominoes);

        pAnswer = pushDominoes(testCase[i].dominoes);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
