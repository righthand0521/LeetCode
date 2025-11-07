#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(int r, long long k, long long val, long long* cnt, int stationsSize) {
    bool retVal = true;

    long long* diff = (long long*)malloc((stationsSize + 1) * sizeof(long long));
    if (diff == NULL) {
        perror("malloc");
        retVal = false;
        return retVal;
    }
    memcpy(diff, cnt, (stationsSize + 1) * sizeof(long long));

    long long sum = 0;
    long long add;
    long long remaining = k;
    int end;
    for (int i = 0; i < stationsSize; i++) {
        sum += diff[i];
        if (sum >= val) {
            continue;
        }

        add = val - sum;
        if (remaining < add) {
            retVal = false;
            break;
        }

        remaining -= add;
        end = fmin(stationsSize, i + 2 * r + 1);
        diff[end] -= add;
        sum += add;
    }

    //
    free(diff);

    return retVal;
}
long long maxPower(int* stations, int stationsSize, int r, int k) {
    long long retVal = 0;

    long long* cnt = (long long*)calloc(stationsSize + 1, sizeof(long long));
    if (cnt == NULL) {
        perror("calloc");
        return retVal;
    }
    int left, right;
    for (int i = 0; i < stationsSize; i++) {
        left = fmax(0, i - r);
        right = fmin(stationsSize, i + r + 1);
        cnt[left] += stations[i];
        cnt[right] -= stations[i];
    }

    long long minVal = LLONG_MAX;
    long long sumTotal = 0;
    for (int i = 0; i < stationsSize; i++) {
        if (stations[i] < minVal) {
            minVal = stations[i];
        }
        sumTotal += stations[i];
    }
    long long middle;
    long long high = sumTotal + k;
    long long low = minVal;
    while (low <= high) {
        middle = low + (high - low) / 2;
        if (check(r, k, middle, cnt, stationsSize) == true) {
            retVal = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    //
    free(cnt);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int stations[MAX_SIZE];
        int stationsSize;
        int r;
        int k;
    } testCase[] = {{{1, 2, 4, 5, 0}, 5, 1, 2}, {{4, 4, 4, 4}, 4, 0, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: stations = [1,2,4,5,0], r = 1, k = 2
     *  Output: 5
     *
     *  Input: stations = [4,4,4,4], r = 0, k = 3
     *  Output: 4
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: stations = [");
        for (j = 0; j < testCase[i].stationsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].stations[j]);
        }
        printf("], r = %d, k = %d\n", testCase[i].r, testCase[i].k);

        answer = maxPower(testCase[i].stations, testCase[i].stationsSize, testCase[i].r, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
