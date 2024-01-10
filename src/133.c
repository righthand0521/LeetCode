#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for a Node.
struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

#define DFS (1)
#define BFS (1)

#define MAX_NODE_SIZE (100 + 4)  // The number of nodes in the graph is in the range [0, 100].
struct Node** visited;
#if (DFS)
struct Node* dfs(struct Node* s) {
    if (s == NULL) {
        return NULL;
    }

    if (visited[s->val]) {
        return visited[s->val];
    }

    struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
    cloneNode->val = s->val;
    cloneNode->numNeighbors = s->numNeighbors;

    visited[cloneNode->val] = cloneNode;
    cloneNode->neighbors = (struct Node**)malloc(sizeof(struct Node*) * cloneNode->numNeighbors);

    for (int i = 0; i < cloneNode->numNeighbors; i++) {
        cloneNode->neighbors[i] = dfs(s->neighbors[i]);
    }

    return cloneNode;
}
#elif (BFS)
int* state;

void bfs(struct Node* s) {
    if (visited[s->val] && state[s->val] == 2) {
        return;
    }

    struct Node* neighbor;
    if (visited[s->val]) {
        neighbor = visited[s->val];
        neighbor->val = s->val;
        neighbor->numNeighbors = s->numNeighbors;
        neighbor->neighbors = (struct Node**)malloc(sizeof(struct Node*) * neighbor->numNeighbors);
    } else {
        neighbor = (struct Node*)malloc(sizeof(struct Node));
        neighbor->val = s->val;
        neighbor->numNeighbors = s->numNeighbors;
        neighbor->neighbors = (struct Node**)malloc(sizeof(struct Node*) * neighbor->numNeighbors);
        visited[s->val] = neighbor;
    }

    for (int i = 0; i < neighbor->numNeighbors; i++) {
        if (visited[s->neighbors[i]->val]) {
            neighbor->neighbors[i] = visited[s->neighbors[i]->val];
        } else {
            visited[s->neighbors[i]->val] = (struct Node*)malloc(sizeof(struct Node));
            state[s->neighbors[i]->val] = 1;
            neighbor->neighbors[i] = visited[s->neighbors[i]->val];
        }
    }

    state[neighbor->val] = 2;
}
#endif
struct Node* cloneGraph(struct Node* s) {
    struct Node* pRetVal = s;

#if (DFS)
    printf("DFS");

    visited = (struct Node**)malloc(sizeof(struct Node*) * MAX_NODE_SIZE);
    memset(visited, 0, sizeof(struct Node*) * MAX_NODE_SIZE);

    pRetVal = dfs(s);
#elif (BFS)
    printf("BFS");

    if (s == NULL) {
        return NULL;
    }

    visited = (struct Node**)malloc(sizeof(struct Node*) * MAX_NODE_SIZE);
    memset(visited, 0, sizeof(struct Node*) * MAX_NODE_SIZE);

    state = (int*)malloc(sizeof(int) * MAX_NODE_SIZE);
    memset(state, 0, sizeof(int) * MAX_NODE_SIZE);

    struct Node* QUEUE[MAX_NODE_SIZE];
    int head = -1;
    int eneighbor = -1;
    QUEUE[++eneighbor] = s;

    int flag[MAX_NODE_SIZE];
    memset(flag, 0, sizeof(int) * MAX_NODE_SIZE);

    struct Node* p;
    int i;
    while (head != eneighbor) {
        p = QUEUE[++head];
        bfs(p);
        for (i = 0; i < p->numNeighbors; i++) {
            if (!flag[p->neighbors[i]->val]) {
                QUEUE[++eneighbor] = p->neighbors[i];
                flag[p->neighbors[i]->val] = 1;
            }
        }
    }

    pRetVal = visited[s->val];
#endif

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int adjList[MAX_SIZE][2];
        int adjListSize;
        int adjListColSize[MAX_SIZE];
    } testCase[] = {{{{2, 4}, {1, 3}, {2, 4}, {1, 3}}, 4, {2, 2, 2, 2}}, {{{}}, 9, {}}, {{{}}, 0, {}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: adjList = [[2, 4], [1, 3], [2, 4], [1, 3]]
     *  Output: [[2, 4], [1, 3], [2, 4], [1, 3]]
     *
     *  Input: adjList = [[]]
     *  Output: [[]]
     *
     *  Input: adjList = []
     *  Output: []
     */

    // struct Node* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: people = [");
        for (j = 0; j < testCase[i].adjListSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].adjListColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].adjList[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        // pAnswer = cloneGraph(testCase[i].adjList);
        // printf("Output: %s\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
