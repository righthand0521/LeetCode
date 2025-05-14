#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
#define LETTERSIZE (26)  // s consists only of lowercase English letters.
typedef struct {
    int a[LETTERSIZE][LETTERSIZE];
} Mat;
Mat mul(Mat x, Mat y) {
    Mat retVal;

    memset(&retVal, 0, sizeof(retVal));
    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 0; j < LETTERSIZE; j++) {
            for (int k = 0; k < LETTERSIZE; k++) {
                retVal.a[i][j] = (retVal.a[i][j] + (long long)x.a[i][k] * y.a[k][j]) % MODULO;
            }
        }
    }

    return retVal;
}
Mat quickmul(Mat x, int y) {  //  matrix exponentiation by squaring
    Mat retVal;

    // identity matrix
    memset(&retVal, 0, sizeof(retVal));
    for (int i = 0; i < LETTERSIZE; i++) {
        retVal.a[i][i] = 1;
    }

    Mat cur = x;
    while (y > 0) {
        if (y & 1) {
            retVal = mul(retVal, cur);
        }
        cur = mul(cur, cur);
        y >>= 1;
    }

    return retVal;
}
int lengthAfterTransformations(char* s, int t, int* nums, int numsSize) {
    int retVal = 0;

    Mat T;
    memset(&T, 0, sizeof(T));
    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 1; j <= nums[i]; j++) {
            T.a[(i + j) % LETTERSIZE][i] = 1;
        }
    }

    Mat res = quickmul(T, t);

    int f[LETTERSIZE];
    memset(f, 0, sizeof(f));
    for (char* p = s; *p; p++) {
        f[*p - 'a']++;
    }

    for (int i = 0; i < LETTERSIZE; i++) {
        for (int j = 0; j < LETTERSIZE; j++) {
            retVal = (retVal + (long long)res.a[i][j] * f[j]) % MODULO;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
#define MAX_NUMS_SIZE (26)
    struct testCaseType {
        char s[MAX_SIZE];
        int t;
        int nums[MAX_NUMS_SIZE];
        int numsSize;
    } testCase[] = {{"abcyy", 2, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}, 26},
                    {"azbk", 1, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 26}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcyy", t = 2, nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
     *  Output: 7
     *
     *  Input: s = "azbk", t = 1, nums = [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
     *  Output: 8
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = %d, nums = [", testCase[i].s, testCase[i].t);
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = lengthAfterTransformations(testCase[i].s, testCase[i].t, testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
