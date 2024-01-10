#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int process(char* srcBuf, int k, char* dstBuf) {
    int idx = 0;

    int len = strlen(srcBuf) + 1;
    int count = k;
    int sum = 0;
    int i;
    for (i = 0; *(srcBuf + i); ++i) {
        sum += ((int)(*(srcBuf + i)) - 48);
        count--;
        if (count == 0) {
            idx += snprintf(dstBuf + idx, len - idx, "%d", sum);
            count = k;
            sum = 0;
        }
    }
    if (count != k) {
        idx += snprintf(dstBuf + idx, len - idx, "%d", sum);
    }

    return idx;
}
char* digitSum(char* s, int k) {
    char* pRetVal = NULL;

    int len = strlen(s);
    if (len <= k) {
        return s;
    }
    char srcBuf[len + 1];
    memset(srcBuf, 0, sizeof(srcBuf));
    snprintf(srcBuf, sizeof(srcBuf), "%s", s);

    char dstBuf[len + 1];
    len = k + 1;
    while (len > k) {
        memset(dstBuf, 0, sizeof(dstBuf));
        len = process(srcBuf, k, dstBuf);
        memset(srcBuf, 0, sizeof(srcBuf));
        snprintf(srcBuf, sizeof(srcBuf), "%s", dstBuf);
    }

    pRetVal = (char*)malloc((len + 1) * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, len + 1);
    memcpy(pRetVal, dstBuf, len);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* s;
        int k;
    } testCase[] = {
        {"11111222223", 3},
        {"00000000", 3},
        {"1234", 2},
        {"9999999999888888888899999999998888888888999999999988888888889999999999888888888899999999998888888888", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", k = %d\n", testCase[i].s, testCase[i].k);

        pAnswer = digitSum(testCase[i].s, testCase[i].k);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
