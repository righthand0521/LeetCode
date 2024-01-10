#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/path-with-maximum-probability/solutions/543933/dijkstra-dui-you-hua-cyu-yan-by-numpy-2-ab0j/
#if (1)
#define N (10010)
#define M (1000000)

int hv;
double hp;

double heap[M][2];
int heapSize;

int h[N], to[M], ne[M], idx;
double w[M];

double dist[N];
bool st[N];

void push(int v, double p) {
    int i;
    for (i = ++heapSize; heap[i / 2][0] < p; i /= 2) {
        heap[i][0] = heap[i / 2][0];
        heap[i][1] = heap[i / 2][1];
    }
    heap[i][0] = p;
    heap[i][1] = v;
}
void pop() {
    hp = heap[1][0];
    hv = heap[1][1];

    double lastp = heap[heapSize][0];
    int lastv = heap[heapSize--][1];

    int i, child;
    for (i = 1; i * 2 <= heapSize; i = child) {
        child = i * 2;
        if (child != heapSize && heap[child + 1][0] > heap[child][0]) {
            child++;
        }

        if (lastp < heap[child][0]) {
            heap[i][0] = heap[child][0];
            heap[i][1] = heap[child][1];
        } else {
            break;
        }
    }
    heap[i][0] = lastp;
    heap[i][1] = lastv;
}
void add(int src, int dst, double pathProb) {
    to[idx] = dst;
    w[idx] = pathProb;
    ne[idx] = h[src];
    h[src] = idx++;
}
void dijkstra(int s, int n) {
    int i;

    dist[s] = 1.0;
    push(s, 1.0);
    while (heapSize > 0) {
        pop();
        if (st[hv]) {
            continue;
        }
        st[hv] = true;

        for (i = h[hv]; ~i; i = ne[i]) {
            if (!st[to[i]] && hp * w[i] > dist[to[i]]) {
                dist[to[i]] = hp * w[i];
                push(to[i], dist[to[i]]);
            }
        }
    }
}
#endif
double maxProbability(int n, int **edges, int edgesSize, int *edgesColSize, double *succProb, int succProbSize,
                      int start, int end) {
    double retVal = 0;

    int i;

    idx = 0;
    heapSize = 0;
    heap[0][0] = 1.0;
    memset(st, false, sizeof(st));
    memset(h, -1, sizeof(h));
    for (i = 0; i < n; i++) {
        dist[i] = 0.0;
    }

    int src, dst;
    double pathProb;
    for (i = 0; i < edgesSize; i++) {
        src = edges[i][0];
        dst = edges[i][1];
        pathProb = succProb[i];

        add(src, dst, pathProb);
        add(dst, src, pathProb);
    }

    dijkstra(start, n);
    if (dist[end] != 0.0) {
        retVal = dist[end];
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (20000)
#define MAX_COL_SIZE (2)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
        double succProb[MAX_ROW_SIZE];
        int succProbSize;
        int start;
        int end;
    } testCase[] = {{3, {{0, 1}, {1, 2}, {0, 2}}, 3, {2, 2, 2}, {0.5, 0.5, 0.2}, 3, 0, 2},
                    {3, {{0, 1}, {1, 2}, {0, 2}}, 3, {2, 2, 2}, {0.5, 0.5, 0.3}, 3, 0, 2},
                    {3, {{0, 1}}, 1, {2}, {0.5}, 1, 0, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
     *  Output: 0.25000
     *
     *  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
     *  Output: 0.30000
     *
     *  Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
     *  Output: 0.00000
     */

    int **pEdges = NULL;
    double answer = 0;
    int i, j, k = 0;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], succProb = [");
        for (j = 0; j < testCase[i].succProbSize; ++j) {
            printf("%s%f", (k == 0) ? "" : ",", testCase[i].succProb[j]);
        }
        printf("], start = %d, end = %d\n", testCase[i].start, testCase[i].end);

        pEdges = (int **)malloc(testCase[i].edgesSize * sizeof(int *));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int *)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }
        answer = maxProbability(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                testCase[i].succProb, testCase[i].succProbSize, testCase[i].start, testCase[i].end);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
