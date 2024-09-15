#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTheLongestSubstring(char* s) {
    int retVal = 0;

    int characterMap[26];  // s contains only lowercase English letters.
    memset(characterMap, 0, sizeof(characterMap));
    characterMap['a' - 'a'] = 1;
    characterMap['e' - 'a'] = 2;
    characterMap['i' - 'a'] = 4;
    characterMap['o' - 'a'] = 8;
    characterMap['u' - 'a'] = 16;
    int mp[32];  // 1 + 2 + 4 + 8 + 16 = 31 < 32
    memset(mp, -1, sizeof(mp));

    int sSize = strlen(s);
    int prefixXOR = 0;
    int i;
    for (i = 0; i < sSize; ++i) {
        prefixXOR ^= characterMap[s[i] - 'a'];
        if ((mp[prefixXOR] == -1) && (prefixXOR != 0)) {
            mp[prefixXOR] = i;
        }
        retVal = fmax(retVal, i - mp[prefixXOR]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"eleetminicoworoep"}, {"leetcodeisgreat"}, {"bcbcbc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "eleetminicoworoep"
     *  Output: 13
     *
     *  Input: s = "leetcodeisgreat"
     *  Output: 5
     *
     *  Input: s = "bcbcbc"
     *  Output: 6
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = findTheLongestSubstring(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
