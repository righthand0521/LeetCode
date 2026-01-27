# [Graph](https://en.wikipedia.org/wiki/Graph_(discrete_mathematics))

- [Breadth-First Search](https://en.wikipedia.org/wiki/Breadth-first_search)
- [Depth-First Search](https://en.wikipedia.org/wiki/Depth-first_search)
- [Topological sorting](https://en.wikipedia.org/wiki/Topological_sorting)
- [Union Find](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

## [3108. Minimum Cost Walk in Weighted Graph](https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/)  2108

- [Official](https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/editorial/)

<details><summary>Description</summary>

```text
There is an undirected weighted graph with n vertices labeled from 0 to n - 1.

You are given the integer n and an array edges,
where edges[i] = [ui, vi, wi] indicates that there is an edge between vertices ui and vi with a weight of wi.

A walk on a graph is a sequence of vertices and edges.
The walk starts and ends with a vertex,
and each edge connects the vertex that comes before it and the vertex that comes after it.
It's important to note that a walk may visit the same edge or vertex more than once.

The cost of a walk starting at node u and ending at node v
is defined as the bitwise AND of the weights of the edges traversed during the walk.
In other words, if the sequence of edge weights encountered during the walk is w0, w1, w2, ..., wk,
then the cost is calculated as w0 & w1 & w2 & ... & wk, where & denotes the bitwise AND operator.

You are also given a 2D array query, where query[i] = [si, ti].
For each query, you need to find the minimum cost of the walk starting at vertex si and ending at vertex ti.
If there exists no such walk, the answer is -1.

Return the array answer, where answer[i] denotes the minimum cost of a walk for query i.

Example 1:
Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
Output: [1,-1]
Explanation:
To achieve the cost of 1 in the first query, we need to move on the following edges:
0->1 (weight 7), 1->2 (weight 1), 2->1 (weight 1), 1->3 (weight 7).
In the second query, there is no walk between nodes 3 and 4, so the answer is -1.

Example 2:
Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
Output: [0]
Explanation:
To achieve the cost of 0 in the first query, we need to move on the following edges:
1->2 (weight 1), 2->1 (weight 6), 1->2 (weight 1).

Constraints:
2 <= n <= 10^5
0 <= edges.length <= 10^5
edges[i].length == 3
0 <= ui, vi <= n - 1
ui != vi
0 <= wi <= 10^5
1 <= query.length <= 10^5
query[i].length == 2
0 <= si, ti <= n - 1
si != ti
```

<details><summary>Hint</summary>

```text
1. The intended solution uses Disjoint Set Union.
2. Notice that, if u and v are not connected then the answer is -1,
   otherwise we can use all the edges from the connected component where both belong to.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/minimum-cost-walk-in-weighted-graph/solutions/2727524/dai-quan-tu-li-lu-tu-de-zui-xiao-dai-jie-6tds/
int findParent(int* parent, int x) {
    int retVal;

    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    retVal = x;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumCost(int n, int** edges, int edgesSize, int* edgesColSize, int** query, int querySize, int* queryColSize,
                 int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    const int fullWeight = 0x7FFFFFFF;
    int x = 0;

    int parent[n];
    int weight[n];
    for (x = 0; n > x; x++) {
        parent[x] = x;
        weight[x] = fullWeight;
    }

    int e0 = 0, e1 = 0, p0 = 0, p1 = 0;
    for (x = 0; edgesSize > x; x++) {
        e0 = fmin(edges[x][0], edges[x][1]);
        e1 = fmax(edges[x][0], edges[x][1]);
        p0 = findParent(parent, e0);
        p1 = findParent(parent, e1);
        if (p0 != p1) {
            weight[p1] &= weight[p0];
            parent[p0] = p1;
        }
        weight[p1] &= edges[x][2];
    }

    pRetVal = (int*)calloc(querySize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (x = 0; querySize > x; x++) {
        if (query[x][0] == query[x][1]) {
            pRetVal[x] = 0;
        } else {
            p0 = findParent(parent, query[x][0]);
            p1 = findParent(parent, query[x][1]);
            if (p0 == p1) {
                pRetVal[x] = weight[p0];
            } else {
                pRetVal[x] = -1;
            }
        }
    }
    (*returnSize) = querySize;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int dfs(int node, vector<vector<pair<int, int>>>& adjList, vector<bool>& visited, vector<int>& components,
            int componentId) {
        // Initialize the cost to the number that has only 1s in its binary representation
        int retVal = numeric_limits<int>::max();

        components[node] = componentId;  // Mark the node as part of the current component
        visited[node] = true;
        for (auto& [neighbor, weight] : adjList[node]) {
            retVal &= weight;  // Update the cost by performing a bitwise AND of the edge weights
            if (visited[neighbor] == true) {
                continue;
            }
            // Recursively calculate the cost of the rest of the component and accumulate it into retVal
            retVal &= dfs(neighbor, adjList, visited, components, componentId);
        }

        return retVal;
    }

   public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> retVal;

        // Create the adjacency list of the graph
        vector<vector<pair<int, int>>> adjList(n);
        for (auto& edge : edges) {
            adjList[edge[0]].push_back({edge[1], edge[2]});
            adjList[edge[1]].push_back({edge[0], edge[2]});
        }

        vector<bool> visited(n, false);

        // Array to store the component ID of each node
        vector<int> components(n);
        vector<int> componentCost;
        int componentId = 0;
        // Perform DFS for each unvisited node to identify components and calculate their costs
        for (int node = 0; node < n; node++) {
            // If the node hasn't been visited, it's a new component
            if (visited[node] == true) {
                continue;
            }
            // Get the component cost and mark all nodes in the component
            componentCost.push_back(dfs(node, adjList, visited, components, componentId));
            // Increment the component ID for the next component
            componentId++;
        }

        for (auto& q : query) {
            int start = q[0];
            int end = q[1];
            // If they are in the same component, return the precomputed cost for the component
            if (components[start] == components[end]) {
                retVal.push_back(componentCost[components[start]]);
            } else {  // If they are in different components, return -1
                retVal.push_back(-1);
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dfs(self, node, adjList, visited, components, componentId):
        retVal = -1  # Initialize the cost to the number that has only 1s in its binary representation

        components[node] = componentId  # Mark the node as part of the current component
        visited[node] = True
        for neighbor, weight in adjList[node]:
            retVal &= weight  # Update the component cost by performing a bitwise AND of the edge weights
            if visited[neighbor] == True:
                continue
            # Recursively calculate the cost of the rest of the component and accumulate it into currentCost
            retVal &= self.dfs(neighbor, adjList, visited, components, componentId)

        return retVal

    def minimumCost(self, n: int, edges: List[List[int]], query: List[List[int]]) -> List[int]:
        retVal = []

        # Create the adjacency list of the graph
        adjList = [[] for _ in range(n)]
        for edge in edges:
            adjList[edge[0]].append((edge[1], edge[2]))
            adjList[edge[1]].append((edge[0], edge[2]))

        visited = [False] * n

        # Array to store the component ID of each node
        components = [0] * n
        componentCost = []
        componentId = 0
        # Perform DFS for each unvisited node to identify components and calculate their costs
        for node in range(n):
            if visited[node] == True:
                continue
            # Get the component cost and mark all nodes in the component
            componentCost.append(self.dfs(node, adjList, visited, components, componentId))
            componentId += 1

        for q in query:
            start, end = q
            # If they are in the same component, return the precomputed cost for the component
            # Else they are in different components, return -1
            if components[start] == components[end]:
                retVal.append(componentCost[components[start]])
            else:
                retVal.append(-1)

        return retVal
```

</details>

## [3203. Find Minimum Diameter After Merging Two Trees](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/)  2266

- [Official](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/editorial/)

<details><summary>Description</summary>

```text
There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively.
You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1,
respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and
edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

You must connect one node from the first tree with another node from the second tree with an edge.

Return the minimum possible diameter of the resulting tree.

The diameter of a tree is the length of the longest path between any two nodes in the tree.

Example 1:
Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
Output: 3
Explanation:
We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.

Example 2:
Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
Output: 5
Explanation:
We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.

Constraints:
1 <= n, m <= 10^5
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
```

<details><summary>Hint</summary>

```text
1. Suppose that we connected node a in tree1 with node b in tree2.
   The diameter length of the resulting tree will be the largest of the following 3 values:
   - The diameter of tree 1.
   - The diameter of tree 2.
   - The length of the longest path that starts at node a and
     that is completely within Tree 1 + The length of the longest path
     that starts at node b and that is completely within Tree 2 + 1.
   The added one in the third value is due to the additional edge that we have added between trees 1 and 2.
2. Values 1 and 2 are constant regardless of our choice of a and b.
   Therefore, we need to pick a and b in such a way that minimizes value 3.
3. If we pick a and b optimally, they will be in the diameters of Tree 1 and Tree 2, respectively.
   Exactly which nodes of the diameter should we pick?
4. a is the center of the diameter of tree 1, and b is the center of the diameter of tree 2.
```

</details>

</details>

<details><summary>C</summary>

```c
int** buildAdjList(int** edges, int edgesSize, int* edgesColSize, int** returnColSize) {
    int** pRetVal = NULL;

    int returnSize = edgesSize + 1;

    (*returnColSize) = (int*)malloc(returnSize * sizeof(int));
    if ((*returnColSize) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    for (int i = 0; i < edgesSize; ++i) {
        (*returnColSize)[edges[i][0]]++;
        (*returnColSize)[edges[i][1]]++;
    }

    pRetVal = (int**)malloc(returnSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColSize));
        (*returnColSize) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < returnSize; ++i) {
        pRetVal[i] = (int*)malloc((*returnColSize)[i] * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColSize));
            (*returnColSize) = NULL;
            for (int j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnColSize)[i] * sizeof(int)));
    }

    memset((*returnColSize), 0, (returnSize * sizeof(int)));
    int src, dst;
    for (int i = 0; i < edgesSize; ++i) {
        src = edges[i][0];
        dst = edges[i][1];
        pRetVal[src][(*returnColSize)[src]++] = dst;
        pRetVal[dst][(*returnColSize)[dst]++] = src;
    }

    return pRetVal;
};
void findDiameter(int** adjList, int* adjListColSize, int node, int parent, int* first, int* second) {
    (*first) = 0;
    (*second) = 0;

    int childDiameter, depth;
    int maxDepth1 = 0;
    int maxDepth2 = 0;
    int diameter = 0;
    for (int i = 0; i < adjListColSize[node]; ++i) {
        // Skip the parent to avoid cycles
        if (adjList[node][i] == parent) {
            continue;
        }

        // Recursively calculate the diameter and depth of the neighbor's subtree
        findDiameter(adjList, adjListColSize, adjList[node][i], node, first, second);
        childDiameter = (*first);
        depth = (*second);

        // Update the maximum diameter of the subtree
        diameter = fmax(diameter, childDiameter);

        // Increment the depth to include the edge to this neighbor
        depth++;

        // Update the two largest depths from the current node
        if (depth > maxDepth1) {
            maxDepth2 = maxDepth1;
            maxDepth1 = depth;
        } else if (depth > maxDepth2) {
            maxDepth2 = depth;
        }
    }

    // Update the diameter to include the path through the current node
    diameter = fmax(diameter, maxDepth1 + maxDepth2);

    (*first) = diameter;
    (*second) = maxDepth1;
}
int minimumDiameterAfterMerge(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size,
                              int* edges2ColSize) {
    int retVal = 0;

    int* adjListColSize1 = NULL;
    int** adjList1 = buildAdjList(edges1, edges1Size, edges1ColSize, &adjListColSize1);
    int diameter1 = 0;
    findDiameter(adjList1, adjListColSize1, 0, -1, &diameter1, &retVal);

    int* adjListColSize2 = NULL;
    int** adjList2 = buildAdjList(edges2, edges2Size, edges2ColSize, &adjListColSize2);
    int diameter2 = 0;
    findDiameter(adjList2, adjListColSize2, 0, -1, &diameter2, &retVal);

    int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

    retVal = diameter1;
    retVal = fmax(retVal, diameter2);
    retVal = fmax(retVal, combinedDiameter);

    //
    free(adjListColSize1);
    adjListColSize1 = NULL;
    for (int i = 0; i <= edges1Size; ++i) {
        free(adjList1[i]);
        adjList1[i] = NULL;
    }
    free(adjList1);
    adjList1 = NULL;
    free(adjListColSize2);
    adjListColSize2 = NULL;
    for (int i = 0; i <= edges2Size; ++i) {
        free(adjList2[i]);
        adjList2[i] = NULL;
    }
    free(adjList2);
    adjList2 = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    vector<vector<int>> buildAdjList(int size, vector<vector<int>>& edges) {
        vector<vector<int>> retVal(size);

        for (auto& edge : edges) {
            retVal[edge[0]].push_back(edge[1]);
            retVal[edge[1]].push_back(edge[0]);
        }

        return retVal;
    };

    pair<int, int> findDiameter(vector<vector<int>>& adjList, int node, int parent) {
        pair<int, int> retVal = {0, 0};

        int maxDepth1 = 0;
        int maxDepth2 = 0;
        int diameter = 0;
        for (int neighbor : adjList[node]) {
            // Skip the parent to avoid cycles
            if (neighbor == parent) {
                continue;
            }

            // Recursively calculate the diameter and depth of the neighbor's subtree
            auto [childDiameter, depth] = findDiameter(adjList, neighbor, node);

            // Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter);

            // Increment the depth to include the edge to this neighbor
            depth++;

            // Update the two largest depths from the current node
            if (depth > maxDepth1) {
                maxDepth2 = maxDepth1;
                maxDepth1 = depth;
            } else if (depth > maxDepth2) {
                maxDepth2 = depth;
            }
        }

        // Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2);

        retVal = {diameter, maxDepth1};

        return retVal;
    }

   public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int retVal = 0;

        int edges1Size = edges1.size() + 1;
        vector<vector<int>> adjList1 = buildAdjList(edges1Size, edges1);
        int diameter1 = findDiameter(adjList1, 0, -1).first;

        int edges2Size = edges2.size() + 1;
        vector<vector<int>> adjList2 = buildAdjList(edges2Size, edges2);
        int diameter2 = findDiameter(adjList2, 0, -1).first;

        int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

        retVal = max({diameter1, diameter2, combinedDiameter});

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def buildAdjList(self, size: int, edges: list[list[int]]) -> list[list[int]]:
        retVal = [[] for _ in range(size)]

        for edge in edges:
            retVal[edge[0]].append(edge[1])
            retVal[edge[1]].append(edge[0])

        return retVal

    def findDiameter(self, adjList: list[list[int]], node: int, parent: int) -> tuple[int, int]:
        retVal = 0, 0

        maxDepth1 = 0
        maxDepth2 = 0
        diameter = 0
        for neighbor in adjList[node]:
            # Skip the parent to avoid cycles
            if neighbor == parent:
                continue

            # Recursively calculate the diameter and depth of the neighbor's subtree
            childDiameter, depth = self.findDiameter(adjList, neighbor, node)

            # Increment depth to include edge to neighbor
            depth += 1

            # Update the maximum diameter of the subtree
            diameter = max(diameter, childDiameter)

            # Update the two largest depths from the current node
            if depth > maxDepth1:
                maxDepth2 = maxDepth1
                maxDepth1 = depth
            elif depth > maxDepth2:
                maxDepth2 = depth

        # Update the diameter to include the path through the current node
        diameter = max(diameter, maxDepth1 + maxDepth2)

        # Return the diameter and the longest depth
        retVal = diameter, maxDepth1

        return retVal

    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
        retVal = 0

        edges1Size = len(edges1) + 1
        adjList1 = self.buildAdjList(edges1Size, edges1)
        diameter1, _ = self.findDiameter(adjList1, 0, -1)

        edges2Size = len(edges2) + 1
        adjList2 = self.buildAdjList(edges2Size, edges2)
        diameter2, _ = self.findDiameter(adjList2, 0, -1)

        combinedDiameter = ceil(diameter1 / 2) + ceil(diameter2 / 2) + 1

        retVal = max(diameter1, diameter2, combinedDiameter)

        return retVal
```

</details>

## [3243. Shortest Distance After Road Addition Queries I](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/)  1567

- [Official](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/editorial/)
- [Official](https://leetcode.cn/problems/shortest-distance-after-road-addition-queries-i/solutions/2984418/xin-zeng-dao-lu-cha-xun-hou-de-zui-duan-9smce/)

<details><summary>Description</summary>

```text
You are given an integer n and a 2D integer array queries.

There are n cities numbered from 0 to n - 1.
Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi.
After each query, you need to find the length of the shortest path from city 0 to city n - 1.

Return an array answer where for each i in the range [0, queries.length - 1],
answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.

Example 1:
Input: n = 5, queries = [[2,4],[0,2],[0,4]]
Output: [3,2,1]
Explanation:
After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.

Example 2:
Input: n = 4, queries = [[0,3],[0,2]]
Output: [1,1]
Explanation:
After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.
After the addition of the road from 0 to 2, the length of the shortest path remains 1.

Constraints:
3 <= n <= 500
1 <= queries.length <= 500
queries[i].length == 2
0 <= queries[i][0] < queries[i][1] < n
1 < queries[i][1] - queries[i][0]
There are no repeated roads among the queries.
```

<details><summary>Hint</summary>

```text
1. Maintain the graph and use an efficient shortest path algorithm after each update.
2. We use BFS/Dijkstra for each query.
```

</details>

</details>

<details><summary>C</summary>

```c
typedef struct Node {
    int val;
    struct Node *next;
} Node;
typedef struct List {
    Node *node;
} List;
int push(List *pObj, int val) {
    int retVal = EXIT_SUCCESS;

    Node *pNew = (Node *)malloc(sizeof(Node));
    if (pNew == NULL) {
        perror("malloc");
        retVal = EXIT_FAILURE;
        return retVal;
    }
    pNew->next = pObj->node;
    pNew->val = val;

    pObj->node = pNew;

    return retVal;
}
void freeList(List *pObj) {
    Node *pFree;
    Node *pCurrent;
    for (pCurrent = pObj->node; pCurrent != NULL;) {
        pFree = pCurrent;
        pCurrent = pCurrent->next;
        free(pFree);
        pFree = NULL;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *shortestDistanceAfterQueries(int n, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
    int *pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    List *adjacency = (List *)malloc(n * sizeof(List));
    if (adjacency == NULL) {
        perror("malloc");
        goto exit;
    }
    memset(adjacency, 0, n * sizeof(List));

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        perror("malloc");
        goto exit_adjacency;
    }
    memset(dp, 0, n * sizeof(int));

    for (i = 1; i < n; ++i) {
        if (push(&adjacency[i], i - 1) == EXIT_FAILURE) {
            goto exit_dp;
        }
        dp[i] = i;
    }

    pRetVal = (int *)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_dp;
    }

    Node *pCurrent;
    for (i = 0; i < queriesSize; ++i) {
        if (push(&adjacency[queries[i][1]], queries[i][0]) == EXIT_FAILURE) {
            i = n;
            goto exit_dp;
        }

        for (j = queries[i][1]; j < n; ++j) {
            for (pCurrent = adjacency[j].node; pCurrent != NULL; pCurrent = pCurrent->next) {
                dp[j] = fmin(dp[j], dp[pCurrent->val] + 1);
            }
        }
        pRetVal[i] = dp[n - 1];
    }
    (*returnSize) = queriesSize;
    i = n;

exit_dp:
    free(dp);
    dp = NULL;

    for (j = 0; j < i; ++j) {
        freeList(&adjacency[j]);
    }

exit_adjacency:
    free(adjacency);
    adjacency = NULL;

exit:
    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int findMinDistance(vector<vector<int>>& adjList, int n) {
        int retVal = 0;

        vector<int> dp(n);
        dp[n - 1] = 0;
        for (int currentNode = n - 2; currentNode >= 0; currentNode--) {
            int minDistance = n;
            for (auto neighbor : adjList[currentNode]) {
                minDistance = min(minDistance, dp[neighbor] + 1);
            }
            dp[currentNode] = minDistance;
        }
        retVal = dp[0];

        return retVal;
    }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> retVal;

        vector<vector<int>> adjacency(n, vector<int>(0));
        for (int i = 0; i < n - 1; i++) {
            adjacency[i].push_back(i + 1);
        }

        for (auto& road : queries) {
            int src = road[0];
            int dst = road[1];
            adjacency[src].push_back(dst);

            retVal.push_back(findMinDistance(adjacency, n));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def findMinDistance(self, adjacency: List[List[int]], n: int) -> int:
        retVal = 0

        dp = [0] * n
        dp[n - 1] = 0
        for currentNode in range(n - 2, -1, -1):
            minDistance = n
            for neighbor in adjacency[currentNode]:
                minDistance = min(minDistance, dp[neighbor] + 1)
            dp[currentNode] = minDistance
        retVal = dp[0]

        return retVal

    def shortestDistanceAfterQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        retVal = []

        adjacency = [[] for _ in range(n)]
        for i in range(n - 1):
            adjacency[i].append(i + 1)

        for src, dst in queries:
            adjacency[src].append(dst)
            retVal.append(self.findMinDistance(adjacency, n))

        return retVal
```

</details>

## [3341. Find Minimum Time to Reach Last Room I](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/)  1721

- [Official](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/editorial/)
- [Official](https://leetcode.cn/problems/find-minimum-time-to-reach-last-room-i/solutions/3669493/dao-da-zui-hou-yi-ge-fang-jian-de-zui-sh-i9zw/)

<details><summary>Description</summary>

```text
There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m,
where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room.
You start from the room (0, 0) at time t = 0 and can move to an adjacent room.
Moving between adjacent rooms takes exactly one second.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.

Example 1:
Input: moveTime = [[0,4],[4,4]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in one second.

Example 2:
Input: moveTime = [[0,0,0],[0,0,0]]
Output: 3
Explanation:
The minimum time required is 3 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in one second.
At time t == 2, move from room (1, 1) to room (1, 2) in one second.

Example 3:
Input: moveTime = [[0,1],[1,2]]
Output: 3

Constraints:
2 <= n == moveTime.length <= 50
2 <= m == moveTime[i].length <= 50
0 <= moveTime[i][j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use shortest path algorithms.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef QUEUE_H
#define QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int x;
    int y;
    int distance;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

static bool greater(const void *a, const void *b) {
    static bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = e1->distance > e2->distance;

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    int tmp;
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        tmp = *a;
        *a = *b;
        *b = tmp;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = NULL;

    obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    if (obj->arr == NULL) {
        perror("malloc");
        free(obj);
        obj = NULL;
        return obj;
    }
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;

    return obj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));

    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    Element *pRetVal = NULL;

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue *obj) {
    bool retVal = false;

    if (obj->queueSize == 0) {
        retVal = true;
    }

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize == 0) {
        return NULL;
    }
    pRetVal = &obj->arr[0];

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // QUEUE_H
int minTimeToReach(int **moveTime, int moveTimeSize, int *moveTimeColSize) {
    int retVal = 0;

    int rowSize = moveTimeSize;
    int colSize = moveTimeColSize[0];

    int dijkstra[rowSize][colSize];
    memset(dijkstra, 0x3f, sizeof(dijkstra));
    dijkstra[0][0] = 0;

    int visit[rowSize][colSize];
    memset(visit, 0, sizeof(visit));

    PriorityQueue *queue = createPriorityQueue(greater);
    Element e = {0, 0, 0};
    enQueue(queue, &e);

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Element *p;
    Element s;
    int nextX, nextY, distances;
    while (isEmpty(queue) == false) {
        p = front(queue);
        s = (Element){p->x, p->y, p->distance};
        deQueue(queue);

        if (visit[s.x][s.y]) {
            continue;
        }
        visit[s.x][s.y] = 1;

        for (int i = 0; i < 4; i++) {
            nextX = s.x + directions[i][0];
            if ((nextX < 0) || (nextX >= rowSize)) {
                continue;
            }
            nextY = s.y + directions[i][1];
            if ((nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            distances = fmax(dijkstra[s.x][s.y], moveTime[nextX][nextY]) + 1;
            if (dijkstra[nextX][nextY] > distances) {
                dijkstra[nextX][nextY] = distances;
                e.x = nextX;
                e.y = nextY;
                e.distance = distances;
                enQueue(queue, &e);
            }
        }
    }
    retVal = dijkstra[rowSize - 1][colSize - 1];

    // Free the allocated memory
    freeQueue(queue);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class State {
   public:
    int x;
    int y;
    int distance;
    State(int x, int y, int distance) : x(x), y(y), distance(distance) {}
};

class Solution {
   private:
    int inf = 0x3f3f3f3f;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

   public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int retVal = 0;

        int rowSize = moveTime.size();
        int colSize = moveTime[0].size();

        vector<vector<int>> dijkstra(rowSize, vector<int>(colSize, inf));
        dijkstra[0][0] = 0;

        vector<vector<int>> visit(rowSize, vector<int>(colSize, 0));

        auto cmp = [](const State& a, const State& b) {
            // Compare the distances
            return a.distance > b.distance;
        };
        priority_queue<State, vector<State>, decltype(cmp)> queue(cmp);
        queue.push(State(0, 0, 0));

        while (queue.empty() == false) {
            State node = queue.top();
            queue.pop();

            if (visit[node.x][node.y]) {
                continue;
            }
            visit[node.x][node.y] = 1;

            for (int i = 0; i < 4; i++) {
                int nextX = node.x + directions[i][0];
                if ((nextX < 0) || (nextX >= rowSize)) {
                    continue;
                }

                int nextY = node.y + directions[i][1];
                if ((nextY < 0) || (nextY >= colSize)) {
                    continue;
                }

                int distances = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + 1;
                if (dijkstra[nextX][nextY] > distances) {
                    dijkstra[nextX][nextY] = distances;
                    queue.push(State(nextX, nextY, distances));
                }
            }
        }
        retVal = dijkstra[rowSize - 1][colSize - 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class State:
    def __init__(self, x, y, distance) -> None:
        self.x = x
        self.y = y
        self.distance = distance

    def __lt__(self, other) -> bool:
        retVal = False

        if self.distance < other.distance:
            retVal = True

        return retVal


class Solution:
    def __init__(self) -> None:
        self.directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(moveTime)
        colSize = len(moveTime[0])

        dijkstra = [[float("inf")] * colSize for _ in range(rowSize)]
        dijkstra[0][0] = 0

        visit = [[0] * colSize for _ in range(rowSize)]

        queue = []
        heappush(queue, State(0, 0, 0))

        while queue:
            node = heappop(queue)
            if visit[node.x][node.y]:
                continue

            visit[node.x][node.y] = 1
            for dx, dy in self.directions:
                nextX = node.x + dx
                if (nextX < 0) or (nextX >= rowSize):
                    continue

                nextY = node.y + dy
                if (nextY < 0) or (nextY >= colSize):
                    continue

                distance = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + 1
                if dijkstra[nextX][nextY] > distance:
                    dijkstra[nextX][nextY] = distance
                    heappush(queue, State(nextX, nextY, distance))

        retVal = dijkstra[rowSize - 1][colSize - 1]

        return retVal
```

</details>

## [3342. Find Minimum Time to Reach Last Room II](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/)  1861

- [Official](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/editorial/)
- [Official](https://leetcode.cn/problems/find-minimum-time-to-reach-last-room-ii/solutions/3669494/dao-da-zui-hou-yi-ge-fang-jian-de-zui-sh-dj3j/)

<details><summary>Description</summary>

```text
There is a dungeon with n x m rooms arranged as a grid.

You are given a 2D array moveTime of size n x m,
where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room.
You start from the room (0, 0) at time t = 0 and can move to an adjacent room.
Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.

Return the minimum time to reach the room (n - 1, m - 1).

Two rooms are adjacent if they share a common wall, either horizontally or vertically.

Example 1:
Input: moveTime = [[0,4],[4,4]]
Output: 7
Explanation:
The minimum time required is 7 seconds.
At time t == 4, move from room (0, 0) to room (1, 0) in one second.
At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.

Example 2:
Input: moveTime = [[0,0,0,0],[0,0,0,0]]
Output: 6
Explanation:
The minimum time required is 6 seconds.
At time t == 0, move from room (0, 0) to room (1, 0) in one second.
At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
At time t == 3, move from room (1, 1) to room (1, 2) in one second.
At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.

Example 3:
Input: moveTime = [[0,1],[1,2]]
Output: 4

Constraints:
2 <= n == moveTime.length <= 750
2 <= m == moveTime[i].length <= 750
0 <= moveTime[i][j] <= 10^9
```

<details><summary>Hint</summary>

```text
1. Use shortest path algorithms with a state for the last move being odd or even indexed.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef QUEUE_H
#define QUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int x;
    int y;
    int distance;
} Element;
typedef bool (*compare)(const void *, const void *);
typedef struct PriorityQueue {
    Element *arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;

static bool greater(const void *a, const void *b) {
    static bool retVal = false;

    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;
    retVal = e1->distance > e2->distance;

    return retVal;
}
static void memswap(void *m1, void *m2, size_t size) {
    int tmp;
    unsigned char *a = (unsigned char *)m1;
    unsigned char *b = (unsigned char *)m2;
    while (size--) {
        tmp = *a;
        *a = *b;
        *b = tmp;

        a++;
        b++;
    }
}
static void swap(Element *arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element *arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue *createPriorityQueue(compare cmpFunc) {
    PriorityQueue *obj = NULL;

    obj = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (obj == NULL) {
        perror("malloc");
        return obj;
    }
    obj->capacity = MIN_QUEUE_SIZE;
    obj->arr = (Element *)malloc(sizeof(Element) * obj->capacity);
    if (obj->arr == NULL) {
        perror("malloc");
        free(obj);
        obj = NULL;
        return obj;
    }
    obj->queueSize = 0;
    obj->lessFunc = cmpFunc;

    return obj;
}
void heapfiy(PriorityQueue *obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue *obj, Element *e) {
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));

    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element *deQueue(PriorityQueue *obj) {
    Element *pRetVal = NULL;

    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    pRetVal = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return pRetVal;
}
bool isEmpty(const PriorityQueue *obj) {
    bool retVal = false;

    if (obj->queueSize == 0) {
        retVal = true;
    }

    return retVal;
}
Element *front(const PriorityQueue *obj) {
    Element *pRetVal = NULL;

    if (obj->queueSize == 0) {
        return NULL;
    }
    pRetVal = &obj->arr[0];

    return pRetVal;
}
void clear(PriorityQueue *obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue *obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue *obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // QUEUE_H
int minTimeToReach(int **moveTime, int moveTimeSize, int *moveTimeColSize) {
    int retVal = 0;

    int rowSize = moveTimeSize;
    int colSize = moveTimeColSize[0];

    int dijkstra[rowSize][colSize];
    memset(dijkstra, 0x3f, sizeof(dijkstra));
    dijkstra[0][0] = 0;

    int visit[rowSize][colSize];
    memset(visit, 0, sizeof(visit));

    PriorityQueue *queue = createPriorityQueue(greater);
    Element e = {0, 0, 0};
    enQueue(queue, &e);

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Element *p;
    Element s;
    int nextX, nextY, distances;
    while (isEmpty(queue) == false) {
        p = front(queue);
        s = (Element){p->x, p->y, p->distance};
        deQueue(queue);

        if (visit[s.x][s.y]) {
            continue;
        }

        if ((s.x == rowSize - 1) && (s.y == colSize - 1)) {
            break;
        }

        visit[s.x][s.y] = 1;

        for (int i = 0; i < 4; i++) {
            nextX = s.x + directions[i][0];
            if ((nextX < 0) || (nextX >= rowSize)) {
                continue;
            }
            nextY = s.y + directions[i][1];
            if ((nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            distances = fmax(dijkstra[s.x][s.y], moveTime[nextX][nextY]) + (s.x + s.y) % 2 + 1;
            if (dijkstra[nextX][nextY] > distances) {
                dijkstra[nextX][nextY] = distances;
                e.x = nextX;
                e.y = nextY;
                e.distance = distances;
                enQueue(queue, &e);
            }
        }
    }
    retVal = dijkstra[rowSize - 1][colSize - 1];

    // Free the allocated memory
    freeQueue(queue);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class State {
   public:
    int x;
    int y;
    int distance;
    State(int x, int y, int distance) : x(x), y(y), distance(distance) {}
#if 0
#else
    bool operator<(const State& rth) const {
        // Compare the distances
        return distance > rth.distance;
    }
#endif
};

class Solution {
   private:
    int inf = 0x3f3f3f3f;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

   public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int retVal = 0;

        int rowSize = moveTime.size();
        int colSize = moveTime[0].size();

        vector<vector<int>> dijkstra(rowSize, vector<int>(colSize, inf));
        dijkstra[0][0] = 0;

        vector<vector<int>> visit(rowSize, vector<int>(colSize, 0));

#if 0
        auto cmp = [](const State& a, const State& b) {
            // Compare the distances
            return a.distance > b.distance;
        };
        priority_queue<State, vector<State>, decltype(cmp)> queue(cmp);
#else
        priority_queue<State> queue;
#endif
        queue.push(State(0, 0, 0));

        while (queue.empty() == false) {
            State node = queue.top();
            queue.pop();

            if (visit[node.x][node.y]) {
                continue;
            }

            if ((node.x == rowSize - 1) && (node.y == colSize - 1)) {
                break;
            }

            visit[node.x][node.y] = 1;

            for (int i = 0; i < 4; i++) {
                int nextX = node.x + directions[i][0];
                if ((nextX < 0) || (nextX >= rowSize)) {
                    continue;
                }

                int nextY = node.y + directions[i][1];
                if ((nextY < 0) || (nextY >= colSize)) {
                    continue;
                }

                int distances = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + (node.x + node.y) % 2 + 1;
                if (dijkstra[nextX][nextY] > distances) {
                    dijkstra[nextX][nextY] = distances;
                    queue.push(State(nextX, nextY, distances));
                }
            }
        }
        retVal = dijkstra[rowSize - 1][colSize - 1];

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class State:
    def __init__(self, x, y, distance) -> None:
        self.x = x
        self.y = y
        self.distance = distance

    def __lt__(self, other) -> bool:
        retVal = False

        if self.distance < other.distance:
            retVal = True

        return retVal


class Solution:
    def __init__(self) -> None:
        self.directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        retVal = 0

        rowSize = len(moveTime)
        colSize = len(moveTime[0])

        dijkstra = [[float("inf")] * colSize for _ in range(rowSize)]
        dijkstra[0][0] = 0

        visit = [[0] * colSize for _ in range(rowSize)]

        queue = []
        heappush(queue, State(0, 0, 0))

        while queue:
            node = heappop(queue)
            if visit[node.x][node.y]:
                continue

            if (node.x == rowSize - 1) and (node.y == colSize - 1):
                break

            visit[node.x][node.y] = 1

            for dx, dy in self.directions:
                nextX = node.x + dx
                if (nextX < 0) or (nextX >= rowSize):
                    continue

                nextY = node.y + dy
                if (nextY < 0) or (nextY >= colSize):
                    continue

                distance = max(dijkstra[node.x][node.y], moveTime[nextX][nextY]) + (node.x + node.y) % 2 + 1
                if dijkstra[nextX][nextY] > distance:
                    dijkstra[nextX][nextY] = distance
                    heappush(queue, State(nextX, nextY, distance))

        retVal = dijkstra[rowSize - 1][colSize - 1]

        return retVal
```

</details>

## [3607. Power Grid Maintenance](https://leetcode.com/problems/power-grid-maintenance/)  1700

- [Official](https://leetcode.com/problems/power-grid-maintenance/editorial/)
- [Official](https://leetcode.cn/problems/power-grid-maintenance/solutions/3819897/dian-wang-wei-hu-by-leetcode-solution-d92h/)

<details><summary>Description</summary>

```text
You are given an integer c representing c power stations,
each with a unique identifier id from 1 to c (1‑based indexing).

These stations are interconnected via n bidirectional cables, represented by a 2D array connections,
where each element connections[i] = [ui, vi] indicates a connection between station ui and station vi.
Stations that are directly or indirectly connected form a power grid.

Initially, all stations are online (operational).

You are also given a 2D array queries, where each query is one of the following two types:
- [1, x]: A maintenance check is requested for station x.
  If station x is online, it resolves the check by itself.
  If station x is offline,
  the check is resolved by the operational station with the smallest id in the same power grid as x.
  If no operational station exists in that grid, return -1.
- [2, x]: Station x goes offline (i.e., it becomes non-operational).

Return an array of integers representing the results of each query of type [1, x] in the order they appear.

Note: The power grid preserves its structure;
an offline (non‑operational) node remains part of its grid and taking it offline does not alter connectivity.

Example 1:
Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
Output: [3,2,3]
Explanation:
- Initially, all stations {1, 2, 3, 4, 5} are online and form a single power grid.
- Query [1,3]: Station 3 is online, so the maintenance check is resolved by station 3.
- Query [2,1]: Station 1 goes offline. The remaining online stations are {2, 3, 4, 5}.
- Query [1,1]: Station 1 is offline,
  so the check is resolved by the operational station with the smallest id among {2, 3, 4, 5}, which is station 2.
- Query [2,2]: Station 2 goes offline. The remaining online stations are {3, 4, 5}.
- Query [1,2]: Station 2 is offline,
  so the check is resolved by the operational station with the smallest id among {3, 4, 5}, which is station 3.

Example 2:
Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
Output: [1,-1]
Explanation:
- There are no connections, so each station is its own isolated grid.
- Query [1,1]: Station 1 is online in its isolated grid, so the maintenance check is resolved by station 1.
- Query [2,1]: Station 1 goes offline.
- Query [1,1]: Station 1 is offline and there are no other stations in its grid, so the result is -1.

Constraints:
1 <= c <= 10^5
0 <= n == connections.length <= min(10^5, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 10^5
queries[i].length == 2
queries[i][0] is either 1 or 2.
1 <= queries[i][1] <= c
```

<details><summary>Hint</summary>

```text
1. Use DFS or BFS to assign each station a component ID
2. For each component, maintain a sorted set of online station IDs
3. For query [2, x], remove x from the set of its component
4. For query [1, x], if x is in its component’s set return x;
   otherwise if the set is non-empty return its smallest element; else return -1
5. Precompute all components and then handle each query in O(log n) time using the sorted sets
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef DSU_H
#define DSU_H

typedef struct {
    int* parent;
    int size;
} DSU;
DSU* dsuCreate(int size) {
    DSU* pObj = NULL;

    pObj = (DSU*)malloc(sizeof(DSU));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->size = size;
    pObj->parent = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        pObj->parent[i] = i;
    }

    return pObj;
}
int dsuFind(DSU* pObj, int x) {
    int retVal = 0;

    if (pObj->parent[x] != x) {
        pObj->parent[x] = dsuFind(pObj, pObj->parent[x]);
    }
    retVal = pObj->parent[x];

    return retVal;
}
void dsuJoin(DSU* pObj, int u, int v) {
    //
    pObj->parent[dsuFind(pObj, v)] = dsuFind(pObj, u);
}
void dsuFree(DSU* pObj) {
    free(pObj->parent);
    pObj->parent = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // DSU_H
#ifndef HASH_H
#define DSU_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** pObj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*pObj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** pObj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(pObj, key) == NULL) {
        HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
        if (pEntry == NULL) {
            perror("malloc");
            return retVal;
        }
        pEntry->key = key;
        pEntry->val = val;
        HASH_ADD_INT(*pObj, key, pEntry);
        retVal = true;
    }

    return retVal;
}
void hashSetItem(HashItem** pObj, int key, int val) {
    HashItem* pEntry = hashFindItem(pObj, key);
    if (pEntry == NULL) {
        hashAddItem(pObj, key, val);
    } else {
        pEntry->val = val;
    }
}
int hashGetItem(HashItem** pObj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(pObj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** pObj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *pObj, curr, tmp) {
        HASH_DEL(*pObj, curr);
        free(curr);
    }
}

#endif  // HASH_H
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* processQueries(int c, int** connections, int connectionsSize, int* connectionsColSize, int** queries,
                    int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    DSU* dsu = dsuCreate(c + 1);
    for (int i = 0; i < connectionsSize; i++) {
        dsuJoin(dsu, connections[i][0], connections[i][1]);
    }

    bool* online = (bool*)malloc((c + 1) * sizeof(bool));
    int* offlineCounts = (int*)calloc(c + 1, sizeof(int));
    for (int i = 0; i <= c; i++) {
        online[i] = true;
    }
    for (int i = 0; i < queriesSize; i++) {
        int op = queries[i][0];
        int x = queries[i][1];
        if (op == 2) {
            online[x] = false;
            offlineCounts[x]++;
        }
    }

    HashItem* minimumOnlineStations = NULL;
    for (int i = 1; i <= c; i++) {
        int root = dsuFind(dsu, i);
        if (hashFindItem(&minimumOnlineStations, root) == NULL) {
            hashAddItem(&minimumOnlineStations, root, -1);
        }

        int station = hashGetItem(&minimumOnlineStations, root, -1);
        if (online[i]) {
            if (station == -1 || station > i) {
                hashSetItem(&minimumOnlineStations, root, i);
            }
        }
    }

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit;
    }

    for (int i = queriesSize - 1; i >= 0; i--) {
        int op = queries[i][0];
        int x = queries[i][1];
        int root = dsuFind(dsu, x);
        int station = hashGetItem(&minimumOnlineStations, root, -1);

        if (op == 1) {
            if (online[x]) {
                pRetVal[(*returnSize)++] = x;
            } else {
                pRetVal[(*returnSize)++] = station;
            }
        }

        if (op == 2) {
            if (offlineCounts[x] > 1) {
                offlineCounts[x]--;
            } else {
                online[x] = true;
                if (station == -1 || station > x) {
                    hashSetItem(&minimumOnlineStations, root, x);
                }
            }
        }
    }

    for (int i = 0, j = (*returnSize) - 1; i < j; i++, j--) {
        int temp = pRetVal[i];
        pRetVal[i] = pRetVal[j];
        pRetVal[j] = temp;
    }

exit:
    dsuFree(dsu);
    free(online);
    free(offlineCounts);
    hashFree(&minimumOnlineStations);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class DSU {
   public:
    vector<int> parent;

    DSU(int size) {
        parent.resize(size);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        int retVal = x;

        if (parent[x] != x) {
            parent[x] = find(parent[x]);
            retVal = parent[x];
        }

        return retVal;
    }
    void join(int u, int v) {
        //
        parent[find(v)] = find(u);
    }
};
class Solution {
   public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<int> retVal;

        DSU dsu(c + 1);
        for (auto& p : connections) {
            dsu.join(p[0], p[1]);
        }

        vector<bool> online(c + 1, true);
        vector<int> offlineCounts(c + 1, 0);
        for (auto& q : queries) {
            int op = q[0], x = q[1];
            if (op == 2) {
                online[x] = false;
                offlineCounts[x]++;
            }
        }

        unordered_map<int, int> minimumOnlineStations;
        for (int i = 1; i <= c; i++) {
            int root = dsu.find(i);
            if (!minimumOnlineStations.count(root)) {
                minimumOnlineStations[root] = -1;
            }

            int station = minimumOnlineStations[root];
            if (online[i]) {
                if (station == -1 || station > i) {
                    minimumOnlineStations[root] = i;
                }
            }
        }

        for (int i = (int)queries.size() - 1; i >= 0; i--) {
            int op = queries[i][0], x = queries[i][1];
            int root = dsu.find(x);
            int station = minimumOnlineStations[root];

            if (op == 1) {
                if (online[x]) {
                    retVal.push_back(x);
                } else {
                    retVal.push_back(station);
                }
            }

            if (op == 2) {
                if (offlineCounts[x] > 1) {
                    offlineCounts[x]--;
                } else {
                    online[x] = true;
                    if (station == -1 || station > x) {
                        minimumOnlineStations[root] = x;
                    }
                }
            }
        }

        reverse(retVal.begin(), retVal.end());

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class DSU:
    def __init__(self, size: int) -> None:
        self.parent = list(range(size))

    def find(self, x: int) -> int:
        retVal = 0

        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        retVal = self.parent[x]

        return retVal

    def join(self, u: int, v: int) -> None:
        self.parent[self.find(v)] = self.find(u)


class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        retVal = []

        dsu = DSU(c + 1)
        for p in connections:
            dsu.join(p[0], p[1])

        online = [True] * (c + 1)
        offline_counts = [0] * (c + 1)
        for q in queries:
            op, x = q[0], q[1]
            if op == 2:
                online[x] = False
                offline_counts[x] += 1

        minimum_online_stations = {}
        for i in range(1, c + 1):
            root = dsu.find(i)
            if root not in minimum_online_stations:
                minimum_online_stations[root] = -1

            station = minimum_online_stations[root]
            if online[i]:
                if station == -1 or station > i:
                    minimum_online_stations[root] = i

        for i in range(len(queries) - 1, -1, -1):
            op = queries[i][0]
            x = queries[i][1]

            root = dsu.find(x)
            station = minimum_online_stations[root]

            if op == 1:
                if online[x]:
                    retVal.append(x)
                else:
                    retVal.append(station)

            if op == 2:
                if offline_counts[x] > 1:
                    offline_counts[x] -= 1
                else:
                    online[x] = True
                    if station == -1 or station > x:
                        minimum_online_stations[root] = x

        retVal = retVal[::-1]

        return retVal
```

</details>

## [3650. Minimum Cost Path with Edge Reversals](https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/)  1854

- [Official](https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/editorial/)
- [Official](https://leetcode.cn/problems/minimum-cost-path-with-edge-reversals/solutions/3887138/bian-fan-zhuan-de-zui-xiao-lu-jing-zong-5yugt/)

<details><summary>Description</summary>

```text
You are given a directed, weighted graph with n nodes labeled from 0 to n - 1,
and an array edges where edges[i] = [ui, vi, wi] represents a directed edge from node ui to node vi with cost wi.

Each node ui has a switch that can be used at most once: when you arrive at ui and have not yet used its switch,
you may activate it on one of its incoming edges vi → ui reverse that edge to ui → vi and immediately traverse it.

The reversal is only valid for that single move, and using a reversed edge costs 2 * wi.

Return the minimum total cost to travel from node 0 to node n - 1. If it is not possible, return -1.

Example 1:
Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
Output: 5
Explanation:
Use the path 0 → 1 (cost 3).
At node 1 reverse the original edge 3 → 1 into 1 → 3 and traverse it at cost 2 * 1 = 2.
Total cost is 3 + 2 = 5.

Example 2:
Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
Output: 3
Explanation:
No reversal is needed. Take the path 0 → 2 (cost 1), then 2 → 1 (cost 1), then 1 → 3 (cost 1).
Total cost is 1 + 1 + 1 = 3.

Constraints:
2 <= n <= 5 * 10^4
1 <= edges.length <= 10^5
edges[i] = [ui, vi, wi]
0 <= ui, vi <= n - 1
1 <= wi <= 1000
```

<details><summary>Hint</summary>

```text
1. Do we only need to reverse at most one edge for each node?
   If so, can we add reversed edges for each node and use the one that helps in the shortest path?
2. Add reverse edges: {u, v, w} -> {v, u, 2 * w}, and use Dijkstra.
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#define MIN_QUEUE_SIZE (64)

typedef struct Element {
    int data[2];
} Element;
typedef bool (*compare)(const void*, const void*);
typedef struct PriorityQueue {
    Element* arr;
    int capacity;
    int queueSize;
    compare lessFunc;
} PriorityQueue;
Element* createElement(int x, int y) {
    Element* pObj = NULL;

    pObj = (Element*)malloc(sizeof(Element));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->data[0] = x;
    pObj->data[1] = y;

    return pObj;
}
static bool less(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = e1->data[0] > e2->data[0];

    return retVal;
}
#if 0
static bool greater(const void* a, const void* b) {
    bool retVal = false;

    Element* e1 = (Element*)a;
    Element* e2 = (Element*)b;
    retVal = e1->data[0] < e2->data[0];

    return retVal;
}
#endif
static void memswap(void* m1, void* m2, size_t size) {
    unsigned char* a = (unsigned char*)m1;
    unsigned char* b = (unsigned char*)m2;
    while (size--) {
        *b ^= *a;
        *a ^= *b;
        *b ^= *a;
        a++;
        b++;
    }
}
static void swap(Element* arr, int i, int j) {
    //
    memswap(&arr[i], &arr[j], sizeof(Element));
}
static void down(Element* arr, int size, int i, compare cmpFunc) {
    for (int k = 2 * i + 1; k < size; k = 2 * k + 1) {
        if (k + 1 < size && cmpFunc(&arr[k], &arr[k + 1])) {
            k++;
        }

        if (cmpFunc(&arr[k], &arr[(k - 1) / 2])) {
            break;
        }

        swap(arr, k, (k - 1) / 2);
    }
}
PriorityQueue* createPriorityQueue(compare cmpFunc) {
    PriorityQueue* pObj = NULL;

    pObj = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->capacity = MIN_QUEUE_SIZE;
    pObj->arr = (Element*)malloc(sizeof(Element) * pObj->capacity);
    pObj->queueSize = 0;
    pObj->lessFunc = cmpFunc;

    return pObj;
}
void heapfiy(PriorityQueue* obj) {
    for (int i = obj->queueSize / 2 - 1; i >= 0; i--) {
        down(obj->arr, obj->queueSize, i, obj->lessFunc);
    }
}
void enQueue(PriorityQueue* obj, Element* e) {
    // we need to alloc more space, just twice space size
    if (obj->queueSize == obj->capacity) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, sizeof(Element) * obj->capacity);
    }
    memcpy(&obj->arr[obj->queueSize], e, sizeof(Element));

    for (int i = obj->queueSize; i > 0 && obj->lessFunc(&obj->arr[(i - 1) / 2], &obj->arr[i]); i = (i - 1) / 2) {
        swap(obj->arr, i, (i - 1) / 2);
    }
    obj->queueSize++;
}
Element* deQueue(PriorityQueue* obj) {
    swap(obj->arr, 0, obj->queueSize - 1);
    down(obj->arr, obj->queueSize - 1, 0, obj->lessFunc);
    Element* e = &obj->arr[obj->queueSize - 1];
    obj->queueSize--;

    return e;
}
bool isEmpty(const PriorityQueue* obj) {
    bool retVal = (obj->queueSize == 0);

    return retVal;
}
Element* front(const PriorityQueue* obj) {
    Element* pRetVal = NULL;

    if (obj->queueSize != 0) {
        pRetVal = &obj->arr[0];
    }

    return pRetVal;
}
void clear(PriorityQueue* obj) {
    //
    obj->queueSize = 0;
}
int size(const PriorityQueue* obj) {
    int retVal = obj->queueSize;

    return retVal;
}
void freeQueue(PriorityQueue* obj) {
    free(obj->arr);
    obj->arr = NULL;
    free(obj);
    obj = NULL;
}

#endif  // PRIORITYQUEUE_H
#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjNode {
    int vertex;
    int weight;
    struct AdjNode* next;
} AdjNode;
typedef struct {
    AdjNode** lists;
    int n;
} Graph;
AdjNode* createAdjNode(int vertex, int weight) {
    AdjNode* pObj = NULL;

    pObj = (AdjNode*)malloc(sizeof(AdjNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->vertex = vertex;
    pObj->weight = weight;
    pObj->next = NULL;

    return pObj;
}
Graph* createGraph(int n) {
    Graph* pObj = NULL;

    pObj = (Graph*)malloc(sizeof(Graph));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->n = n;
    pObj->lists = (AdjNode**)malloc(n * sizeof(AdjNode*));
    for (int i = 0; i < n; i++) {
        pObj->lists[i] = NULL;
    }

    return pObj;
}
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjNode* newNode = createAdjNode(dest, weight);
    if (newNode == NULL) {
        perror("createAdjNode");
        return;
    }
    newNode->next = graph->lists[src];
    graph->lists[src] = newNode;

    AdjNode* reverseNode = createAdjNode(src, 2 * weight);
    if (reverseNode == NULL) {
        perror("createAdjNode");
        return;
    }
    reverseNode->next = graph->lists[dest];
    graph->lists[dest] = reverseNode;
}
void freeGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    AdjNode *current, *temp;
    for (int i = 0; i < graph->n; i++) {
        current = graph->lists[i];
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
            temp = NULL;
        }
    }
    free(graph->lists);
    graph->lists = NULL;
    free(graph);
    graph = NULL;
}

#endif  // GRAPH_H
int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = -1;

    Graph* adjacency = createGraph(n);
    int src, dest, weight;
    for (int i = 0; i < edgesSize; i++) {
        src = edges[i][0];
        dest = edges[i][1];
        weight = edges[i][2];
        addEdge(adjacency, src, dest, weight);
    }

    int* distance = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
    }
    distance[0] = 0;

    bool* visited = (bool*)calloc(n, sizeof(bool));

    PriorityQueue* heap = createPriorityQueue(less);
    Element startElem;
    startElem.data[0] = 0;
    startElem.data[1] = 0;
    enQueue(heap, &startElem);

    Element *current, newElem;
    int currentDistance, x, y, w;
    while (isEmpty(heap) != true) {
        current = front(heap);
        currentDistance = current->data[0];
        x = current->data[1];
        deQueue(heap);

        if (x == n - 1) {
            retVal = currentDistance;
            break;
        }

        if (visited[x] == true) {
            continue;
        }
        visited[x] = true;

        for (AdjNode* neighbor = adjacency->lists[x]; neighbor != NULL; neighbor = neighbor->next) {
            y = neighbor->vertex;
            w = neighbor->weight;
            if (currentDistance + w < distance[y]) {
                distance[y] = currentDistance + w;

                newElem.data[0] = distance[y];
                newElem.data[1] = y;
                enQueue(heap, &newElem);
            }
        }
    }

    //
    free(distance);
    free(visited);
    freeQueue(heap);
    freeGraph(adjacency);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int minCost(int n, vector<vector<int>>& edges) {
        int retVal = -1;

        vector<vector<pair<int, int>>> adjacency(n);
        for (auto& e : edges) {
            int x = e[0];
            int y = e[1];
            int w = e[2];
            adjacency[x].emplace_back(y, w);
            adjacency[y].emplace_back(x, 2 * w);
        }

        vector<int> distance(n, numeric_limits<int>::max());
        distance[0] = 0;
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        heap.emplace(0, 0);
        while (heap.empty() == false) {
            int x = heap.top().second;
            heap.pop();
            if (x == n - 1) {
                retVal = distance[x];
                break;
            }

            if (visited[x] == true) {
                continue;
            }
            visited[x] = true;

            for (auto& [y, w] : adjacency[x]) {
                if (distance[x] + w < distance[y]) {
                    distance[y] = distance[x] + w;
                    heap.emplace(distance[y], y);
                }
            }
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        retVal = -1

        adjacency = [[] for _ in range(n)]
        for x, y, w in edges:
            adjacency[x].append((y, w))
            adjacency[y].append((x, 2 * w))

        distance = [float('inf')] * n
        distance[0] = 0
        visited = [False] * n
        heap = [(0, 0)]  # (Distance, Node)
        while heap:
            currentDistance, x = heappop(heap)
            if x == n - 1:
                retVal = currentDistance
                break

            if visited[x] == True:
                continue
            visited[x] = True

            for y, w in adjacency[x]:
                newDistance = currentDistance + w
                if newDistance < distance[y]:
                    distance[y] = newDistance
                    heappush(heap, (newDistance, y))

        return retVal
```

</details>
