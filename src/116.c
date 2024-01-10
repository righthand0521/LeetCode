#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeNode.h"

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */
void dfs(struct Node* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    /* Example
     *                                          (01)
     *
     *                    (02) ------------------01-----------------> (03)
     *
     *         (04) -------04------> (05) -------02------> (06) -------08------> (07)
     *
     *    (08) -06-> (09) -05-> (10) -07-> (11) -03-> (12) -10-> (13) -09-> (14) -11-> (15)
     */
    struct Node* pLeft = pRoot->left;
    struct Node* pRight = pRoot->right;
    while (pLeft != NULL) {
        pLeft->next = pRight;
        pLeft = pLeft->right;
        pRight = pRight->left;
    }
    dfs(pRoot->left);
    dfs(pRoot->right);
}
struct Node* connect(struct Node* root) {
    struct Node* pRetVal = root;

    dfs(pRetVal);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int root[MAX_SIZE];
        int rootSize;
    } testCase[] = {{{1, 2, 3, 4, 5, 6, 7}, 7}, {{}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    struct Node* pRoot = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: root = [");
        for (j = 0; j < testCase[i].rootSize; ++j) {
            if (testCase[i].root[j] == INT_MIN) {
                printf("%snull", (j == 0 ? "" : ","));
                continue;
            }
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].root[j]);
        }
        printf("]\n");

        createNodeTree(&pRoot, testCase[i].root, 0, testCase[i].rootSize);
        pRoot = connect(pRoot);
        printf("Output: [");
        displayNodeTreeByNext(pRoot);
        printf("]\n");
#if (DEBUG)
        displayNodeTree(pRoot, 0);
        printf("\n");
#endif

        printf("\n");

        freeNodeTree(pRoot);
        pRoot = NULL;
    }

    return EXIT_SUCCESS;
}
