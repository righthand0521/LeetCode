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

## [3719. Longest Balanced Subarray I](https://leetcode.com/problems/longest-balanced-subarray-i/)  1467

- [Official](https://leetcode.com/problems/longest-balanced-subarray-i/editorial/)
- [Official](https://leetcode.cn/problems/longest-balanced-subarray-i/solutions/3896554/zui-chang-ping-heng-zi-shu-zu-i-by-leetc-7mlh/)

<details><summary>Description</summary>

```text
You are given an integer array nums.

A subarray is called balanced
if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

Return the length of the longest balanced subarray.

Example 1:
Input: nums = [2,5,4,3]
Output: 4
Explanation:
The longest balanced subarray is [2, 5, 4, 3].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.

Example 2:
Input: nums = [3,2,2,5,4]
Output: 5
Explanation:
The longest balanced subarray is [3, 2, 2, 5, 4].
It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.

Example 3:
Input: nums = [1,2,3,2]
Output: 3
Explanation:
The longest balanced subarray is [2, 3, 2].
It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.

Constraints:
1 <= nums.length <= 1500
1 <= nums[i] <= 10^5
```

<details><summary>Hint</summary>

```text
1. Use brute force
2. Try every subarray and use a map/set data structure to track the distinct even and odd numbers
```

</details>

</details>

<details><summary>C</summary>

```c
#ifndef List_H
#define List_H

typedef struct {
    struct ListNode* head;
    int size;
} List;
List* listCreate() {
    List* pObj = NULL;

    pObj = (List*)malloc(sizeof(List));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->head = NULL;
    pObj->size = 0;

    return pObj;
}
void listPush(List* list, int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (node == NULL) {
        perror("malloc");
        return;
    }
    node->val = val;
    node->next = list->head;
    list->head = node;
    list->size++;
}
void listPop(List* list) {
    if (list->head == NULL) {
        return;
    }
    struct ListNode* temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->size--;
}
int listAt(List* list, int index) {
    int retVal = -1;

    struct ListNode* cur = list->head;
    for (int i = 0; i < index && cur != NULL; i++) {
        cur = cur->next;
    }
    if (cur != NULL) {
        retVal = cur->val;
    }

    return retVal;
}
void listReverse(List* list) {
    struct ListNode* prev = NULL;
    struct ListNode* cur = list->head;
    struct ListNode* next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    list->head = prev;
}
void listFree(List* list) {
    while (list->head != NULL) {
        listPop(list);
    }
    free(list);
}

#endif  // List_H
#ifndef Hash_H
#define Hash_H

typedef struct {
    int key;
    List* val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** obj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** obj, int key, List* val) {
    bool retVal = false;

    if (hashFindItem(obj, key)) {
        return retVal;
    }

    HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
    if (pEntry == NULL) {
        perror("malloc");
        return retVal;
    }
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    retVal = true;

    return retVal;
}
List* hashGetItem(HashItem** obj, int key) {
    List* pRetVal = NULL;

    HashItem* pEntry = hashFindItem(obj, key);
    if (pEntry == NULL) {
        pRetVal = listCreate();
        hashAddItem(obj, key, pRetVal);
        return pRetVal;
    }
    pRetVal = pEntry->val;

    return pRetVal;
}
void hashFree(HashItem** obj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        listFree(curr->val);
        free(curr);
    }
}
void hashIterate(HashItem** obj, void (*callback)(HashItem* item)) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        //
        callback(curr);
    }
}
void reverseList(HashItem* item) {
    //
    listReverse(item->val);
}

#endif  // Hash_H
#ifndef LazyTag_H
#define LazyTag_H

typedef struct {
    int toAdd;
} LazyTag;
void lazyTagAdd(LazyTag* tag, LazyTag* other) {
    //
    tag->toAdd += other->toAdd;
}
bool lazyTagHasTag(LazyTag* tag) {
    bool retVal = (tag->toAdd != 0);

    return retVal;
}
void lazyTagClear(LazyTag* tag) {
    //
    tag->toAdd = 0;
}

#endif  // LazyTag_H
#ifndef SegmentTree_H
#define SegmentTree_H

typedef struct {
    int minValue;
    int maxValue;
    LazyTag lazyTag;
} SegmentTreeNode;
typedef struct {
    int n;
    SegmentTreeNode* tree;
} SegmentTree;
void segmentTreeApplyTag(SegmentTree* seg, int i, LazyTag* tag) {
    seg->tree[i].minValue += tag->toAdd;
    seg->tree[i].maxValue += tag->toAdd;
    lazyTagAdd(&seg->tree[i].lazyTag, tag);
}
void segmentTreePushdown(SegmentTree* seg, int i) {
    if (lazyTagHasTag(&seg->tree[i].lazyTag)) {
        LazyTag tag = {seg->tree[i].lazyTag.toAdd};
        segmentTreeApplyTag(seg, i << 1, &tag);
        segmentTreeApplyTag(seg, (i << 1) | 1, &tag);
        lazyTagClear(&seg->tree[i].lazyTag);
    }
}
void segmentTreePushup(SegmentTree* seg, int i) {
    seg->tree[i].minValue = fmin(seg->tree[i << 1].minValue, seg->tree[(i << 1) | 1].minValue);
    seg->tree[i].maxValue = fmax(seg->tree[i << 1].maxValue, seg->tree[(i << 1) | 1].maxValue);
}
void segmentTreeBuild(SegmentTree* seg, int* data, int l, int r, int i) {
    if (l == r) {
        seg->tree[i].minValue = seg->tree[i].maxValue = data[l - 1];
        return;
    }

    int mid = l + ((r - l) >> 1);
    segmentTreeBuild(seg, data, l, mid, i << 1);
    segmentTreeBuild(seg, data, mid + 1, r, (i << 1) | 1);
    segmentTreePushup(seg, i);
}
void segmentTreeUpdate(SegmentTree* seg, int targetL, int targetR, LazyTag* tag, int l, int r, int i) {
    if ((targetL <= l) && (r <= targetR)) {
        segmentTreeApplyTag(seg, i, tag);
        return;
    }

    segmentTreePushdown(seg, i);
    int mid = l + ((r - l) >> 1);
    if (targetL <= mid) {
        segmentTreeUpdate(seg, targetL, targetR, tag, l, mid, i << 1);
    }
    if (targetR > mid) {
        segmentTreeUpdate(seg, targetL, targetR, tag, mid + 1, r, (i << 1) | 1);
    }
    segmentTreePushup(seg, i);
}
int segmentTreeFind(SegmentTree* seg, int targetL, int targetR, int val, int l, int r, int i) {
    int retVal = -1;

    if ((seg->tree[i].minValue > val) || (seg->tree[i].maxValue < val)) {
        return retVal;
    }

    if (l == r) {
        retVal = l;
        return retVal;
    }

    segmentTreePushdown(seg, i);

    int mid = l + ((r - l) >> 1);
    if (targetR >= mid + 1) {
        retVal = segmentTreeFind(seg, targetL, targetR, val, mid + 1, r, (i << 1) | 1);
        if (retVal != -1) {
            return retVal;
        }
    }

    if (targetL <= mid) {
        retVal = segmentTreeFind(seg, targetL, targetR, val, l, mid, i << 1);
        return retVal;
    }

    return retVal;
}
SegmentTree* segmentTreeCreate(int* data, int n) {
    SegmentTree* pObj = NULL;

    pObj = (SegmentTree*)malloc(sizeof(SegmentTree));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->n = n;
    pObj->tree = (SegmentTreeNode*)calloc(n * 4 + 1, sizeof(SegmentTreeNode));
    segmentTreeBuild(pObj, data, 1, n, 1);

    return pObj;
}
void segmentTreeAdd(SegmentTree* seg, int l, int r, int val) {
    LazyTag tag = {val};
    segmentTreeUpdate(seg, l, r, &tag, 1, seg->n, 1);
}
int segmentTreeFindLast(SegmentTree* seg, int start, int val) {
    int retVal = -1;

    if (start <= seg->n) {
        retVal = segmentTreeFind(seg, start, seg->n, val, 1, seg->n, 1);
    }

    return retVal;
}
void segmentTreeFree(SegmentTree* seg) {
    free(seg->tree);
    free(seg);
}

#endif  // SegmentTree_H
int sgn(int x) {
    int retVal = -1;

    if (x % 2 == 0) {
        retVal = 1;
    }

    return retVal;
}
int longestBalanced(int* nums, int numsSize) {
    int retVal = 0;

    int prefixSum[numsSize];
    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[0] = sgn(nums[0]);

    HashItem* occurrences = NULL;
    List* list0 = hashGetItem(&occurrences, nums[0]);
    listPush(list0, 1);
    for (int i = 1; i < numsSize; i++) {
        prefixSum[i] = prefixSum[i - 1];
        List* occ = hashGetItem(&occurrences, nums[i]);
        if (occ->size == 0) {
            prefixSum[i] += sgn(nums[i]);
        }
        listPush(occ, i + 1);
    }
    hashIterate(&occurrences, reverseList);

    SegmentTree* seg = segmentTreeCreate(prefixSum, numsSize);
    for (int i = 0; i < numsSize; i++) {
        int findResult = segmentTreeFindLast(seg, i + retVal, 0);
        int newLen = findResult - i;
        if (newLen > retVal) {
            retVal = newLen;
        }

        int nextPos = numsSize + 1;
        List* occ = hashGetItem(&occurrences, nums[i]);
        listPop(occ);
        if (occ->size > 0) {
            nextPos = listAt(occ, 0);
        }
        segmentTreeAdd(seg, i + 1, nextPos - 1, -sgn(nums[i]));
    }

    //
    segmentTreeFree(seg);
    hashFree(&occurrences);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
struct LazyTag {
    int to_add = 0;

    LazyTag& operator+=(const LazyTag& other) {
        this->to_add += other.to_add;

        return *this;
    }
    bool has_tag() const {
        bool retVal = (to_add != 0);

        return retVal;
    }
    void clear() {
        //
        to_add = 0;
    }
};
struct SegmentTreeNode {
    int min_value = 0;
    int max_value = 0;
    // int data = 0; // only leaf nodes are used, this question does not require it.
    LazyTag lazy_tag;
};
class SegmentTree {
   public:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTree(const vector<int>& data) : n(data.size()) {
        tree.resize(n * 4 + 1);
        build(data, 1, n, 1);
    }
    void add(int l, int r, int val) {
        LazyTag tag{val};
        update(l, r, tag, 1, n, 1);
    }
    int find_last(int start, int val) {
        int retVal = -1;

        if (start <= n) {
            retVal = find(start, n, val, 1, n, 1);
        }

        return retVal;
    }

   private:
    inline void apply_tag(int i, const LazyTag& tag) {
        tree[i].min_value += tag.to_add;
        tree[i].max_value += tag.to_add;
        tree[i].lazy_tag += tag;
    }
    inline void pushdown(int i) {
        if (tree[i].lazy_tag.has_tag() == true) {
            LazyTag tag = tree[i].lazy_tag;
            apply_tag(i << 1, tag);
            apply_tag(i << 1 | 1, tag);
            tree[i].lazy_tag.clear();
        }
    }
    inline void pushup(int i) {
        tree[i].min_value = std::min(tree[i << 1].min_value, tree[i << 1 | 1].min_value);
        tree[i].max_value = std::max(tree[i << 1].max_value, tree[i << 1 | 1].max_value);
    }
    void build(const vector<int>& data, int l, int r, int i) {
        if (l == r) {
            tree[i].min_value = tree[i].max_value = data[l - 1];
            return;
        }
        int mid = l + ((r - l) >> 1);
        build(data, l, mid, i << 1);
        build(data, mid + 1, r, i << 1 | 1);
        pushup(i);
    }
    void update(int target_l, int target_r, const LazyTag& tag, int l, int r, int i) {
        if ((target_l <= l) && (r <= target_r)) {
            apply_tag(i, tag);
            return;
        }
        pushdown(i);

        int mid = l + ((r - l) >> 1);
        if (target_l <= mid) {
            update(target_l, target_r, tag, l, mid, i << 1);
        }
        if (target_r > mid) {
            update(target_l, target_r, tag, mid + 1, r, i << 1 | 1);
        }
        pushup(i);
    }
    int find(int target_l, int target_r, int val, int l, int r, int i) {
        int retVal = -1;

        if (tree[i].min_value > val || tree[i].max_value < val) {
            return retVal;
        }

        // according to the Intermediate Value Theorem, there must be a solution within this interval.
        if (l == r) {
            retVal = l;
            return retVal;
        }
        pushdown(i);

        int mid = l + ((r - l) >> 1);

        // target_l is definitely less than or equal to r (=n)
        if (target_r >= mid + 1) {
            retVal = find(target_l, target_r, val, mid + 1, r, i << 1 | 1);
            if (retVal != -1) {
                return retVal;
            }
        }

        if (l <= target_r && mid >= target_l) {
            retVal = find(target_l, target_r, val, l, mid, i << 1);
            return retVal;
        }

        return retVal;
    }
};
class Solution {
   private:
    int sgn(int x) {
        int retVal = -1;

        if (x % 2 == 0) {
            retVal = 1;
        }

        return retVal;
    }

   public:
    int longestBalanced(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();

        map<int, queue<int>> occurrences;
        occurrences[nums[0]].push(1);

        vector<int> prefix_sum(numsSize, 0);
        prefix_sum[0] = sgn(nums[0]);
        for (int i = 1; i < numsSize; i++) {
            prefix_sum[i] = prefix_sum[i - 1];
            auto& occ = occurrences[nums[i]];
            if (occ.empty() == true) {
                prefix_sum[i] += sgn(nums[i]);
            }
            occ.push(i + 1);
        }

        SegmentTree seg(prefix_sum);
        for (int i = 0; i < numsSize; i++) {
            retVal = max(retVal, seg.find_last(i + retVal, 0) - i);

            auto next_pos = numsSize + 1;
            occurrences[nums[i]].pop();
            if (occurrences[nums[i]].empty() == false) {
                next_pos = occurrences[nums[i]].front();
            }

            seg.add(i + 1, next_pos - 1, -sgn(nums[i]));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class LazyTag:
    def __init__(self) -> None:
        self.to_add = 0

    def add(self, other) -> "LazyTag":
        retVal = None

        self.to_add += other.to_add
        retVal = self

        return retVal

    def has_tag(self) -> bool:
        retVal = (self.to_add != 0)

        return retVal

    def clear(self) -> None:
        self.to_add = 0


class SegmentTreeNode:
    def __init__(self) -> None:
        self.min_value = 0
        self.max_value = 0
        self.lazy_tag = LazyTag()


class SegmentTree:
    def __init__(self, data) -> None:
        self.n = len(data)
        self.tree = [SegmentTreeNode() for _ in range(self.n * 4 + 1)]
        self._build(data, 1, self.n, 1)

    def add(self, l, r, val) -> None:
        tag = LazyTag()
        tag.to_add = val
        self._update(l, r, tag, 1, self.n, 1)

    def find_last(self, start, val) -> int:
        retVal = -1

        if start <= self.n:
            retVal = self._find(start, self.n, val, 1, self.n, 1)

        return retVal

    def _apply_tag(self, i, tag) -> None:
        self.tree[i].min_value += tag.to_add
        self.tree[i].max_value += tag.to_add
        self.tree[i].lazy_tag.add(tag)

    def _pushdown(self, i) -> None:
        if self.tree[i].lazy_tag.has_tag() == False:
            return

        tag = LazyTag()
        tag.to_add = self.tree[i].lazy_tag.to_add
        self._apply_tag(i << 1, tag)
        self._apply_tag((i << 1) | 1, tag)
        self.tree[i].lazy_tag.clear()

    def _pushup(self, i) -> None:
        self.tree[i].min_value = min(self.tree[i << 1].min_value, self.tree[(i << 1) | 1].min_value)
        self.tree[i].max_value = max(self.tree[i << 1].max_value, self.tree[(i << 1) | 1].max_value)

    def _build(self, data, l, r, i) -> None:
        if l == r:
            self.tree[i].min_value = data[l - 1]
            self.tree[i].max_value = data[l - 1]
            return

        mid = l + ((r - l) >> 1)
        self._build(data, l, mid, i << 1)
        self._build(data, mid + 1, r, (i << 1) | 1)
        self._pushup(i)

    def _update(self, target_l, target_r, tag, l, r, i) -> None:
        if (target_l <= l) and (r <= target_r):
            self._apply_tag(i, tag)
            return

        self._pushdown(i)
        mid = l + ((r - l) >> 1)
        if target_l <= mid:
            self._update(target_l, target_r, tag, l, mid, i << 1)
        if target_r > mid:
            self._update(target_l, target_r, tag, mid + 1, r, (i << 1) | 1)
        self._pushup(i)

    def _find(self, target_l, target_r, val, l, r, i) -> int:
        retVal = -1

        if (self.tree[i].min_value > val) or (self.tree[i].max_value < val):
            return retVal

        if l == r:
            retVal = l
            return retVal

        self._pushdown(i)
        mid = l + ((r - l) >> 1)
        if target_r >= mid + 1:
            retVal = self._find(target_l, target_r, val, mid + 1, r, (i << 1) | 1)
            if retVal != -1:
                return retVal

        if (l <= target_r) and (mid >= target_l):
            retVal = self._find(target_l, target_r, val, l, mid, i << 1)
            return retVal

        return retVal


class Solution:
    def sgn(self, x: int) -> int:
        retVal = -1

        if x % 2 == 0:
            retVal = 1

        return retVal

    def longestBalanced(self, nums: List[int]) -> int:
        retVal = 0

        numsSize = len(nums)

        occurrences = defaultdict(deque)
        occurrences[nums[0]].append(1)

        prefix_sum = [0] * numsSize
        prefix_sum[0] = self.sgn(nums[0])
        for i in range(1, numsSize):
            prefix_sum[i] = prefix_sum[i - 1]
            occ = occurrences[nums[i]]
            if not occ:
                prefix_sum[i] += self.sgn(nums[i])
            occ.append(i + 1)

        seg = SegmentTree(prefix_sum)
        for i in range(numsSize):
            retVal = max(retVal, seg.find_last(i + retVal, 0) - i)
            next_pos = numsSize + 1
            occurrences[nums[i]].popleft()
            if occurrences[nums[i]]:
                next_pos = occurrences[nums[i]][0]
            seg.add(i + 1, next_pos - 1, -self.sgn(nums[i]))

        return retVal
```

</details>
