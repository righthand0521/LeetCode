#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (long long)(1e9 + 7)
long long quickmul(long long x, long long y) {
    long long res = 1;

    long long current = x % MODULO;
    while (y) {
        if (y & 1) {
            res = res * current % MODULO;
        }
        y >>= 1;
        current = current * current % MODULO;
    }

    return res;
}
int magicalSum(int m, int k, int* nums, int numsSize) {
    int retVal = 0;

    long long* fac = (long long*)malloc((m + 1) * sizeof(long long));
    fac[0] = 1;
    for (int i = 1; i <= m; i++) {
        fac[i] = fac[i - 1] * i % MODULO;
    }

    long long* ifac = (long long*)malloc((m + 1) * sizeof(long long));
    ifac[0] = 1;
    ifac[1] = 1;
    for (int i = 2; i <= m; i++) {
        ifac[i] = quickmul(i, MODULO - 2);
    }
    for (int i = 2; i <= m; i++) {
        ifac[i] = ifac[i - 1] * ifac[i] % MODULO;
    }

    long long** numsPower = (long long**)malloc(numsSize * sizeof(long long*));
    for (int i = 0; i < numsSize; i++) {
        numsPower[i] = (long long*)malloc((m + 1) * sizeof(long long));
        numsPower[i][0] = 1;
        for (int j = 1; j <= m; j++) {
            numsPower[i][j] = numsPower[i][j - 1] * nums[i] % MODULO;
        }
    }

    long long**** f = (long long****)malloc(numsSize * sizeof(long long***));
    for (int i = 0; i < numsSize; i++) {
        f[i] = (long long***)malloc((m + 1) * sizeof(long long**));
        for (int j = 0; j <= m; j++) {
            f[i][j] = (long long**)malloc((m * 2 + 1) * sizeof(long long*));
            for (int p = 0; p <= m * 2; p++) {
                f[i][j][p] = (long long*)calloc((k + 1), sizeof(long long));
            }
        }
    }
    for (int j = 0; j <= m; j++) {
        f[0][j][j][0] = numsPower[0][j] * ifac[j] % MODULO;
    }
    for (int i = 0; i + 1 < numsSize; i++) {
        for (int j = 0; j <= m; j++) {
            for (int p = 0; p <= m * 2; p++) {
                for (int q = 0; q <= k; q++) {
                    int q2 = p % 2 + q;
                    if (q2 > k) {
                        break;
                    }
                    for (int r = 0; r + j <= m; r++) {
                        int p2 = p / 2 + r;
                        f[i + 1][j + r][p2][q2] += f[i][j][p][q] * numsPower[i + 1][r] % MODULO * ifac[r] % MODULO;
                        f[i + 1][j + r][p2][q2] %= MODULO;
                    }
                }
            }
        }
    }

    long long res = 0;
    for (int p = 0; p <= m * 2; p++) {
        for (int q = 0; q <= k; q++) {
            int bitcount = __builtin_popcount(p);
            if (bitcount + q == k) {
                res = (res + f[numsSize - 1][m][p][q] * fac[m] % MODULO) % MODULO;
            }
        }
    }
    retVal = (int)res;

    //
    free(fac);
    free(ifac);
    for (int i = 0; i < numsSize; i++) {
        free(numsPower[i]);
    }
    free(numsPower);
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j <= m; j++) {
            for (int p = 0; p <= m * 2; p++) {
                free(f[i][j][p]);
            }
            free(f[i][j]);
        }
        free(f[i]);
    }
    free(f);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int m;
        int k;
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{5, 5, {1, 10, 100, 10000, 1000000}, 5}, {2, 2, {5, 4, 3, 2, 1}, 5}, {1, 1, {28}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
     *  Output: 991600007
     *
     *  Input: m = 2, k = 2, nums = [5,4,3,2,1]
     *  Output: 170
     *
     *  Input: m = 1, k = 1, nums = [28]
     *  Output: 28
     */

    long long answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: m = %d, k = %d, nums = [", testCase[i].m, testCase[i].k);
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = magicalSum(testCase[i].m, testCase[i].k, testCase[i].nums, testCase[i].numsSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
