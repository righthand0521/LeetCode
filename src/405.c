#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* toHex(int num) {
#define MAX_SIZE 9
    char* pRetVal = (char*)malloc(MAX_SIZE * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, MAX_SIZE * sizeof(char));

#if 1
    if (num == 0) {
        pRetVal[0] = '0';
        return pRetVal;
    }

    int i;
    unsigned n = num;
    while (n > 0) {
        // printf("%d: %x\n", n&0xf, n&0xf);
        for (i = (MAX_SIZE - 1); i >= 1; --i) {
            pRetVal[i] = pRetVal[i - 1];
        }
        pRetVal[0] = ((n & 0xf) < 10) ? ((n & 0xf) + 48) : ((n & 0xf) - 10 + 97);
        n >>= 4;
    }
#else
    snprintf(pRetVal, MAX_SIZE * sizeof(char), "%x", num);
    printf("%s\n", pRetVal);
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
    int testCase[] = {26, -1, 0, INT_MIN, INT_MAX};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = %d\n", testCase[i]);

        pAnswer = toHex(testCase[i]);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
