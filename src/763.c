#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *partitionLabels(char *s, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    pRetVal = (int *)calloc(sSize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int i;

    int last[MAX_LETTERS];
    memset(last, 0, sizeof(last));
    for (i = 0; i < sSize; ++i) {
        last[s[i] - 'a'] = i;
    }

    int start = 0;
    int end = 0;
    for (i = 0; i < sSize; ++i) {
        end = fmax(end, last[s[i] - 'a']);
        if (i == end) {
            pRetVal[(*returnSize)++] = i - start + 1;
            start = i + 1;
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char s[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"ababcbacadefegdehijhklij", 0}, {"eccbbbbdec", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "ababcbacadefegdehijhklij"
     *  Output: [9,7,8]
     *
     *  Input: s = "eccbbbbdec"
     *  Output: [10]
     */

    int *pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = partitionLabels(testCase[i].s, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
