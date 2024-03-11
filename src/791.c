#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAL_SIZE (26)  // 1 <= order.length <= 26
int val[MAX_VAL_SIZE];
int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (val[*(char*)n1 - 'a'] < val[*(char*)n2 - 'a']);
}
char* customSortString(char* order, char* s) {
    char* pRetVal = NULL;

    memset(val, 0, sizeof(val));

    int orderSize = strlen(order);
    int idx;
    int i;
    for (i = 0; i < orderSize; ++i) {
        idx = order[i] - 'a';
        val[idx] = MAX_VAL_SIZE - i;
    }

    int sSize = strlen(s);
    qsort(s, sSize, sizeof(char), compareInteger);
    pRetVal = s;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char order[26];
        char s[MAX_SIZE];
    } testCase[] = {{"cba", "abcd"}, {"bcafg", "abcd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:  order = "cba", s = "abcd"
     *  Output:  "cbad"
     *
     *  Input:  order = "bcafg", s = "abcd"
     *  Output:  "bcad"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: order = \"%s\", s = \"%s\"\n", testCase[i].order, testCase[i].s);

        pAnswer = customSortString(testCase[i].order, testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
