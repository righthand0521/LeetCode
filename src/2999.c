#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long calculate(const char* x, const char* s, int limit) {
    long long retVal = 0;

    int xSize = strlen(x);
    int sSize = strlen(s);
    if (xSize < sSize) {
        return retVal;
    } else if (xSize == sSize) {
        if (strcmp(x, s) >= 0) {
            retVal = 1;
        }
        return retVal;
    }

    char* suffix = (char*)malloc(sSize + 1);
    strncpy(suffix, x + xSize - sSize, sSize);
    suffix[sSize] = '\0';

    int preLen = xSize - sSize;
    for (int i = 0; i < preLen; i++) {
        int digit = x[i] - '0';
        if (limit < digit) {
            retVal += (long long)pow(limit + 1, preLen - i);
            free(suffix);
            return retVal;
        }
        retVal += (long long)digit * (long long)pow(limit + 1, preLen - 1 - i);
    }

    if (strcmp(suffix, s) >= 0) {
        retVal++;
    }
    free(suffix);

    return retVal;
}
long long numberOfPowerfulInt(long long start, long long finish, int limit, char* s) {
    long long retVal = 0;

#define MAX_LONGLONG_STRING_SIZE (32)

    char startString[MAX_LONGLONG_STRING_SIZE];
    memset(startString, 0, sizeof(startString));
    sprintf(startString, "%lld", start - 1);

    char finishString[MAX_LONGLONG_STRING_SIZE];
    memset(finishString, 0, sizeof(finishString));
    sprintf(finishString, "%lld", finish);

    retVal = calculate(finishString, s, limit) - calculate(startString, s, limit);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        long long start;
        long long finish;
        int limit;
        char* s;
    } testCase[] = {{1, 6000, 4, "124"}, {15, 215, 6, "10"}, {1000, 2000, 4, "3000"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: start = 1, finish = 6000, limit = 4, s = "124"
     *  Output: 5
     *
     *  Input: start = 15, finish = 215, limit = 6, s = "10"
     *  Output: 2
     *
     *  Input: start = 1000, finish = 2000, limit = 4, s = "3000"
     *  Output: 0
     */

    long long answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: start = %lld, finish = %lld, limit = %d, s = \" %s \"\n", testCase[i].start, testCase[i].finish,
               testCase[i].limit, testCase[i].s);

        answer = numberOfPowerfulInt(testCase[i].start, testCase[i].finish, testCase[i].limit, testCase[i].s);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
