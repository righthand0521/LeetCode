#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(unsigned int* pMasks, int start, int end, unsigned int mask, int* pMaxLength) {
    int i;
    for (i = start; i < end; ++i) {
        if ((mask & pMasks[i]) == 0) {
            backtracking(pMasks, i + 1, end, (mask | pMasks[i]), pMaxLength);
        }
    }

    int count = 0;
    while (mask) {
        count += (mask & 1);
        mask >>= 1;
    }
    (*pMaxLength) = ((*pMaxLength) > count) ? (*pMaxLength) : count;
}
int maxLength(char** arr, int arrSize) {
    int retVal = 0;

    unsigned int masks[arrSize];
    memset(masks, 0, sizeof(masks));
    unsigned int mask;
    int i;
    for (i = 0; i < arrSize; ++i) {
        while (*arr[i]) {
            mask = (1 << (*arr[i] - 'a'));
            if ((masks[i] & mask) != 0) {
                masks[i] = 0;
                break;
            }
            masks[i] |= mask;

            arr[i]++;
        }
    }
    backtracking(masks, 0, arrSize, 0, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        char* arr[MAX_SIZE];
        int arrSize;
    } testCase[] = {{{"un", "iq", "ue"}, 3},
                    {{"cha", "r", "act", "ers"}, 4},
                    {{"abcdefghijklmnopqrstuvwxyz"}, 1},
                    {{"a", "abc", "d", "de", "def"}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr = ["un","iq","ue"]
     *  Output: 4
     *
     *  Input: arr = ["cha","r","act","ers"]
     *  Output: 6
     *
     *  Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
     *  Output: 26
     *
     *  Input: arr = ["a", "abc", "d", "de", "def"]
     *  Output: 6
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr = [");
        for (j = 0; j < testCase[i].arrSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].arr[j]);
        }
        printf("]\n");

        answer = maxLength(testCase[i].arr, testCase[i].arrSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
