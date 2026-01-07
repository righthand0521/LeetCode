# Tree

## [3372. Maximize the Number of Target Nodes After Connecting Trees I](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/)  1926

- [Official](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/solutions/3677383/lian-jie-liang-ke-shu-hou-zui-da-mu-biao-730m/)

<details><summary>Description</summary>

```text
There exist two undirected trees with n and m nodes,
with distinct labels in ranges [0, n - 1] and [0, m - 1], respectively.

You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively,
where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree
and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
You are also given an integer k.

Node u is target to node v if the number of edges on the path from u to v is less than or equal to k.
Note that a node is always target to itself.

Return an array of n integers answer,
where answer[i] is the maximum possible number of nodes target to node i of the first tree
if you have to connect one node from the first tree to another node in the second tree.

Note that queries are independent from each other.
That is, for every query you will remove the added edge before proceeding to the next query.

Example 1:
Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
Output: [9,7,9,8,8]
Explanation:
For i = 0, connect node 0 from the first tree to node 0 from the second tree.
For i = 1, connect node 1 from the first tree to node 0 from the second tree.
For i = 2, connect node 2 from the first tree to node 4 from the second tree.
For i = 3, connect node 3 from the first tree to node 4 from the second tree.
For i = 4, connect node 4 from the first tree to node 4 from the second tree.

Example 2:
Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
Output: [6,3,3,3,3]
Explanation:
For every i, connect node i of the first tree with any node of the second tree.

Constraints:
2 <= n, m <= 1000
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
0 <= k <= 1000
```

<details><summary>Hint</summary>

```text
1. For each node u in the first tree, find the number of nodes at a distance of at most k from node u.
2. For each node v in the second tree, find the number of nodes at a distance of at most k - 1 from node v.
```

</details>

</details>

<details><summary>C</summary>

```c
int dfs(int node, int parent, int** children, int* childrenColSize, int k) {
    int retVal = 0;

    if (k < 0) {
        return retVal;
    }

    retVal = 1;
    for (int i = 0; i < childrenColSize[node]; i++) {
        int child = children[node][i];
        if (child == parent) {
            continue;
        }
        retVal += dfs(child, node, children, childrenColSize, k - 1);
    }

    return retVal;
}
int* build(int** edges, int edgesSize, int k) {
    int* pRetVal = NULL;

    int n = edgesSize + 1;

    int* childrenColSize = (int*)malloc(n * sizeof(int));
    if (childrenColSize == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(childrenColSize, 0, n * sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        childrenColSize[edges[i][0]]++;
        childrenColSize[edges[i][1]]++;
    }

    int** children = (int**)malloc(n * sizeof(int*));
    if (children == NULL) {
        perror("malloc");
        free(childrenColSize);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        children[i] = (int*)malloc(childrenColSize[i] * sizeof(int));
        childrenColSize[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        children[edges[i][0]][childrenColSize[edges[i][0]]++] = edges[i][1];
        children[edges[i][1]][childrenColSize[edges[i][1]]++] = edges[i][0];
    }

    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        for (int i = 0; i < n; i++) {
            free(children[i]);
        }
        free(children);
        free(childrenColSize);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = dfs(i, -1, children, childrenColSize, k);
    }

    //
    for (int i = 0; i < n; i++) {
        free(children[i]);
    }
    free(children);
    free(childrenColSize);

    return pRetVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize,
                    int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int* count1 = build(edges1, edges1Size, k);
    if (count1 == NULL) {
        perror("build");
        return pRetVal;
    }
    int* count2 = build(edges2, edges2Size, k - 1);
    if (count2 == NULL) {
        perror("build");
        return pRetVal;
    }

    int maxCount = 0;
    for (int i = 0; i < edges2Size + 1; i++) {
        if (count2[i] > maxCount) {
            maxCount = count2[i];
        }
    }

    int n = edges1Size + 1;
    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(count1);
        free(count2);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = count1[i] + maxCount;
    }
    (*returnSize) = n;

    //
    free(count1);
    free(count2);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int dfs(int node, int parent, const vector<vector<int>>& children, int k) {
        int retVal = 0;

        if (k < 0) {
            return retVal;
        }

        retVal = 1;
        for (int child : children[node]) {
            if (child == parent) {
                continue;
            }
            retVal += dfs(child, node, children, k - 1);
        }

        return retVal;
    }
    vector<int> build(const vector<vector<int>>& edges, int k) {
        vector<int> retVal;

        int edgesSize = edges.size() + 1;
        vector<vector<int>> children(edgesSize);
        for (const auto& edge : edges) {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }

        retVal.resize(edgesSize);
        for (int i = 0; i < edgesSize; i++) {
            retVal[i] = dfs(i, -1, children, k);
        }

        return retVal;
    }

   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        vector<int> retVal;

        vector<int> count1 = build(edges1, k);
        vector<int> count2 = build(edges2, k - 1);
        int maxCount2 = *max_element(count2.begin(), count2.end());

        int edges1Size = edges1.size() + 1;
        retVal.resize(edges1Size);
        for (int i = 0; i < edges1Size; i++) {
            retVal[i] = count1[i] + maxCount2;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dfs(self, node: int, parent: int, children: List[List[int]], k: int) -> int:
        retVal = 0

        if k < 0:
            return retVal

        retVal = 1
        for child in children[node]:
            if child == parent:
                continue
            retVal += self.dfs(child, node, children, k - 1)

        return retVal

    def build(self, edges: List[List[int]], k: int) -> List[int]:
        retVal = []

        edgesSize = len(edges) + 1
        children = [[] for _ in range(edgesSize)]
        for u, v in edges:
            children[u].append(v)
            children[v].append(u)

        retVal = [0] * edgesSize
        for i in range(edgesSize):
            retVal[i] = self.dfs(i, -1, children, k)

        return retVal

    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]], k: int) -> List[int]:
        retVal = []

        count1 = self.build(edges1, k)
        count2 = self.build(edges2, k - 1)
        maxCount2 = max(count2)

        edges1Size = len(edges1) + 1
        for i in range(edges1Size):
            retVal.append(count1[i] + maxCount2)

        return retVal
```

