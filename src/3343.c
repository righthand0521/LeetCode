#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
int countBalancedPermutations(char* num) {
    int retVal = 0;

    int numSize = strlen(num);

    int tot = 0;
    int cnt[10] = {0};
    for (int i = 0; i < numSize; i++) {
        int d = num[i] - '0';
        cnt[d]++;
        tot += d;
    }
    if (tot % 2 != 0) {
        return retVal;
    }

    int target = tot / 2;
    int maxOdd = (numSize + 1) / 2;

    long long comb[maxOdd + 1][maxOdd + 1];
    for (int i = 0; i <= maxOdd; i++) {
        comb[i][i] = comb[i][0] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODULO;
        }
    }

    long long dp[target + 1][maxOdd + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int psum = 0;
    int totSum = 0;
    for (int i = 0; i <= 9; i++) {
        psum += cnt[i];        // Sum of the number of the first i digits
        totSum += i * cnt[i];  // Sum of the first i numbers

        int oddCntStart = fmin(psum, maxOdd);
        int oddCntEnd = fmax(0, psum - (numSize - maxOdd));
        for (int oddCnt = oddCntStart; oddCnt >= oddCntEnd; oddCnt--) {
            int evenCnt = psum - oddCnt;  // The number of bits that need to be filled in even numbered positions

            int currStart = fmin(totSum, target);
            int currEnd = fmax(0, totSum - target);
            for (int curr = currStart; curr >= currEnd; curr--) {
                long long res = 0;

                int jStart = fmax(0, cnt[i] - evenCnt);
                int jEnd = fmin(cnt[i], oddCnt);
                for (int j = jStart; j <= jEnd && i * j <= curr; j++) {
                    // The current digit is filled with j positions at odd positions,
                    // and cnt[i] - j positions at even positions
                    long long ways = comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MODULO;
                    res = (res + ways * dp[curr - i * j][oddCnt - j] % MODULO) % MODULO;
                }
                dp[curr][oddCnt] = res % MODULO;
            }
        }
    }
    retVal = dp[target][maxOdd];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (80)
    struct testCaseType {
        char num[MAX_SIZE];
    } testCase[] = {{"123"}, {"112"}, {"12345"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: num = "123"
     *  Output: 2
     *
     *  Input: num = "112"
     *  Output: 1
     *
     *  Input: num = "12345"
     *  Output: 0
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: num = \"%s\"\n", testCase[i].num);

        answer = countBalancedPermutations(testCase[i].num);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
