#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/minimum-cost-to-convert-string-ii/solutions/2577877/zi-dian-shu-floyddp-by-endlesscheng-oi2r/
typedef struct Node {
    struct Node* son[26];
    int sid;
} Node;
Node* root = NULL;
int sid = 0;
Node* createNode() {
    Node* pObj = NULL;

    pObj = (Node*)malloc(sizeof(Node));
    if (pObj == NULL) {
        perror("malloc failed");
        return pObj;
    }
    pObj->sid = -1;
    for (int i = 0; i < 26; i++) {
        pObj->son[i] = NULL;
    }

    return pObj;
}
int put(const char* s) {
    int retVal = -1;

    int idx;
    Node* o = root;
    for (int i = 0; s[i]; i++) {
        idx = s[i] - 'a';
        if (o->son[idx] == NULL) {
            o->son[idx] = createNode();
        }
        o = o->son[idx];
    }

    if (o->sid < 0) {
        o->sid = sid++;
    }
    retVal = o->sid;

    return retVal;
}
void freeNode(Node* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (node->son[i] != NULL) {
            freeNode(node->son[i]);
            node->son[i] = NULL;
        }
    }

    free(node);
    node = NULL;
}
long long minimumCost(char* source, char* target, char** original, int originalSize, char** changed, int changedSize,
                      int* cost, int costSize) {
    long long retVal = -1;

    root = createNode();
    sid = 0;

    int maxNodes = costSize * 2;

    int** dis = (int**)malloc(maxNodes * sizeof(int*));
    for (int i = 0; i < maxNodes; i++) {
        dis[i] = (int*)malloc(maxNodes * sizeof(int));
        for (int j = 0; j < maxNodes; j++) {
            dis[i][j] = INT_MAX / 2;
        }
        dis[i][i] = 0;
    }

    int x, y;
    for (int i = 0; i < costSize; i++) {
        x = put(original[i]);
        y = put(changed[i]);
        if (cost[i] < dis[x][y]) {
            dis[x][y] = cost[i];
        }
    }

    for (int k = 0; k < sid; k++) {
        for (int i = 0; i < sid; i++) {
            if (dis[i][k] == INT_MAX / 2) {
                continue;
            }

            for (int j = 0; j < sid; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }

    int sourceSize = strlen(source);
    long long* dp = (long long*)malloc((sourceSize + 1) * sizeof(long long));
    dp[sourceSize] = 0;

    Node *p, *q;
    int d;
    long long candidate;
    for (int i = sourceSize - 1; i >= 0; i--) {
        dp[i] = LLONG_MAX / 2;
        if (source[i] == target[i]) {
            dp[i] = dp[i + 1];
        }

        p = root;
        q = root;
        for (int j = i; j < sourceSize; j++) {
            p = p->son[source[j] - 'a'];
            q = q->son[target[j] - 'a'];
            if ((p == NULL) || (q == NULL)) {
                break;
            }

            if ((p->sid < 0) || (q->sid < 0)) {
                continue;
            }

            d = dis[p->sid][q->sid];
            if (d < INT_MAX / 2) {
                candidate = (long long)d + dp[j + 1];
                if (candidate < dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
    }

    if (dp[0] < LLONG_MAX / 2) {
        retVal = dp[0];
    }

    //
    freeNode(root);
    root = NULL;
    for (int i = 0; i < maxNodes; i++) {
        free(dis[i]);
        dis[i] = NULL;
    }
    free(dis);
    dis = NULL;
    free(dp);
    dp = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* source;
        char* target;
        char* original[MAX_SIZE];
        int originalSize;
        char* changed[MAX_SIZE];
        int changedSize;
        int cost[MAX_SIZE];
        int costSize;
    } testCase[] = {
        {"abcd", "acbe", {"a", "b", "c", "c", "e", "d"}, 6, {"b", "c", "b", "e", "b", "e"}, 6, {2, 5, 5, 1, 2, 20}, 6},
        {"abcdefgh", "acdeeghh", {"bcd", "fgh", "thh"}, 3, {"cde", "thh", "ghh"}, 3, {1, 3, 5}, 3},
        {"abcdefgh", "addddddd", {"bcd", "defgh"}, 2, {"ddd", "ddddd"}, 2, {100, 1578}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input:
     *  source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"],
     *  changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
     *  Output: 28
     *
     *  Input:
     *  source = "abcdefgh", target = "acdeeghh", original = ["bcd","fgh","thh"],
     *  changed = ["cde","thh","ghh"], cost = [1,3,5]
     *  Output: 9
     *
     *  Input:
     *  source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"],
     *  changed = ["ddd","ddddd"], cost = [100,1578]
     *  Output: -1
     */

    int i, j;
    long long answer;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: source = \"%s\", target = \"%s\", original = [", testCase[i].source, testCase[i].target);
        for (j = 0; j < testCase[i].originalSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].original[j]);
        }
        printf("], changed = [");
        for (j = 0; j < testCase[i].originalSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].changed[j]);
        }
        printf("], cost = [");
        for (j = 0; j < testCase[i].costSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].cost[j]);
        }
        printf("]\n");

        answer = minimumCost(testCase[i].source, testCase[i].target, testCase[i].original, testCase[i].originalSize,
                             testCase[i].changed, testCase[i].changedSize, testCase[i].cost, testCase[i].costSize);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
