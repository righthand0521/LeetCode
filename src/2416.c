#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_NODE_H
#define TREE_NODE_H

#define TRIE_WIDTH (26)  // words[i] consists of lowercase English letters.
typedef struct Trie {
    struct Trie* children[TRIE_WIDTH];
    int score;
} Trie;

Trie* createTrie() {
    Trie* pRetVal = NULL;

    pRetVal = (Trie*)malloc(sizeof(Trie));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal->children, 0, sizeof(pRetVal->children));
    pRetVal->score = 0;

    return pRetVal;
}
void insert(Trie* pObj, char* word) {
    int idx;
    int wordsSize = strlen(word);
    int i;
    for (i = 0; i < wordsSize; i++) {
        idx = word[i] - 'a';
        if (pObj->children[idx] == NULL) {
            pObj->children[idx] = createTrie();
            if (pObj->children[idx] == NULL) {
                perror("malloc");
                return;
            }
        }
        pObj = pObj->children[idx];
        pObj->score++;
    }
}
void freeTrie(Trie* pObj) {
    int i;
    for (i = 0; i < TRIE_WIDTH; i++) {
        if (pObj->children[i]) {
            freeTrie(pObj->children[i]);
            pObj->children[i] = NULL;
        }
    }
    free(pObj);
    pObj = NULL;
}

#endif  // TREE_NODE_H
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumPrefixScores(char** words, int wordsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    pRetVal = (int*)malloc(wordsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (wordsSize * sizeof(int)));
    (*returnSize) = wordsSize;

    Trie* pRoot = createTrie();
    if (pRoot == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < wordsSize; i++) {
        insert(pRoot, words[i]);
    }

    int idx, wordSize;
    Trie* pCurrent = pRoot;
    for (i = 0; i < wordsSize; ++i) {
        pCurrent = pRoot;
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; j++) {
            idx = words[i][j] - 'a';
            pCurrent = pCurrent->children[idx];
            pRetVal[i] += pCurrent->score;
        }
    }

    freeTrie(pRoot);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int returnSize;
    } testCase[] = {{{"abc", "ab", "bc", "b"}, 4, 0}, {{"abcd"}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["abc","ab","bc","b"]
     *  Output: [5,4,3,2]
     *
     *  Input: words = ["abcd"]
     *  Output: [4]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        pAnswer = sumPrefixScores(testCase[i].words, testCase[i].wordsSize, &testCase[i].returnSize);
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
