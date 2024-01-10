#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateBinaryTreeNodes(int n, int* leftChild, int leftChildSize, int* rightChild, int rightChildSize) {
    bool retVal = false;

    int i;

    //
    int root = -1;
    int children[n + 1];
    memset(children, 0, sizeof(children));
    for (i = 0; i < leftChildSize; ++i) {
        children[leftChild[i] + 1]++;
    }
    for (i = 0; i < rightChildSize; ++i) {
        children[rightChild[i] + 1]++;
    }
    for (i = 1; i < n + 1; ++i) {
        if (children[i] == 0) {
            root = i - 1;
            break;
        }
    }
    if (root == -1) {
        return retVal;
    }

    //
    int visited[n];
    memset(visited, 0, sizeof(visited));
    visited[root] = 1;

    int bfsQueue[n * 2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = root;

    int allChildSize = 2;
    int allChild[allChildSize];
    int node, child;
    while (bfsQueueHead > bfsQueueTail) {
        node = bfsQueue[bfsQueueTail];
        ++bfsQueueTail;

        memset(allChild, 0, sizeof(allChild));
        allChild[0] = leftChild[node];
        allChild[1] = rightChild[node];
        for (i = 0; i < allChildSize; ++i) {
            child = allChild[i];
            if (child == -1) {
                continue;
            }

            if (visited[child] != 0) {
                return retVal;
            }
            bfsQueue[bfsQueueHead++] = child;
            visited[child] = 1;
        }
    }
    for (i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int n;
        int leftChild[MAX_SIZE];
        int leftChildSize;
        int rightChild[MAX_SIZE];
        int rightChildSize;
    } testCase[] = {{4, {1, -1, 3, -1}, 4, {2, -1, -1, -1}, 4},
                    {4, {1, -1, 3, -1}, 4, {2, 3, -1, -1}, 4},
                    {2, {1, 0}, 2, {-1, -1}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
     *  Output: true
     *
     *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
     *  Output: false
     *
     *  Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
     *  Output: false
     */

    int i, j;
    bool answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, leftChild = [", testCase[i].n);
        for (j = 0; j < testCase[i].leftChildSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].leftChild[j]);
        }
        printf("], rightChild = [");
        for (j = 0; j < testCase[i].rightChildSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rightChild[j]);
        }
        printf("]\n");

        answer = validateBinaryTreeNodes(testCase[i].n, testCase[i].leftChild, testCase[i].leftChildSize,
                                         testCase[i].rightChild, testCase[i].rightChildSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
