#ifndef ADJACENCY_H
#define ADJACENCY_H

typedef struct Edge {
    int to;
    int cost;
    struct Edge *next;
} Edge;
Edge *createEdge(int to, int cost) {
    Edge *pObj = NULL;

    pObj = (Edge *)malloc(sizeof(Edge));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->to = to;
    pObj->cost = cost;
    pObj->next = NULL;

    return pObj;
}
void freeEdgeList(Edge *pList) {
    while (pList) {
        Edge *pFree = pList;
        pList = pList->next;
        free(pFree);
    }
}

#endif  // ADJACENCY_H
