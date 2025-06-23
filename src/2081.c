#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
// 2 <= k <= 9, 1 <= n <= 30
static const long answer[8][30] = {
    {1,       3,       5,       7,       9,       33,      99,       313,       585,       717,
     7447,    9009,    15351,   32223,   39993,   53235,   53835,    73737,     585585,    1758571,
     1934391, 1979791, 3129213, 5071705, 5259525, 5841485, 13500531, 719848917, 910373019, 939474939},
    {1,       2,       4,       8,       121,     151,     212,     242,     484,      656,
     757,     29092,   48884,   74647,   75457,   76267,   92929,   93739,   848848,   1521251,
     2985892, 4022204, 4219124, 4251524, 4287824, 5737375, 7875787, 7949497, 27711772, 83155138},
    {1,       2,       3,       5,       55,      373,     393,      666,       787,       939,
     7997,    53235,   55255,   55655,   57675,   506605,  1801081,  2215122,   3826283,   3866683,
     5051505, 5226225, 5259525, 5297925, 5614165, 5679765, 53822835, 623010326, 954656459, 51717171715},
    {1,          2,          3,          4,          6,           88,         252,       282,
     626,        676,        1221,       15751,      18881,       10088001,   10400401,  27711772,
     30322303,   47633674,   65977956,   808656808,  831333138,   831868138,  836131638, 836181638,
     2512882152, 2596886952, 2893553982, 6761551676, 12114741121, 12185058121},
    {1,      2,      3,      4,       5,       7,       55,      111,     141,     191,
     343,    434,    777,    868,     1441,    7667,    7777,    22022,   39893,   74647,
     168861, 808808, 909909, 1867681, 3097903, 4232324, 4265624, 4298924, 4516154, 4565654},
    {1,         2,           3,           4,           5,           6,          8,         121,
     171,       242,         292,         16561,       65656,       2137312,    4602064,   6597956,
     6958596,   9470749,     61255216,    230474032,   466828664,   485494584,  638828836, 657494756,
     858474858, 25699499652, 40130703104, 45862226854, 61454945416, 64454545446},
    {1,     2,     3,      4,      5,      6,       7,       9,       121,     292,
     333,   373,   414,    585,    3663,   8778,    13131,   13331,   26462,   26662,
     30103, 30303, 207702, 628826, 660066, 1496941, 1935391, 1970791, 4198914, 55366355},
    {1,      2,       3,       4,       5,       6,       7,       8,       191,     282,
     373,    464,     555,     646,     656,     6886,    25752,   27472,   42324,   50605,
     626626, 1540451, 1713171, 1721271, 1828281, 1877781, 1885881, 2401042, 2434342, 2442442}};
#endif
bool isPalindrome(int64_t x, int k, int* digit) {
    bool retVal = true;

    int length = -1;
    while (x > 0) {
        ++length;
        digit[length] = x % k;
        x /= k;
    }

    for (int i = 0, j = length; i < j; ++i, --j) {
        if (digit[i] != digit[j]) {
            retVal = false;
            break;
        }
    }

    return retVal;
}
long long kMirror(int k, int n) {
    long long retVal = 0;

    int digit[100];
    memset(digit, 0, sizeof(digit));
    int left = 1;
    int count = 0;
    while (count < n) {
        int right = left * 10;

        // op = 0 indicates enumerating odd-length palindromes
        // op = 1 indicates enumerating even-length palindromes
        for (int op = 0; op < 2; ++op) {
            for (int i = left; i < right && count < n; ++i) {
                int64_t combined = i;

                int x = (op == 0 ? i / 10 : i);
                while (x > 0) {
                    combined = combined * 10 + x % 10;
                    x /= 10;
                }

                if (isPalindrome(combined, k, digit)) {
                    ++count;
                    retVal += combined;
                }
            }
        }

        left = right;
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int k;
        int n;
    } testCase[] = {{2, 5}, {3, 7}, {7, 17}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 2, n = 5
     *  Output: 25
     *
     *  Input: k = 3, n = 7
     *  Output: 499
     *
     *  Input: k = 7, n = 17
     *  Output: 20379000
     */

    long long answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d, n = %d\n", testCase[i].k, testCase[i].n);

        answer = kMirror(testCase[i].k, testCase[i].n);
        printf("Output: %lld\n", answer);
    }

    return EXIT_SUCCESS;
}
