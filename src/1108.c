#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* defangIPaddr(char* address) {
    char* pRetVal = NULL;

    int len = strlen(address);
    int returnSize = len + 3 * 2 + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, returnSize * sizeof(char));

#if (1)
    printf("for\n");

    int idx = 0;
    int i;
    for (i = 0; i < len; ++i) {
        if (address[i] == '.') {
            pRetVal[idx++] = '[';
            pRetVal[idx++] = '.';
            pRetVal[idx++] = ']';
        } else {
            pRetVal[idx++] = address[i];
        }
    }
#else
    printf("sscanf\n");

    int ip1, ip2, ip3, ip4;
    sscanf(address, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);
    snprintf(pRetVal, returnSize * sizeof(char), "%d[.]%d[.]%d[.]%d", ip1, ip2, ip3, ip4);
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (64)
    struct testCaseType {
        char address[MAX_SIZE];
    } testCase[] = {{"1.1.1.1"}, {"255.100.50.0"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: address = "1.1.1.1"
     *  Output: "1[.]1[.]1[.]1"
     *
     *  Input: address = "255.100.50.0"
     *  Output: "255[.]100[.]50[.]0"
     */

    char* pAnswer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: address=\"%s\"\n", testCase[i].address);

        pAnswer = defangIPaddr(testCase[i].address);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
