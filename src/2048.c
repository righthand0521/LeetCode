#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/next-greater-numerically-balanced-number/solutions/1537631/next-permutation-vs-dfs/
int cnt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
long long dfs(long long n, long long val, int sz) {
    long long retVal = 0;

    if (sz == 0) {
        for (int i = 1; i <= 9; ++i) {
            if ((cnt[i] != i) && (cnt[i] != 0)) {
                return retVal;
            }
        }
        retVal = (val > n) ? (val) : (0);

        return retVal;
    }

    for (int i = 1; retVal == 0 && i <= 9; ++i)
        if ((cnt[i] > 0) && (cnt[i] <= sz)) {
            --cnt[i];
            retVal = dfs(n, val * 10 + i, sz - 1);
            ++cnt[i];
        }

    return retVal;
}
int nextBeautifulNumber(int n) {
    int retVal = 0;

    char s[8];  // 0 <= n <= 10^6
    memset(s, 0, sizeof(s));
    snprintf(s, sizeof(s), "%d", n);
    int sz = strlen(s);
    retVal = dfs(n, 0, sz);
    if (retVal == 0) {
        retVal = dfs(0, 0, sz + 1);
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
    } testCase[] = {{1}, {1000}, {3000}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 1
     *  Output: 22
     *
     *  Input: n = 1000
     *  Output: 1333
     *
     *  Input: n = 3000
     *  Output: 3133
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        answer = nextBeautifulNumber(testCase[i].n);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
