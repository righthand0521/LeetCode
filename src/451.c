#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void *pa, const void *pb) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;

    // descending order
    if (a[1] == b[1]) {
        return b[0] - a[0];
    } else {
        return b[1] - a[1];
    }
}
char *frequencySort(char *s) {
    char *pRetVal = s;

    int i, j;

#define HASHTABLE_SIZE (128)  // s consists of uppercase and lowercase English letters and digits.
    int **pHashTable = (int **)malloc(HASHTABLE_SIZE * sizeof(int *));
    if (pHashTable == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        pHashTable[i] = (int *)malloc(2 * sizeof(int));
        if (pHashTable[i] == NULL) {
            perror("malloc");
            goto exit;
        }
        pHashTable[i][0] = i;
        pHashTable[i][1] = 0;
    }

    int idx;
    int sSize = strlen(s);
    for (i = 0; i < sSize; ++i) {
        idx = s[i];
        ++pHashTable[idx][1];
    }
    qsort(pHashTable, HASHTABLE_SIZE, sizeof(pHashTable[0]), compareIntArray);
    idx = 0;
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        for (j = 0; j < pHashTable[i][1]; ++j) {
            s[idx++] = pHashTable[i][0];
        }
    }

exit:
    for (j = 0; j < i; ++j) {
        free(pHashTable[j]);
        pHashTable[j] = NULL;
    }
    free(pHashTable);
    pHashTable = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (5 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"tree"}, {"cccaaa"}, {"Aabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "tree"
     *  Output: "eert"
     *
     *  Input: s = "cccaaa"
     *  Output: "aaaccc"
     *
     *  Input: s = "Aabb"
     *  Output: "bbAa"
     */

    char *pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = frequencySort(testCase[i].s);
        printf("Output = \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
