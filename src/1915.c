#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
long long wonderfulSubstrings(char* word) {
    long long retVal = 0;

    struct hashTable* pFrequency = NULL;
    struct hashTable* pTemp = NULL;

    // Create the frequency map : Key = bitmask, Value = frequency of bitmask key
    pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTemp == NULL) {
        perror("malloc");
        goto exit;
    }
    pTemp->key = 0;
    pTemp->value = 1;
    HASH_ADD_INT(pFrequency, key, pTemp);

    int bit, odd, bitmask;
    int mask = 0;
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        // a string word that consists of the first ten lowercase English letters
        bit = word[i] - 'a';

        // Flip the parity of the c-th bit in the running prefix mask
        mask ^= (1 << bit);

        // Count smaller prefixes that create substrings with no odd occurring letters
        pTemp = NULL;
        HASH_FIND_INT(pFrequency, &mask, pTemp);
        if (pTemp != NULL) {
            retVal += pTemp->value;
            pTemp->value += 1;
        } else {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                goto exit;
            }
            pTemp->key = mask;
            pTemp->value = 1;
            HASH_ADD_INT(pFrequency, key, pTemp);
        }

        // Loop through every possible letter that can appear an odd number of times in a substring
        for (odd = 0; odd < 10; ++odd) {
            bitmask = mask ^ (1 << odd);
            pTemp = NULL;
            HASH_FIND_INT(pFrequency, &bitmask, pTemp);
            if (pTemp != NULL) {
                retVal += pTemp->value;
            }
        }
    }

exit:
    freeAll(pFrequency);

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
    } testCase[] = {{"aba"}, {"aabb"}, {"he"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "aba"
     *  Output: 4
     *
     *  Input: word = "aabb"
     *  Output: 9
     *
     *  Input: word = "he"
     *  Output: 2
     */

    long long answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = wonderfulSubstrings(testCase[i].word);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
