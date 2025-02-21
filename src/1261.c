#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
void dfs(struct TreeNode* currentNode, int currentValue, struct hashTable** seen) {
    if (currentNode == NULL) {
        return;
    }

    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(*seen, &currentValue, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            return;
        }
        pTemp->key = currentValue;
        HASH_ADD_INT(*seen, key, pTemp);
    }
    dfs(currentNode->left, currentValue * 2 + 1, seen);
    dfs(currentNode->right, currentValue * 2 + 2, seen);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct {
    struct hashTable* seen;
} FindElements;
FindElements* findElementsCreate(struct TreeNode* root) {
    FindElements* pRetVal = NULL;

    pRetVal = (FindElements*)malloc(sizeof(FindElements));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->seen = NULL;
    dfs(root, 0, &pRetVal->seen);

    return pRetVal;
}
bool findElementsFind(FindElements* obj, int target) {
    bool retVal = false;

    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(obj->seen, &target, pTemp);
    if (pTemp != NULL) {
        retVal = true;
    }

    return retVal;
}
void findElementsFree(FindElements* obj) {
    freeAll(obj->seen);
    free(obj);
}
/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);
 * findElementsFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int val[MAX_SIZE][MAX_SIZE];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"FindElements", "find", "find"}, {{-1, INT_MIN, -1}, {1}, {2}}, {3, 1, 1}, 3},
                    {{"FindElements", "find", "find", "find"}, {{-1, -1, -1, -1, -1}, {1}, {3}, {5}}, {5, 1, 1, 1}, 4},
                    {{"FindElements", "find", "find", "find", "find"},
                     {{-1, INT_MIN, -1, -1, INT_MIN, -1}, {2}, {3}, {4}, {5}},
                     {6, 1, 1, 1, 1},
                     5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["FindElements","find","find"]
     *  [[[-1,null,-1]],[1],[2]]
     *  Output
     *  [null,false,true]
     *
     *  Input
     *  ["FindElements","find","find","find"]
     *  [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
     *  Output
     *  [null,true,true,false]
     *
     *  Input
     *  ["FindElements","find","find","find","find"]
     *  [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
     *  Output
     *  [null,true,false,false,true]
     */

    FindElements* pFindElements = NULL;
    struct TreeNode* pRoot = NULL;
    bool retBoolValue;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("\"%s\"%s", testCase[i].methods[j], (j == (testCase[i].calls - 1) ? "" : ","));
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            if (strcmp(testCase[i].methods[j], "FindElements") == 0) {
                printf("[");
                for (k = 0; k < testCase[i].valSize[j]; ++k) {
                    if (testCase[i].val[j][k] == INT_MIN) {
                        printf("%snull", (k == 0 ? "" : ","));
                    } else if (testCase[i].val[j][k] == INT_MAX) {
                        continue;
                    } else {
                        printf("%s%d", (k == 0 ? "" : ","), testCase[i].val[j][k]);
                    }
                }
                printf("]");
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            if (strcmp(testCase[i].methods[j], "FindElements") == 0) {
                pRoot = buildBinaryTree(testCase[i].val[j], testCase[i].valSize[j], 0);
                pFindElements = findElementsCreate(pRoot);
                printf("%s%s", "null", (j == (testCase[i].calls - 1) ? "" : ","));
            } else if (strcmp(testCase[i].methods[j], "find") == 0) {
                retBoolValue = findElementsFind(pFindElements, testCase[i].val[j][0]);
                printf("%s%s", (retBoolValue == true ? "true" : "false"), (j == (testCase[i].calls - 1) ? "" : ","));
            }
        }
        printf("]\n");
        findElementsFree(pFindElements);
        pFindElements = NULL;
        freeTreeNode(pRoot);
        pRoot = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