</details>

## [3373. Maximize the Number of Target Nodes After Connecting Trees II](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/)  2161

- [Official](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/editorial/)
- [Official](https://leetcode.cn/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/solutions/3677384/lian-jie-liang-ke-shu-hou-zui-da-mu-biao-0qy7/)

<details><summary>Description</summary>

```text
There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.

You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1,
respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree
and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

Node u is target to node v if the number of edges on the path from u to v is even.
Note that a node is always target to itself.

Return an array of n integers answer,
where answer[i] is the maximum possible number of nodes that are target to node i of the first tree
if you had to connect one node from the first tree to another node in the second tree.

Note that queries are independent from each other.
That is, for every query you will remove the added edge before proceeding to the next query.

Example 1:
Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
Output: [8,7,7,8,8]
Explanation:
For i = 0, connect node 0 from the first tree to node 0 from the second tree.
For i = 1, connect node 1 from the first tree to node 4 from the second tree.
For i = 2, connect node 2 from the first tree to node 7 from the second tree.
For i = 3, connect node 3 from the first tree to node 0 from the second tree.
For i = 4, connect node 4 from the first tree to node 4 from the second tree.

Example 2:
Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]]
Output: [3,6,6,6,6]
Explanation:
For every i, connect node i of the first tree with any node of the second tree.

Constraints:
2 <= n, m <= 10^5
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
1. Compute an array even where even[u] is the number of nodes at an even distance from node u, for every u of the first tree.
2. Compute an array odd where odd[u] is the number of nodes at an odd distance from node u, for every u of the second tree.
3. answer[i] = even[i]+ max(odd[1], odd[2], …, odd[m - 1])
```

</details>

</details>

<details><summary>C</summary>

```c
int dfs(int node, int parent, int depth, int** children, int* childrenColSize, int* color) {
    int retVal = 1 - depth % 2;

    color[node] = depth % 2;
    for (int i = 0; i < childrenColSize[node]; i++) {
        int child = children[node][i];
        if (child == parent) {
            continue;
        }
        retVal += dfs(child, node, depth + 1, children, childrenColSize, color);
    }

    return retVal;
}
int* build(int** edges, int edgesSize, int* color) {
    int* pRetVal = NULL;

    int n = edgesSize + 1;

    int* childrenColSize = (int*)calloc(n, sizeof(int));
    if (childrenColSize == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (int i = 0; i < edgesSize; i++) {
        childrenColSize[edges[i][0]]++;
        childrenColSize[edges[i][1]]++;
    }

    int** children = (int**)malloc(n * sizeof(int*));
    if (children == NULL) {
        perror("malloc");
        free(childrenColSize);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        children[i] = (int*)malloc(childrenColSize[i] * sizeof(int));
        childrenColSize[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        children[u][childrenColSize[u]++] = v;
        children[v][childrenColSize[v]++] = u;
    }
    int res = dfs(0, -1, 0, children, childrenColSize, color);

    pRetVal = (int*)malloc(2 * sizeof(int));
    if (pRetVal != NULL) {
        pRetVal[0] = res;
        pRetVal[1] = n - res;

    } else {
        perror("malloc");
    }

    //
    for (int i = 0; i < n; i++) {
        free(children[i]);
    }
    free(children);
    free(childrenColSize);

    return pRetVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize,
                    int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int n = edges1Size + 1;
    int* color1 = (int*)calloc(n, sizeof(int));
    if (color1 == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int* count1 = build(edges1, edges1Size, color1);
    if (count1 == NULL) {
        perror("build");
        free(color1);
        return pRetVal;
    }

    int m = edges2Size + 1;
    int* color2 = (int*)calloc(m, sizeof(int));
    if (color2 == NULL) {
        perror("calloc");
        free(color1);
        free(count1);
        return pRetVal;
    }
    int* count2 = build(edges2, edges2Size, color2);
    if (count2 == NULL) {
        perror("build");
        free(color1);
        free(count1);
        free(color2);
        return pRetVal;
    }

    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal != NULL) {
        for (int i = 0; i < n; i++) {
            pRetVal[i] = count1[color1[i]] + (count2[0] > count2[1] ? count2[0] : count2[1]);
        }
        (*returnSize) = n;
    } else {
        perror("malloc");
    }

    //
    free(color1);
    free(count1);
    free(color2);
    free(count2);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   private:
    int dfs(int node, int parent, int depth, const vector<vector<int>>& children, vector<int>& color) {
        int retVal = 1 - depth % 2;

        color[node] = depth % 2;
        for (int child : children[node]) {
            if (child == parent) {
                continue;
            }
            retVal += dfs(child, node, depth + 1, children, color);
        }

        return retVal;
    }
    vector<int> build(const vector<vector<int>>& edges, vector<int>& color) {
        vector<int> retVal;

        int edgesSize = edges.size() + 1;
        vector<vector<int>> children(edgesSize);
        for (const auto& edge : edges) {
            children[edge[0]].push_back(edge[1]);
            children[edge[1]].push_back(edge[0]);
        }
        int res = dfs(0, -1, 0, children, color);
        retVal = {res, edgesSize - res};

        return retVal;
    }

   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        vector<int> retVal;

        int edges1Size = edges1.size() + 1;
        vector<int> color1(edges1Size);
        vector<int> count1 = build(edges1, color1);

        int edges2Size = edges2.size() + 1;
        vector<int> color2(edges2Size);
        vector<int> count2 = build(edges2, color2);

        retVal.resize(edges1.size() + 1);
        for (int i = 0; i < edges1Size; i++) {
            retVal[i] = count1[color1[i]] + max(count2[0], count2[1]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def dfs(self, node: int, parent: int, depth: int, children: List[List[int]], color: List[int]) -> int:
        retVal = 1 - depth % 2

        color[node] = depth % 2
        for child in children[node]:
            if child == parent:
                continue
            retVal += self.dfs(child, node, depth + 1, children, color)

        return retVal

    def build(self, edges: List[List[int]], color: List[int]) -> List[int]:
        retVal = []

        edgesSize = len(edges) + 1
        children = [[] for _ in range(edgesSize)]
        for u, v in edges:
            children[u].append(v)
            children[v].append(u)
        ret = self.dfs(0, -1, 0, children, color)
        retVal = [ret, edgesSize - ret]

        return retVal

    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        retVal = []

        edges1Size = len(edges1) + 1
        color1 = [0] * edges1Size
        count1 = self.build(edges1, color1)

        edges2Size = len(edges2) + 1
        color2 = [0] * edges2Size
        count2 = self.build(edges2, color2)

        retVal = [0] * edges1Size
        for i in range(edges1Size):
            retVal[i] = count1[color1[i]] + max(count2[0], count2[1])

        return retVal
```

</details>
