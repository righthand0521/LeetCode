#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long maximumTotalDamage(int* power, int powerSize) {
    long long retVal = 0;

    qsort(power, powerSize, sizeof(int), compareInteger);

    int keys[powerSize];
    int vals[powerSize];
    int m = 0;
    for (int i = 0; i < powerSize; i++) {
        if ((m == 0) || (power[i] != keys[m - 1])) {
            keys[m] = power[i];
            vals[m] = 1;
            m++;
        } else {
            vals[m - 1]++;
        }
    }

    int vk[m + 1];
    int vv[m + 1];
    vk[0] = -1000000000;
    vv[0] = 0;
    for (int i = 0; i < m; i++) {
        vk[i + 1] = keys[i];
        vv[i + 1] = vals[i];
    }
    int n = m + 1;

    long long f[n];
    long long mx = 0;
    int j = 1;
    for (int i = 1; i < n; i++) {
        while ((j < i) && (vk[j] < vk[i] - 2)) {
            if (f[j] > mx) {
                mx = f[j];
            }
            j++;
        }

        f[i] = mx + 1LL * vk[i] * vv[i];
        if (f[i] > retVal) {
            retVal = f[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int power[MAX_SIZE];
        int powerSize;
    } testCase[] = {{{1, 1, 3, 4}, 4}, {{7, 1, 6, 6}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: power = [1,1,3,4]
     *  Output: 6
     *
     *  Input: power = [7,1,6,6]
     *  Output: 13
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: power = [");
        for (j = 0; j < testCase[i].powerSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].power[j]);
        }
        printf("]\n");

        answer = maximumTotalDamage(testCase[i].power, testCase[i].powerSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}