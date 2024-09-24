#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_NODE_H
#define TREE_NODE_H

#define TRIE_WIDTH (10)  // Each node has up to 10 possible children (digits 0-9)
struct TrieNode {
    struct TrieNode* children[TRIE_WIDTH];
};
struct TrieNode* createNode() {
    struct TrieNode* pNew = (struct TrieNode*)calloc(1, sizeof(struct TrieNode));
    if (pNew == NULL) {
        perror("perror");
        return pNew;
    }

    int i;
    for (i = 0; i < TRIE_WIDTH; ++i) {
        pNew->children[i] = NULL;
    }

    return pNew;
}
void freeNode(struct TrieNode* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    int i;
    for (i = 0; i < TRIE_WIDTH; ++i) {
        freeNode(pRoot->children[i]);
    }

    free(pRoot);
}
struct TrieNode* addNode(struct TrieNode* pRoot, int num) {
    struct TrieNode* pCurrent = pRoot;

    char numStr[8 + 4];  // 1 <= arr1[i], arr2[i] <= 10^8
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int idx;
    int i;
    for (i = 0; i < numStrSize; ++i) {
        idx = numStr[i] - '0';
        if (pCurrent->children[idx] == NULL) {
            pCurrent->children[idx] = createNode();
        }
        pCurrent = pCurrent->children[idx];
    }

    return pRoot;
}
int findLongestPrefix(struct TrieNode* pRoot, int num) {
    int retVal = 0;

    struct TrieNode* pCurrent = pRoot;

    char numStr[8 + 4];  // 1 <= arr1[i], arr2[i] <= 10^8
    memset(numStr, 0, sizeof(numStr));
    snprintf(numStr, sizeof(numStr), "%d", num);
    int numStrSize = strlen(numStr);

    int idx;
    int i;
    for (i = 0; i < numStrSize; ++i) {
        idx = numStr[i] - '0';
        if (pCurrent->children[idx]) {
            // Increase length if the current digit matches
            retVal++;
            pCurrent = pCurrent->children[idx];
        } else {
            // Stop if no match for the current digit
            break;
        }
    }

    return retVal;
}

#endif  // TREE_NODE_H
int longestCommonPrefix(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int retVal = 0;

    struct TrieNode* pObj = createNode();
    if (pObj == NULL) {
        return retVal;
    }

    // Step 1: Insert all numbers from arr1 into the Trie
    for (int i = 0; i < arr1Size; ++i) {
        pObj = addNode(pObj, arr1[i]);
    }

    // Step 2: Find the longest prefix match for each number in arr2
    int len;
    for (int i = 0; i < arr2Size; ++i) {
        len = findLongestPrefix(pObj, arr2[i]);
        retVal = fmax(retVal, len);
    }

    freeNode(pObj);
    pObj = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int arr1[MAX_SIZE];
        int arr1Size;
        int arr2[MAX_SIZE];
        int arr2Size;
    } testCase[] = {{{1, 10, 100}, 3, {1000}, 1}, {{1, 2, 3}, 3, {4, 4, 4}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: arr1 = [1,10,100], arr2 = [1000]
     *  Output: 3
     *
     *  Input: arr1 = [1,2,3], arr2 = [4,4,4]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: arr1 = [");
        for (j = 0; j < testCase[i].arr1Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr1[j]);
        }
        printf("], arr2 = [");
        for (j = 0; j < testCase[i].arr2Size; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].arr2[j]);
        }
        printf("]\n");

        answer = longestCommonPrefix(testCase[i].arr1, testCase[i].arr1Size, testCase[i].arr2, testCase[i].arr2Size);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
