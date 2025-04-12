#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    char *key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable *pFree) {
    struct hashTable *current;
    struct hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current->key);
        free(current);
    }
}
int compareChar(const void *c1, const void *c2) {
    // ascending order
    return (*(char *)c1 > *(char *)c2);
}
long long countGoodIntegers(int n, int k) {
    long long retVal = 0;

    // Enumerate the number of palindrome numbers of n digits
    int base = (int)pow(10, (n - 1) / 2);
    int skip = n & 1;
    char s[16];
    int sSize;
    long long palindromicInteger;
    struct hashTable *pHashTable = NULL;
    struct hashTable *pTemp;
    for (int i = base; i < base * 10; i++) {
        memset(s, 0, sizeof(s));
        sprintf(s, "%d", i);
        sSize = strlen(s);
        for (int j = sSize - 1 - skip; j >= 0; j--) {
            s[sSize + (sSize - skip - 1 - j)] = s[j];
        }
        s[2 * sSize - skip] = '\0';
        palindromicInteger = atoll(s);

        // If the current palindrome number is a k-palindromic integer
        if (palindromicInteger % k == 0) {
            sSize = strlen(s);
            qsort(s, sSize, sizeof(char), compareChar);

            pTemp = NULL;
            HASH_FIND_STR(pHashTable, s, pTemp);
            if (pTemp != NULL) {
                continue;
            }
            pTemp = (struct hashTable *)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                return retVal;
            }
            pTemp->key = strdup(s);
            HASH_ADD_STR(pHashTable, key, pTemp);
        }
    }

    long long *factorial = malloc((n + 1) * sizeof(long long));
    if (factorial == NULL) {
        perror("malloc");
        freeAll(pHashTable);
        return retVal;
    }
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    pTemp = NULL;
    int cnt[10];
    long long tot;
    for (pTemp = pHashTable; pTemp; pTemp = pTemp->hh.next) {
        memset(cnt, 0, sizeof(cnt));
        for (int j = 0; pTemp->key[j] != '\0'; j++) {
            cnt[pTemp->key[j] - '0']++;
        }

        // Calculate permutations and combinations
        tot = (n - cnt[0]) * factorial[n - 1];
        for (int j = 0; j < 10; j++) {
            tot /= factorial[cnt[j]];
        }
        retVal += tot;
    }

    //
    free(factorial);
    freeAll(pHashTable);

    return retVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int k;
    } testCase[] = {{3, 5}, {1, 4}, {5, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, k = 5
     *  Output: 27
     *
     *  Input: n = 1, k = 4
     *  Output: 2
     *
     *  Input: n = 5, k = 6
     *  Output: 2468
     */

    long long answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        answer = countGoodIntegers(testCase[i].n, testCase[i].k);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
