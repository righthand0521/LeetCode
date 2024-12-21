# Tree

## [1026. Maximum Difference Between Node and Ancestor](https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/)  1446

- [Official](https://leetcode.cn/problems/maximum-difference-between-node-and-ancestor/solutions/2231286/jie-dian-yu-qi-zu-xian-zhi-jian-de-zui-d-2ykj/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b
where v = |a.val - b.val| and a is an ancestor of b.

A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.

Example 1:
      8
   /     \
  3       10
 / \        \
1   6        14
   / \      /
  4   7   13
Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation: We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

Example 2:
1
 \
  2
   \
    0
   /
  3
Input: root = [1,null,2,null,0,3]
Output: 3

Constraints:
The number of nodes in the tree is in the range [2, 5000].
0 <= Node.val <= 10^5
```

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int dfs(struct TreeNode* root, int maxAncestor, int minAncestor) {
    int retVal = maxAncestor - minAncestor;

    if (root == NULL) {
        return retVal;
    }

    maxAncestor = fmax(root->val, maxAncestor);
    minAncestor = fmin(root->val, minAncestor);
    int left = dfs(root->left, maxAncestor, minAncestor);
    int right = dfs(root->right, maxAncestor, minAncestor);
    retVal = fmax(left, right);

    return retVal;
}
int maxAncestorDiff(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    retVal = dfs(root, root->val, root->val);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    int dfs(TreeNode* root, int maxAncestor, int minAncestor) {
        int retVal = maxAncestor - minAncestor;

        if (root == nullptr) {
            return retVal;
        }

        maxAncestor = max(root->val, maxAncestor);
        minAncestor = min(root->val, minAncestor);
        int left = dfs(root->left, maxAncestor, minAncestor);
        int right = dfs(root->right, maxAncestor, minAncestor);
        retVal = max(left, right);

        return retVal;
    }
    int maxAncestorDiff(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = dfs(root, root->val, root->val);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def dfs(self, root: Optional[TreeNode], maxAncestor: int, minAncestor: int) -> int:
        retVal = maxAncestor - minAncestor

        if root is None:
            return retVal

        maxAncestor = max(root.val, maxAncestor)
        minAncestor = min(root.val, minAncestor)
        left = self.dfs(root.left, maxAncestor, minAncestor)
        right = self.dfs(root.right, maxAncestor, minAncestor)
        retVal = max(left, right)

        return retVal

    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root is None:
            return retVal
        retVal = self.dfs(root, root.val, root.val)

        return retVal
```

</details>

## [1038. Binary Search Tree to Greater Sum Tree](https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/)  1374

- [Official](https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/editorial/)
- [Official](https://leetcode.cn/problems/binary-search-tree-to-greater-sum-tree/solutions/421601/cong-er-cha-sou-suo-shu-dao-geng-da-he-shu-by-leet/)

<details><summary>Description</summary>

```text
Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST
is changed to the original key plus the sum of all keys greater than the original key in BST.

As a reminder, a binary search tree is a tree that satisfies these constraints:
- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

Example 1:
      4
   /     \
  1       6
 / \     / \
0   2   5   7
     \       \
      3       8
Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]

Example 2:
Input: root = [0,null,1]
Output: [1,null,1]

Constraints:
The number of nodes in the tree is in the range [1, 100].
0 <= Node.val <= 100
All the values in the tree are unique.

Note: This question is the same as 538: https://leetcode.com/problems/convert-bst-to-greater-tree/
```

<details><summary>Hint</summary>

```text
1. What traversal method organizes all nodes in sorted order?
```

</details>

</details>

<details><summary>C</summary>

```c
void plusTraversal(struct TreeNode* root, int* addValue) {
    if (root == NULL) {
        return;
    }

    plusTraversal(root->right, addValue);
    root->val += (*addValue);
    (*addValue) = root->val;
    plusTraversal(root->left, addValue);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* bstToGst(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }
    int addValue = 0;
    plusTraversal(pRetVal, &addValue);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    int addValue = 0;
    void plusTraversal(TreeNode *root) {
        if (root == nullptr) {
            return;
        }

        plusTraversal(root->right);
        root->val += addValue;
        addValue = root->val;
        plusTraversal(root->left);
    }

   public:
    TreeNode *bstToGst(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        addValue = 0;
        plusTraversal(pRetVal);

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self) -> None:
        self.addValue = 0

    def plusTraversal(self, root: TreeNode) -> None:
        if root is None:
            return

        self.plusTraversal(root.right)
        root.val += self.addValue
        self.addValue = root.val
        self.plusTraversal(root.left)

    def bstToGst(self, root: TreeNode) -> TreeNode:
        retVal = root

        if retVal is None:
            return retVal

        self.addValue = 0
        self.plusTraversal(retVal)

        return retVal
```

</details>

## [1110. Delete Nodes And Return Forest](https://leetcode.com/problems/delete-nodes-and-return-forest/)  1511

- [Official](https://leetcode.com/problems/delete-nodes-and-return-forest/editorial/)
- [Official](https://leetcode.cn/problems/delete-nodes-and-return-forest/solutions/2286145/shan-dian-cheng-lin-by-leetcode-solution-gy95/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

Example 1:
Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Example 2:
Input: root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]

Constraints:
The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.
```

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    //
    if (root == NULL) {
        return pRetVal;
    }

    //
    int maxReturnSize = 1000 + 1;  // The number of nodes in the given tree is at most 1000.
    pRetVal = (struct TreeNode**)malloc(maxReturnSize * sizeof(struct TreeNode*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    //
    int toDeleteSetSize = 1000 + 1;  // to_delete contains distinct values between 1 and 1000.
    int toDeleteSet[toDeleteSetSize];
    memset(toDeleteSet, 0, sizeof(toDeleteSet));
    int i;
    for (i = 0; i < to_deleteSize; ++i) {
        toDeleteSet[to_delete[i]] = 1;
    }

    //
    int nodesQueueSize = 1000 + 1;  // The number of nodes in the given tree is at most 1000.
    int nodesQueueHead = 0;
    int nodesQueueTail = 0;
    struct TreeNode* nodesQueue[nodesQueueSize];
    memset(nodesQueue, 0, sizeof(nodesQueue));
    nodesQueue[nodesQueueTail++] = root;

    //
    struct TreeNode* currentNode;
    while (nodesQueueHead < nodesQueueTail) {
        currentNode = nodesQueue[nodesQueueHead++];

        if (currentNode->left != NULL) {
            nodesQueue[nodesQueueTail++] = currentNode->left;
            // Disconnect the left child if it needs to be deleted
            if (toDeleteSet[currentNode->left->val] == 1) {
                currentNode->left = NULL;
            }
        }

        if (currentNode->right != NULL) {
            nodesQueue[nodesQueueTail++] = currentNode->right;
            // Disconnect the right child if it needs to be deleted
            if (toDeleteSet[currentNode->right->val] == 1) {
                currentNode->right = NULL;
            }
        }

        // If the current node needs to be deleted, add its non-null children to the forest
        if (toDeleteSet[currentNode->val] == 1) {
            if (currentNode->left != NULL) {
                pRetVal[(*returnSize)] = currentNode->left;
                (*returnSize) += 1;
            }
            if (currentNode->right != NULL) {
                pRetVal[(*returnSize)] = currentNode->right;
                (*returnSize) += 1;
            }

            if (currentNode != root) {
                free(currentNode);
                currentNode = NULL;
            }
        }
    }

    // Ensure the root is added to the forest if it is not to be deleted
    if (toDeleteSet[root->val] != 1) {
        pRetVal[(*returnSize)] = root;
        (*returnSize) += 1;
    } else {
        free(root);
        root = NULL;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> retVal;

        if (root == nullptr) {
            return retVal;
        }

        unordered_set<int> toDeleteSet(to_delete.begin(), to_delete.end());
        queue<TreeNode*> nodesQueue;
        nodesQueue.push(root);
        while (nodesQueue.empty() == false) {
            TreeNode* currentNode = nodesQueue.front();
            nodesQueue.pop();

            if (currentNode->left) {
                nodesQueue.push(currentNode->left);
                // Disconnect the left child if it needs to be deleted
                if (toDeleteSet.find(currentNode->left->val) != toDeleteSet.end()) {
                    currentNode->left = nullptr;
                }
            }

            if (currentNode->right) {
                nodesQueue.push(currentNode->right);
                // Disconnect the right child if it needs to be deleted
                if (toDeleteSet.find(currentNode->right->val) != toDeleteSet.end()) {
                    currentNode->right = nullptr;
                }
            }

            // If the current node needs to be deleted, add its non-null children to the forest
            if (toDeleteSet.find(currentNode->val) != toDeleteSet.end()) {
                if (currentNode->left) {
                    retVal.push_back(currentNode->left);
                }
                if (currentNode->right) {
                    retVal.push_back(currentNode->right);
                }

                if (currentNode != root) {
                    delete currentNode;
                }
            }
        }

        // Ensure the root is added to the forest if it is not to be deleted
        if (toDeleteSet.find(root->val) == toDeleteSet.end()) {
            retVal.push_back(root);
        } else {
            delete root;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        retVal = []

        if not root:
            return retVal

        toDeleteSet = set(to_delete)
        nodesQueue = deque([root])
        while nodesQueue:
            currentNode = nodesQueue.popleft()

            if currentNode.left:
                nodesQueue.append(currentNode.left)
                # Disconnect the left child if it needs to be deleted
                if currentNode.left.val in toDeleteSet:
                    currentNode.left = None

            if currentNode.right:
                nodesQueue.append(currentNode.right)
                # Disconnect the right child if it needs to be deleted
                if currentNode.right.val in toDeleteSet:
                    currentNode.right = None

            # If the current node needs to be deleted, add its non-null children to the forest
            if currentNode.val in toDeleteSet:
                if currentNode.left:
                    retVal.append(currentNode.left)
                if currentNode.right:
                    retVal.append(currentNode.right)

        # Ensure the root is added to the forest if it is not to be deleted
        if root.val not in toDeleteSet:
            retVal.append(root)

        return retVal
```

</details>

## [1145. Binary Tree Coloring Game](https://leetcode.com/problems/binary-tree-coloring-game/)  1741

- [Official](https://leetcode.cn/problems/binary-tree-coloring-game/solutions/2087907/er-cha-shu-zhao-se-you-xi-by-leetcode-so-ruys/)

<details><summary>Description</summary>

```text
Two players play a turn based game on a binary tree.
We are given the root of this binary tree, and the number of nodes n in the tree.
n is odd, and each node has a distinct value from 1 to n.

Initially, the first player names a value x with 1 <= x <= n,
and the second player names a value y with 1 <= y <= n and y != x.
The first player colors the node with value x red, and the second player colors the node with value y blue.

Then, the players take turns starting with the first player.
In each turn, that player chooses a node of their color (red if player 1, blue if player 2)
and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)

If (and only if) a player cannot choose such a node in this way, they must pass their turn.
If both players pass their turn, the game ends, and the winner is the player that colored more nodes.

You are the second player.
If it is possible to choose such a y to ensure you win the game, return true.
If it is not possible, return false.

Example 1:
Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
Output: true
Explanation: The second player can choose the node with value 2.

Example 2:
Input: root = [1,2,3], n = 3, x = 1
Output: false

Constraints:
The number of nodes in the tree is n.
1 <= x <= n <= 100
n is odd.
1 <= Node.val <= n
All the values of the tree are unique.
```

<details><summary>Hint</summary>

```text
1. The best move y must be immediately adjacent to x, since it locks out that subtree.
2. Can you count each of (up to) 3 different subtrees neighboring x?
```

</details>

</details>

<details><summary>C</summary>

```c
int nodeCount(struct TreeNode* pRoot, int* leftCount, int* rightCount, int nodeValue) {
    if (pRoot == NULL) {
        return 0;
    }

    int left = nodeCount(pRoot->left, leftCount, rightCount, nodeValue);
    int right = nodeCount(pRoot->right, leftCount, rightCount, nodeValue);
    if (pRoot->val == nodeValue) {
        (*leftCount) = left;
        (*rightCount) = right;
    }

    return (left + right + 1);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool btreeGameWinningMove(struct TreeNode* root, int n, int x) {
    bool retVal = false;

    int left = 0;
    int right = 0;
    nodeCount(root, &left, &right, x);

    if (left > (n / 2)) {
        retVal = true;
    } else if (right > (n / 2)) {
        retVal = true;
    } else if ((n - 1 - left - right) > (n / 2)) {
        retVal = true;
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    int nodeCount(TreeNode* root, int* leftCount, int* rightCount, int nodeValue) {
        if (root == nullptr) {
            return 0;
        }

        int left = nodeCount(root->left, leftCount, rightCount, nodeValue);
        int right = nodeCount(root->right, leftCount, rightCount, nodeValue);
        if (root->val == nodeValue) {
            (*leftCount) = left;
            (*rightCount) = right;
        }

        return (left + right + 1);
    }
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        bool retVal = false;

        int left = 0;
        int right = 0;
        nodeCount(root, &left, &right, x);
        if (left > (n / 2)) {
            retVal = true;
        } else if (right > (n / 2)) {
            retVal = true;
        } else if ((n - 1 - left - right) > (n / 2)) {
            retVal = true;
        }

        return retVal;
    }
};
```

</details>

## [1161. Maximum Level Sum of a Binary Tree](https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/)  1249

- [Official](https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/maximum-level-sum-of-a-binary-tree/solutions/1707363/zui-da-ceng-nei-yuan-su-he-by-leetcode-s-2tm4/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

Example 1:
Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Example 2:
Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. Calculate the sum for each level then find the level with the maximum sum.
2. How can you traverse the tree ?
3. How can you sum up the values for every level ?
4. Use DFS or BFS to traverse the tree keeping the level of each node,
   and sum up those values with a map or a frequency array.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define DFS (0)
#define BFS (1)
#define MAX_TREE_NODE (int)(1e4)
void dfs(struct TreeNode* root, int level, int* sum, int* sumSize) {
    if (level == (*sumSize)) {
        sum[(*sumSize)++] = root->val;
    } else {
        sum[level] += root->val;
    }

    if (root->left != NULL) {
        dfs(root->left, level + 1, sum, sumSize);
    }
    if (root->right != NULL) {
        dfs(root->right, level + 1, sum, sumSize);
    }
}
int bfs(struct TreeNode* root) {
    int retVal = 0;

    int maxSum = INT_MIN;
    int level = 0;
    struct TreeNode* bfsQueue[MAX_TREE_NODE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = root;

    int bfsQueueCount;
    int sum;
    int i;
    struct TreeNode* node = NULL;
    while (bfsQueueHead > bfsQueueTail) {
        ++level;

        sum = 0;
        bfsQueueCount = bfsQueueHead - bfsQueueTail;
        for (i = 0; i < bfsQueueCount; ++i) {
            node = bfsQueue[bfsQueueTail];
            ++bfsQueueTail;
            sum += node->val;

            if (node->left != NULL) {
                bfsQueue[bfsQueueHead++] = node->left;
            }
            if (node->right != NULL) {
                bfsQueue[bfsQueueHead++] = node->right;
            }
        }

        if (maxSum < sum) {
            maxSum = sum;
            retVal = level;
        }
    }

    return retVal;
}
int maxLevelSum(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

#if (DFS)
    printf("Depth-First Search\n\n");

    int* sum = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (sum == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(sum, 0, (MAX_TREE_NODE * sizeof(int)));
    int sumSize = 0;

    dfs(root, 0, sum, &sumSize);
    int maxSum = INT_MIN;
    int i;
    for (i = 0; i < sumSize; ++i) {
        if (maxSum < sum[i]) {
            maxSum = sum[i];
            retVal = i + 1;
        }
    }

    free(sum);
    sum = NULL;
#elif (BFS)
    printf("Breadth-First Search\n\n");

    retVal = bfs(root);
#endif

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
#define DFS (0)
#define BFS (1)
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(TreeNode* root, int level, vector<int>& sum) {
        int sumSize = sum.size();
        if (level == sumSize) {
            sum.emplace_back(root->val);
        } else {
            sum[level] += root->val;
        }

        if (root->left != nullptr) {
            dfs(root->left, level + 1, sum);
        }
        if (root->right != nullptr) {
            dfs(root->right, level + 1, sum);
        }
    }
    int bfs(TreeNode* root) {
        int retVal = 0;

        int maxSum = numeric_limits<int>::min();
        int level = 0;
        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);
        while (bfsQueue.empty() == false) {
            ++level;
            int sum = 0;
            int bfsQueueCount = bfsQueue.size();
            for (int i = 0; i < bfsQueueCount; ++i) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();
                sum += node->val;

                if (node->left != nullptr) {
                    bfsQueue.emplace(node->left);
                }
                if (node->right != nullptr) {
                    bfsQueue.emplace(node->right);
                }
            }

            if (maxSum < sum) {
                maxSum = sum;
                retVal = level;
            }
        }

        return retVal;
    }
    int maxLevelSum(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        vector<int> sum;
        dfs(root, 0, sum);
        retVal = distance(sum.begin(), max_element(sum.begin(), sum.end())) + 1;
#elif (BFS)
        retVal = bfs(root);
#endif

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.method = 2

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, root: Optional[TreeNode], level: int, sum: List[int]):
        if level == len(sum):
            sum.append(root.val)
        else:
            sum[level] += root.val

        if root.left:
            self.dfs(root.left, level + 1, sum)
        if root.right:
            self.dfs(root.right, level + 1, sum)

    def bfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        maxSum = float('-inf')
        level = 0
        bfsQueue = deque()
        bfsQueue.append(root)
        while bfsQueue:
            level += 1
            sum = 0
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()
                sum += node.val

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            if maxSum < sum:
                maxSum = sum
                retVal = level

        return retVal

    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if self.method == 1:
            sum = []
            self.dfs(root, 0, sum)
            retVal = sum.index(max(sum)) + 1
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal
```

</details>

## [1325. Delete Leaves With a Given Value](https://leetcode.com/problems/delete-leaves-with-a-given-value/)  1407

- [Official](https://leetcode.com/problems/delete-leaves-with-a-given-value/editorial/)
- [Official](https://leetcode.cn/problems/delete-leaves-with-a-given-value/solutions/101264/shan-chu-gei-ding-zhi-de-xie-zi-jie-dian-by-leet-2/)

<details><summary>Description</summary>

```text
Given a binary tree root and an integer target, delete all the leaf nodes with value target.

Note that once you delete a leaf node with value target,
if its parent node becomes a leaf node and has the value target,
it should also be deleted (you need to continue doing that until you cannot).

Example 1:
    1          1        1
   / \        / \        \
  2   3  ->  2   3  ->    3
 /   / \          \        \
2   2   4          4        4
Input: root = [1,2,3,2,null,2,4], target = 2
Output: [1,null,3,null,4]
Explanation: Leaf nodes in green with value (target = 2) are removed (Picture in left).
After removing, new nodes become leaf nodes with value (target = 2) (Picture in center).

Example 2:
    1          1
   / \        /
  3   3  ->  3
 / \          \
3   2          2
Input: root = [1,3,3,3,2], target = 3
Output: [1,3,null,null,2]

Example 3:
      1        1        1     1
     /        /        /
    2   ->   2   ->   2   ->
   /        /
  2        2
 /
2
Input: root = [1,2,null,2,null,2], target = 2
Output: [1]
Explanation: Leaf nodes in green with value (target = 2) are removed at each step.

Constraints:
The number of nodes in the tree is in the range [1, 3000].
1 <= Node.val, target <= 1000
```

<details><summary>Hint</summary>

```text
1. Use the DFS to reconstruct the tree such that no leaf node is equal to the target.
   If the leaf node is equal to the target, return an empty object instead.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* removeLeafNodes(struct TreeNode* root, int target) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    pRetVal->left = removeLeafNodes(pRetVal->left, target);
    pRetVal->right = removeLeafNodes(pRetVal->right, target);
    if ((pRetVal->left == NULL) && (pRetVal->right == NULL) && (pRetVal->val == target)) {
        free(pRetVal);
        pRetVal = NULL;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        TreeNode* pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        pRetVal->left = removeLeafNodes(pRetVal->left, target);
        pRetVal->right = removeLeafNodes(pRetVal->right, target);
        if ((pRetVal->left == nullptr) && (pRetVal->right == nullptr) && (pRetVal->val == target)) {
            // delete pRetVal;
            pRetVal = nullptr;
        }

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def removeLeafNodes(self, root: Optional[TreeNode], target: int) -> Optional[TreeNode]:
        retVal = root

        if retVal is None:
            return retVal

        retVal.left = self.removeLeafNodes(retVal.left, target)
        retVal.right = self.removeLeafNodes(retVal.right, target)
        if (retVal.left is None) and (retVal.right is None) and (retVal.val == target):
            retVal = None

        return retVal
```

</details>

## [1339. Maximum Product of Splitted Binary Tree](https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/)  1674

<details><summary>Description</summary>

```text
Given the root of a binary tree, split the binary tree into two subtrees by removing one edge
such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

Example 1:
     1              1
   /   \             \
  2     3     2       3
 / \   /     / \     /
4   5 6     4   5   6
Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)

Example 2:
1        1
 \        \
  2        2
 / \      /
3   4    3     4
   / \        / \
  5   6      5   6
Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)

Constraints:
The number of nodes in the tree is in the range [2, 5 * 104].
1 <= Node.val <= 10^4
```

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MODULO (int)(1e9 + 7)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int postOrder(struct TreeNode* root, int* pSubTreeSum, int* returnSubTreeSumCount) {
    if (root == NULL) {
        return 0;
    }

    int retVal = postOrder(root->left, pSubTreeSum, returnSubTreeSumCount) +
                 postOrder(root->right, pSubTreeSum, returnSubTreeSumCount) + root->val;
    pSubTreeSum[(*returnSubTreeSumCount)++] = retVal;

    return retVal;
}
int maxProduct(struct TreeNode* root) {
    int retVal = 0;

#define MAX_NODE (50000)
    int subTreeSum[MAX_NODE];
    memset(subTreeSum, 0, sizeof(subTreeSum));
    int subTreeSumCount = 0;

    int treeSum = postOrder(root, subTreeSum, &subTreeSumCount);
    long long tmpRet = 0;
    int i;
    for (i = 0; i < subTreeSumCount; ++i) {
        tmpRet = MAX(tmpRet, ((long long)subTreeSum[i] * (long long)(treeSum - subTreeSum[i])));
    }
    retVal = tmpRet % MODULO;

    return retVal;
}
```

</details>

## [1367. Linked List in Binary Tree](https://leetcode.com/problems/linked-list-in-binary-tree/)  1649

- [Official](https://leetcode.com/problems/linked-list-in-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/linked-list-in-binary-tree/solutions/122916/er-cha-shu-zhong-de-lie-biao-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given a binary tree root and a linked list with head as the first node.

Return True if all the elements in the linked list starting
from the head correspond to some downward path connected in the binary tree otherwise return False.

In this context downward path means a path that starts at some node and goes downwards.

Example 1:
     1
 /       \
4         4
 \       /
  2     2
 /     / \
1     6   8
         / \
        1   3
Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: Nodes in blue form a subpath in the binary Tree.

Example 2:
     1
 /       \
4         4
 \       /
  2     2
 /     / \
1     6   8
         / \
        1   3
Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true

Example 3:
     1
 /       \
4         4
 \       /
  2     2
 /     / \
1     6   8
         / \
        1   3
Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: false
Explanation: There is no path in the binary tree that contains all the elements of the linked list from head.

Constraints:
The number of nodes in the tree will be in the range [1, 2500].
The number of nodes in the list will be in the range [1, 100].
1 <= Node.val <= 100 for each node in the linked list and binary tree.
```

<details><summary>Hint</summary>

```text
1. Create recursive function, given a pointer in a Linked List and any node in the Binary Tree.
   Check if all the elements in the linked list starting
   from the head correspond to some downward path in the binary tree.
```

</details>

</details>

<details><summary>C</summary>

```c
bool dfs(struct ListNode* head, struct TreeNode* root) {
    bool retVal = false;

    if (head == NULL) {
        retVal = true;
    } else if (root == NULL) {
        retVal = false;
    } else if (head->val != root->val) {
        retVal = false;
    } else {
        retVal = dfs(head->next, root->left) || dfs(head->next, root->right);
    }

    return retVal;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    bool retVal = false;

    if (root == NULL) {
        return retVal;
    }

    retVal = dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    bool dfs(ListNode* head, TreeNode* root) {
        bool retVal = false;

        if (head == nullptr) {
            retVal = true;
        } else if (root == nullptr) {
            retVal = false;
        } else if (head->val != root->val) {
            retVal = false;
        } else {
            retVal = dfs(head->next, root->left) || dfs(head->next, root->right);
        }

        return retVal;
    }

   public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        bool retVal = false;

        if (root == nullptr) {
            return retVal;
        }

        retVal = dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def dfs(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        retVal = False

        if head is None:
            retVal= True
        elif root is None:
            retVal= False
        elif head.val != root.val:
            retVal= False
        else:
            retVal = self.dfs(head.next, root.left) or self.dfs(head.next, root.right)

        return retVal

    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        retVal = False

        if root is None:
            return retVal

        retVal = self.dfs(head, root) or self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

        return retVal
```

</details>

## [1372. Longest ZigZag Path in a Binary Tree](https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/)  1713

- [Official](https://leetcode.cn/problems/longest-zigzag-path-in-a-binary-tree/solutions/147425/er-cha-shu-zhong-de-zui-chang-jiao-cuo-lu-jing-b-2/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree.

A ZigZag path for a binary tree is defined as follow:
- Choose any node in the binary tree and a direction (right or left).
- If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
- Change the direction from right to left or from left to right.
- Repeat the second and third steps until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.

Example 1:
Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
Output: 3
Explanation: Longest ZigZag path in blue nodes (right -> left -> right).

Example 2:
Input: root = [1,1,1,null,1,null,null,1,1,null,1]
Output: 4
Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).

Example 3:
Input: root = [1]
Output: 0

Constraints:
The number of nodes in the tree is in the range [1, 5 * 10^4].
1 <= Node.val <= 100
```

<details><summary>Hint</summary>

```text
1. Create this function maxZigZag(node, direction) maximum zigzag given a node and direction (right or left).
```

</details>

</details>

<details><summary>C</summary>

```c
void dfs(struct TreeNode* root, bool dir, int len, int* retVal) {
    (*retVal) = fmax((*retVal), len);

    // bool dir: left is false, right is true.
    if (dir == false) {
        if (root->left) {
            dfs(root->left, true, len + 1, retVal);
        }
        if (root->right) {
            dfs(root->right, false, 1, retVal);
        }
    } else {
        if (root->right) {
            dfs(root->right, false, len + 1, retVal);
        }
        if (root->left) {
            dfs(root->left, true, 1, retVal);
        }
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int longestZigZag(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    // bool dir: left is false, right is true.
    dfs(root, false, 0, &retVal);
    dfs(root, true, 0, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    void dfs(TreeNode* root, bool dir, int len, int* retVal) {
        (*retVal) = max((*retVal), len);

        // bool dir: left is false, right is true.
        if (dir == false) {
            if (root->left) {
                dfs(root->left, true, len + 1, retVal);
            }
            if (root->right) {
                dfs(root->right, false, 1, retVal);
            }
        } else {
            if (root->right) {
                dfs(root->right, false, len + 1, retVal);
            }
            if (root->left) {
                dfs(root->left, true, 1, retVal);
            }
        }
    }
    int longestZigZag(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        // bool dir: left is false, right is true.
        dfs(root, false, 0, &retVal);
        dfs(root, true, 0, &retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.maxLength = 0

    def dfs(self, root: Optional[TreeNode], dir: bool, len: int):
        self.maxLength = max(self.maxLength, len)

        # bool dir: left is false, right is true.
        if dir == False:
            if root.left != None:
                self.dfs(root.left, True, len + 1)
            if root.right != None:
                self.dfs(root.right, False, 1)
        else:
            if root.right != None:
                self.dfs(root.right, False, len + 1)
            if root.left != None:
                self.dfs(root.left, True, 1)

    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        # bool dir: left is false, right is true.
        self.maxLength = 0
        self.dfs(root, False, 0)
        self.dfs(root, True, 0)
        retVal = self.maxLength

        return retVal
```

</details>

## [1382. Balance a Binary Search Tree](https://leetcode.com/problems/balance-a-binary-search-tree/)  1540

- [Official](https://leetcode.com/problems/balance-a-binary-search-tree/editorial/)
- [Official](https://leetcode.cn/problems/balance-a-binary-search-tree/solutions/241897/jiang-er-cha-sou-suo-shu-bian-ping-heng-by-leetcod/)

<details><summary>Description</summary>

```text
Given the root of a binary search tree, return a balanced binary search tree with the same node values.
If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

Example 1:
1           2           3
 \         / \         / \
  2       1   3       1   4
   \  ->       \  ->   \
    3           4       2
     \
      4
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:
  2
 / \
1   3
Input: root = [2,1,3]
Output: [2,1,3]

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
1 <= Node.val <= 10^5
```

<details><summary>Hint</summary>

```text
1. Convert the tree to a sorted array using an in-order traversal.
2. Construct a new balanced tree from the sorted array recursively.
```

</details>

</details>

<details><summary>C</summary>

```c
void inorderTraversal(struct TreeNode* root, int* inorder, int* inorderSize) {
    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left, inorder, inorderSize);
    inorder[(*inorderSize)] = root->val;
    (*inorderSize) += 1;
    inorderTraversal(root->right, inorder, inorderSize);
}
struct TreeNode* createBalancedBST(int* inorder, int start, int end) {
    struct TreeNode* pRetVal = NULL;

    // Base case: if the start index is greater than the end index, return NULL
    if (start > end) {
        return pRetVal;
    }

    // Find the middle element of the current range
    int mid = start + (end - start) / 2;
    // Recursively construct the left and right subtrees
    struct TreeNode* leftSubtree = createBalancedBST(inorder, start, mid - 1);
    struct TreeNode* rightSubtree = createBalancedBST(inorder, mid + 1, end);
    // Create a new node with the middle element and attach the subtrees
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = inorder[mid];
    pRetVal->left = leftSubtree;
    pRetVal->right = rightSubtree;

    return pRetVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* balanceBST(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree is in the range [1, 10^4].
    // Create a vector to store the inorder traversal of the BST
    int inorder[MAX_TREE_NODE];
    memset(inorder, 0, sizeof(inorder));
    int inorderSize = 0;
    inorderTraversal(root, inorder, &inorderSize);

    // Construct and return the balanced BST
    pRetVal = createBalancedBST(inorder, 0, inorderSize - 1);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->right, inorder);
    }
    TreeNode* createBalancedBST(const vector<int>& inorder, int start, int end) {
        TreeNode* pRetVal = nullptr;

        // Base case: if the start index is greater than the end index, return nullptr
        if (start > end) {
            return pRetVal;
        }

        // Find the middle element of the current range
        int mid = start + (end - start) / 2;
        // Recursively construct the left and right subtrees
        TreeNode* leftSubtree = createBalancedBST(inorder, start, mid - 1);
        TreeNode* rightSubtree = createBalancedBST(inorder, mid + 1, end);
        // Create a new node with the middle element and attach the subtrees
        pRetVal = new TreeNode(inorder[mid], leftSubtree, rightSubtree);

        return pRetVal;
    }

   public:
    TreeNode* balanceBST(TreeNode* root) {
        TreeNode* pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        // Create a vector to store the inorder traversal of the BST
        vector<int> inorder;
        inorderTraversal(root, inorder);
        int inorderSize = inorder.size();

        // Construct and return the balanced BST
        pRetVal = createBalancedBST(inorder, 0, inorderSize - 1);

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def inorderTraversal(self, root: TreeNode, inorder: list) -> None:
        if root is None:
            return

        self.inorderTraversal(root.left, inorder)
        inorder.append(root.val)
        self.inorderTraversal(root.right, inorder)

    def create_balanced_bst(self, inorder: list, start: int, end: int) -> TreeNode:
        retVal = None

        # Base case: if the start index is greater than the end index, return None
        if start > end:
            return retVal

        # Find the middle element of the current range
        mid = start + (end - start) // 2
        # Recursively construct the left and right subtrees
        left_subtree = self.create_balanced_bst(inorder, start, mid - 1)
        right_subtree = self.create_balanced_bst(inorder, mid + 1, end)
        # Create a new node with the middle element and attach the subtrees
        retVal = TreeNode(inorder[mid], left_subtree, right_subtree)

        return retVal

    def balanceBST(self, root: TreeNode) -> TreeNode:
        retVal = root

        if retVal is None:
            return retVal

        inorder = []
        self.inorderTraversal(root, inorder)
        inorderSize = len(inorder)

        retVal = self.create_balanced_bst(inorder, 0, inorderSize - 1)

        return retVal
```

</details>

## [1457. Pseudo-Palindromic Paths in a Binary Tree](https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/)  1405

- [Official](https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/pseudo-palindromic-paths-in-a-binary-tree/solutions/2537866/er-cha-shu-zhong-de-wei-hui-wen-lu-jing-3ii6l/)

<details><summary>Description</summary>

```text
Given a binary tree where node values are digits from 1 to 9.
A path in the binary tree is said to be pseudo-palindromic
if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

Example 1:
    2
   / \
  3   1
 / \   \
3   1   1
Input: root = [2,3,1,3,1,null,1]
Output: 2
Explanation: The figure above represents the given binary tree.
There are three paths going from the root node to leaf nodes:
the red path [2,3,3], the green path [2,1,1], and the path [2,3,1].
Among these paths only red path and green path are pseudo-palindromic paths
since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome)
and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).

Example 2:
    2
   / \
  1   1
 / \
1   3
     \
      1
Input: root = [2,1,1,1,3,null,null,null,null,null,1]
Output: 1
Explanation: The figure above represents the given binary tree.
There are three paths going from the root node to leaf nodes:
the green path [2,1,1], the path [2,1,3,1], and the path [2,1].
Among these paths only the green path is pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1] (palindrome).

Example 3:
Input: root = [9]
Output: 1

Constraints:
The number of nodes in the tree is in the range [1, 10^5].
1 <= Node.val <= 9
```

<details><summary>Hint</summary>

```text
1. Note that the node values of a path form a palindrome if at most one digit has an odd frequency (parity).
2. Use a Depth First Search (DFS) keeping the frequency (parity) of the digits.
   Once you are in a leaf node check if at most one digit has an odd frequency (parity).
```

</details>

</details>

<details><summary>C</summary>

```c
void preorder(struct TreeNode* root, int mask, int* returnCount) {
    if (root == NULL) {
        return;
    }

    mask = mask ^ (1 << root->val);  // 1 <= Node.val <= 9
    if ((root->left == NULL) && (root->right == NULL)) {
        if ((mask & (mask - 1)) == 0) {
            (*returnCount)++;
        }
        return;
    }
    preorder(root->left, mask, returnCount);
    preorder(root->right, mask, returnCount);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int pseudoPalindromicPaths(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    preorder(root, 0, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    void preorder(TreeNode* root, int mask, int* returnCount) {
        if (root == nullptr) {
            return;
        }

        mask = mask ^ (1 << root->val);  // 1 <= Node.val <= 9
        if ((root->left == nullptr) && (root->right == nullptr)) {
            if ((mask & (mask - 1)) == 0) {
                (*returnCount)++;
            }
            return;
        }
        preorder(root->left, mask, returnCount);
        preorder(root->right, mask, returnCount);
    }
    int pseudoPalindromicPaths(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        preorder(root, 0, &retVal);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.count = 0

    def preorder(self, root: Optional[TreeNode], mask: int) -> None:
        if root == None:
            return

        mask = mask ^ (1 << root.val)   # 1 <= Node.val <= 9
        if (root.left == None) and (root.right == None):
            if (mask & (mask - 1)) == 0:
                self.count += 1
            return
        self.preorder(root.left, mask)
        self.preorder(root.right, mask)

    def pseudoPalindromicPaths(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        self.count = 0
        self.preorder(root, 0)
        retVal = self.count

        return retVal
```

</details>

## [1448. Count Good Nodes in Binary Tree](https://leetcode.com/problems/count-good-nodes-in-binary-tree)  1360

- [Official](https://leetcode.cn/problems/count-good-nodes-in-binary-tree/solutions/2399336/tong-ji-er-cha-shu-zhong-hao-jie-dian-de-dqtl/)

<details><summary>Description</summary>

```text
Given a binary tree root,
a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.

Example 1:
Input: root = [3,1,4,3,null,1,5]
Output: 4
Explanation: Nodes in blue are good.
Root Node (3) is always a good node.
Node 4 -> (3,4) is the maximum value in the path starting from the root.
Node 5 -> (3,4,5) is the maximum value in the path
Node 3 -> (3,1,3) is the maximum value in the path.

Example 2:
Input: root = [3,3,null,4,2]
Output: 3
Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.

Example 3:
Input: root = [1]
Output: 1
Explanation: Root is considered as good.

Constraints:
The number of nodes in the binary tree is in the range [1, 10^5].
Each node's value is between [-10^4, 10^4].
```

<details><summary>Hint</summary>

```text
1. Use DFS (Depth First Search) to traverse the tree, and constantly keep track of the current path maximum.
```

</details>

</details>

<details><summary>C</summary>

```c
int dfs(struct TreeNode* root, int maxValue) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if (root->val >= maxValue) {
        retVal++;
        maxValue = root->val;
    }
    int left = dfs(root->left, maxValue);
    int right = dfs(root->right, maxValue);
    retVal += (left + right);

    return retVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int goodNodes(struct TreeNode* root) {
    int retVal = 0;

    int maxValue = INT_MIN;  // Each node's value is between [-10^4, 10^4].
    retVal += dfs(root, maxValue);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    int dfs(struct TreeNode* root, int maxValue) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if (root->val >= maxValue) {
            retVal++;
            maxValue = root->val;
        }
        int left = dfs(root->left, maxValue);
        int right = dfs(root->right, maxValue);
        retVal += (left + right);

        return retVal;
    }
    int goodNodes(TreeNode* root) {
        int retVal = 0;

        int maxValue = numeric_limits<int>::min();  // Each node's value is between [-10^4, 10^4].
        retVal += dfs(root, maxValue);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def dfs(self, root: TreeNode, maxValue: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        if root.val >= maxValue:
            retVal += 1
            maxValue = root.val

        left = self.dfs(root.left, maxValue)
        right = self.dfs(root.right, maxValue)
        retVal += (left + right)

        return retVal

    def goodNodes(self, root: TreeNode) -> int:
        retVal = 0

        maxValue = float('-inf')  # Each node's value is between [-10^4, 10^4].
        retVal += self.dfs(root, maxValue)

        return retVal
```

</details>

## [1530. Number of Good Leaf Nodes Pairs](https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/)  1745

- [Official](https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/editorial/)
- [Official](https://leetcode.cn/problems/number-of-good-leaf-nodes-pairs/solutions/357905/hao-xie-zi-jie-dian-dui-de-shu-liang-by-leetcode-s/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree and an integer distance.
A pair of two different leaf nodes of a binary tree is said to be good
if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree.

Example 1:
Input: root = [1,2,3,null,4], distance = 3
Output: 1
Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3.
This is the only good pair.

Example 2:
Input: root = [1,2,3,4,5,6,7], distance = 3
Output: 2
Explanation: The good pairs are [4,5] and [6,7] with shortest path = 2.
The pair [4,6] is not good because the length of ther shortest path between them is 4.

Example 3:
Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
Output: 1
Explanation: The only good pair is [2,5].

Constraints:
The number of nodes in the tree is in the range [1, 2^10].
1 <= Node.val <= 100
1 <= distance <= 10
```

<details><summary>Hint</summary>

```text
1. Start DFS from each leaf node. stop the DFS when the number of steps done > distance.
2. If you reach another leaf node within distance steps, add 1 to the answer.
3. Note that all pairs will be counted twice so divide the answer by 2.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/number-of-good-leaf-nodes-pairs/solutions/2526545/po-su-de-si-lu-ji-zhi-de-bao-li-by-xun-j-iod9/
void lookChild(struct TreeNode* root, int subtree[], int* subtreeIndex, int deep) {
    if (root == NULL) {
        return;
    } else if ((root->left == NULL) && (root->right == NULL)) {
        subtree[(*subtreeIndex)++] = deep;
        return;
    }

    lookChild(root->left, subtree, subtreeIndex, deep + 1);
    lookChild(root->right, subtree, subtreeIndex, deep + 1);
}
void dfs(struct TreeNode* root, int distance, int* ans) {
    if (root == NULL) {
        return;
    } else if ((root->left == NULL) && (root->right == NULL)) {
        return;
    }

    int maxNodes = 1024;  // The number of nodes in the tree is in the range [1, 2^10].

    int leftIndex = 0;
    int left[maxNodes];
    memset(left, 0, sizeof(left));
    lookChild(root->left, left, &leftIndex, 1);

    int rightIndex = 0;
    int right[maxNodes];
    memset(right, 0, sizeof(right));
    lookChild(root->right, right, &rightIndex, 1);

    int i, j;
    for (i = 0; i < leftIndex; i++) {
        for (j = 0; j < rightIndex; j++) {
            if (left[i] + right[j] <= distance) {
                (*ans)++;
            }
        }
    }
    dfs(root->left, distance, ans);
    dfs(root->right, distance, ans);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countPairs(struct TreeNode* root, int distance) {
    int retVal = 0;

    dfs(root, distance, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    void traverseTree(TreeNode* currNode, TreeNode* prevNode, unordered_map<TreeNode*, vector<TreeNode*>>& graph,
                      unordered_set<TreeNode*>& leafNodes) {
        if (currNode == nullptr) {
            return;
        }

        if ((currNode->left == nullptr) && (currNode->right == nullptr)) {
            leafNodes.insert(currNode);
        }
        if (prevNode != nullptr) {
            graph[prevNode].push_back(currNode);
            graph[currNode].push_back(prevNode);
        }
        traverseTree(currNode->left, currNode, graph, leafNodes);
        traverseTree(currNode->right, currNode, graph, leafNodes);
    }

   public:
    int countPairs(TreeNode* root, int distance) {
        int retVal = 0;

        unordered_map<TreeNode*, vector<TreeNode*>> graph;
        unordered_set<TreeNode*> leafNodes;
        traverseTree(root, nullptr, graph, leafNodes);

        for (auto leaf : leafNodes) {
            queue<TreeNode*> bfsQueue;
            bfsQueue.push(leaf);

            unordered_set<TreeNode*> seen;
            seen.insert(leaf);

            // Go through all nodes that are within the given distance of the current leaf node
            for (int i = 0; i <= distance; i++) {
                int bfsQueueSize = bfsQueue.size();
                for (int j = 0; j < bfsQueueSize; j++) {
                    TreeNode* currNode = bfsQueue.front();
                    bfsQueue.pop();
                    if ((leafNodes.count(currNode) != 0) && (currNode != leaf)) {
                        retVal++;
                    }
                    if (graph.count(currNode) != 0) {
                        for (auto neighbor : graph[currNode]) {
                            if (seen.count(neighbor) == 0) {
                                bfsQueue.push(neighbor);
                                seen.insert(neighbor);
                            }
                        }
                    }
                }
            }
        }

        retVal /= 2;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def traverseTree(self, currNode: TreeNode, prevNode: TreeNode, graph: dict, leafNodes: set) -> None:
        if currNode is None:
            return

        if (currNode.left is None) and (currNode.right is None):
            leafNodes.add(currNode)

        if prevNode is not None:
            if prevNode not in graph:
                graph[prevNode] = []
            graph[prevNode].append(currNode)

            if currNode not in graph:
                graph[currNode] = []
            graph[currNode].append(prevNode)

        self.traverseTree(currNode.left, currNode, graph, leafNodes)
        self.traverseTree(currNode.right, currNode, graph, leafNodes)

    def countPairs(self, root: TreeNode, distance: int) -> int:
        retVal = 0

        graph = {}
        leafNodes = set()
        self.traverseTree(root, None, graph, leafNodes)

        for leaf in leafNodes:
            bfsQueue = []
            bfsQueue.append(leaf)
            seen = set()
            seen.add(leaf)

            for _ in range(distance + 1):
                # Clear all nodes in the queue (distance i away from leaf node)
                # Add the nodes' neighbors (distance i+1 away from leaf node)
                bfsQueueSize = len(bfsQueue)
                for _ in range(bfsQueueSize):
                    currNode = bfsQueue.pop(0)
                    if (currNode in leafNodes) and (currNode != leaf):
                        retVal += 1
                    if currNode in graph:
                        for neighbor in graph.get(currNode):
                            if neighbor not in seen:
                                bfsQueue.append(neighbor)
                                seen.add(neighbor)

        retVal //= 2

        return retVal
```

</details>

## [1569. Number of Ways to Reorder Array to Get Same BST](https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/)  2288

- [Official](https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/editorial/)
- [Official](https://leetcode.cn/problems/number-of-ways-to-reorder-array-to-get-same-bst/solutions/403712/jiang-zi-shu-zu-zhong-xin-pai-xu-de-dao-tong-yi-2/)

<details><summary>Description</summary>

```text
Given an array nums that represents a permutation of integers from 1 to n.
We are going to construct a binary search tree (BST) by inserting the elements of nums
in order into an initially empty BST.
Find the number of different ways to reorder nums so that the constructed BST is identical
to that formed from the original array nums.

For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child.
The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.

Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:
Input: nums = [2,1,3]
Output: 1
Explanation: We can reorder nums to be [2,3,1] which will yield the same BST.
There are no other ways to reorder nums which will yield the same BST.

Example 2:
Input: nums = [3,4,5,1,2]
Output: 5
Explanation: The following 5 arrays will yield the same BST:
[3,1,2,4,5]
[3,1,4,2,5]
[3,1,4,5,2]
[3,4,1,2,5]
[3,4,1,5,2]

Example 3:
Input: nums = [1,2,3]
Output: 0
Explanation: There are no other orderings of nums that will yield the same BST.

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= nums.length
All integers in nums are distinct.
```

<details><summary>Hint</summary>

```text
1. Use a divide and conquer strategy.
2. The first number will always be the root.
   Consider the numbers smaller and larger than the root separately.
   When merging the results together, how many ways can you order x elements in x+y positions?
```

</details>

</details>

<details><summary>C</summary>

```c
#define MODULO (int)(1e9 + 7)
long long dfs(int* nums, int numsSize, long long** table) {
    int retVal = 1;

    if (numsSize < 3) {
        return retVal;
    }

    int leftNodesSize = 0;
    int leftNodes[numsSize];
    memset(leftNodes, 0, sizeof(leftNodes));
    int rightNodesSize = 0;
    int rightNodes[numsSize];
    memset(rightNodes, 0, sizeof(rightNodes));

    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[0]) {
            leftNodes[leftNodesSize++] = nums[i];
        } else {
            rightNodes[rightNodesSize++] = nums[i];
        }
    }

    long long leftWays = dfs(leftNodes, leftNodesSize, table) % MODULO;
    long long rightWays = dfs(rightNodes, rightNodesSize, table) % MODULO;
    retVal = (((leftWays * rightWays) % MODULO) * table[numsSize - 1][leftNodesSize]) % MODULO;

    return retVal;
}
int numOfWays(int* nums, int numsSize) {
    int retVal = 0;

    long long** pTable = (long long**)malloc((numsSize + 1) * sizeof(long long*));
    if (pTable == NULL) {
        perror("malloc");
        return retVal;
    }

    int i, j;
    for (i = 0; i < numsSize + 1; ++i) {
        pTable[i] = (long long*)malloc((i + 1) * sizeof(long long));
        if (pTable[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pTable[j]);
                pTable[j] = NULL;
            }
            free(pTable);
            pTable = NULL;
            return retVal;
        }
        memset(pTable[i], 0, ((i + 1) * sizeof(long long)));
        for (j = 0; j < i + 1; ++j) {
            pTable[i][j] = 1;
        }

        for (j = 1; j < i; ++j) {
            pTable[i][j] = (pTable[i - 1][j - 1] + pTable[i - 1][j]) % MODULO;
        }
    }
    retVal = (dfs(nums, numsSize, pTable) - 1) % MODULO;

    for (i = 0; i < numsSize + 1; ++i) {
        free(pTable[i]);
        pTable[i] = NULL;
    }
    free(pTable);
    pTable = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
#define MODULO (int)(1e9 + 7)
   private:
    long long dfs(vector<int>& nums, vector<vector<long long>>& table) {
        int retVal = 1;

        int numsSize = nums.size();
        if (numsSize < 3) {
            return retVal;
        }

        vector<int> leftNodes;
        vector<int> rightNodes;
        for (int i = 1; i < numsSize; ++i) {
            if (nums[i] < nums[0]) {
                leftNodes.push_back(nums[i]);
            } else {
                rightNodes.push_back(nums[i]);
            }
        }

        long long leftWays = dfs(leftNodes, table) % MODULO;
        long long rightWays = dfs(rightNodes, table) % MODULO;
        retVal = (((leftWays * rightWays) % MODULO) * table[numsSize - 1][leftNodes.size()]) % MODULO;

        return retVal;
    }

   public:
    int numOfWays(vector<int>& nums) {
        int retVal = 0;

        int numsSize = nums.size();
        vector<vector<long long>> table(numsSize + 1);
        for (int i = 0; i < numsSize + 1; ++i) {
            table[i] = vector<long long>(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MODULO;
            }
        }
        retVal = (dfs(nums, table) - 1) % MODULO;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7

    def dfs(self, nums: List[int]) -> int:
        retVal = 1

        numsSize = len(nums)
        if numsSize < 3:
            return retVal

        left_nodes = [a for a in nums if a < nums[0]]
        right_nodes = [a for a in nums if a > nums[0]]
        retVal = self.dfs(left_nodes) * self.dfs(right_nodes) * comb(numsSize - 1, len(left_nodes)) % self.MODULO

        return retVal

    def numOfWays(self, nums: List[int]) -> int:
        retVal = 0

        retVal = (self.dfs(nums) - 1) % self.MODULO

        return retVal
```

</details>

## [1609. Even Odd Tree](https://leetcode.com/problems/even-odd-tree/)  1438

- [Official](https://leetcode.com/problems/even-odd-tree/editorial/)
- [Official](https://leetcode.cn/problems/even-odd-tree/solutions/1174334/qi-ou-shu-by-leetcode-solution-l7bw/?envType=daily-question&envId=2024-02-29)

<details><summary>Description</summary>

```text
A binary tree is named Even-Odd if it meets the following conditions:
- The root of the binary tree is at level index 0, its children are at level index 1,
  their children are at level index 2, etc.
- For every even-indexed level,
  all nodes at the level have odd integer values in strictly increasing order (from left to right).
- For every odd-indexed level,
  all nodes at the level have even integer values in strictly decreasing order (from left to right).
Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.

Example 1:
         1
       /   \
     10     4
    /      / \
   3      7   9
  / \    /     \
12   8  6       2
Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
Output: true
Explanation: The node values on each level are:
Level 0: [1]
Level 1: [10,4]
Level 2: [3,7,9]
Level 3: [12,8,6,2]
Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all even and decreasing, the tree is Even-Odd.

Example 2:
     5
   /   \
  4     2
 / \   /
3   3 7
Input: root = [5,4,2,3,3,7]
Output: false
Explanation: The node values on each level are:
Level 0: [5]
Level 1: [4,2]
Level 2: [3,3,7]
Node values in level 2 must be in strictly increasing order, so the tree is not Even-Odd.

Example 3:
     5
   /   \
  9     1
 / \   /
3   5 7
Input: root = [5,9,1,3,5,7]
Output: false
Explanation: Node values in the level 1 should be even integers.

Constraints:
The number of nodes in the tree is in the range [1, 10^5].
1 <= Node.val <= 10^6
```

<details><summary>Hint</summary>

```text
1. Use the breadth-first search to go through all nodes layer by layer.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isEvenOddTree(struct TreeNode* root) {
    bool retVal = false;

#define MAX_QUEUE_SIZE (int)(1e5)  // The number of nodes in the tree is in the range [1, 10^5].
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail++] = root;

    int i;
    int level = 0;
    int previous, value;
    int bfsQueueSize = 0;
    struct TreeNode* pCurrent = NULL;
    while (bfsQueueHead < bfsQueueTail) {
        if (level % 2 == 0) {
            previous = INT_MIN;
        } else {
            previous = INT_MAX;
        }

        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            pCurrent = bfsQueue[bfsQueueHead++];
            value = pCurrent->val;
            if (level % 2 == 0) {
                if (value % 2 == 0) {
                    return retVal;
                } else if (value <= previous) {
                    return retVal;
                } else {
                    previous = value;
                }
            } else {
                if (value % 2 != 0) {
                    return retVal;
                } else if (value >= previous) {
                    return retVal;
                } else {
                    previous = value;
                }
            }

            if (pCurrent->left != NULL) {
                bfsQueue[bfsQueueTail++] = pCurrent->left;
            }
            if (pCurrent->right != NULL) {
                bfsQueue[bfsQueueTail++] = pCurrent->right;
            }
        }
        level++;
    }
    retVal = true;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    bool isEvenOddTree(TreeNode* root) {
        bool retVal = false;

        int level = 0;
        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);
        while (bfsQueue.empty() == false) {
            int previous;
            if (level % 2 == 0) {
                previous = numeric_limits<int>::min();
            } else {
                previous = numeric_limits<int>::max();
            }

            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                TreeNode* current = bfsQueue.front();
                bfsQueue.pop();
                int value = current->val;
                if (level % 2 == 0) {
                    if (value % 2 == 0) {
                        return retVal;
                    } else if (value <= previous) {
                        return retVal;
                    } else {
                        previous = value;
                    }
                } else {
                    if (value % 2 != 0) {
                        return retVal;
                    } else if (value >= previous) {
                        return retVal;
                    } else {
                        previous = value;
                    }
                }

                if (current->left != nullptr) {
                    bfsQueue.push(current->left);
                }
                if (current->right != nullptr) {
                    bfsQueue.push(current->right);
                }
            }
            level++;
        }
        retVal = true;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        level = 0
        bfsQueue = deque()
        bfsQueue.append(root)
        while bfsQueue:
            if level % 2 == 0:
                previous = float('-inf')
            else:
                previous = float('inf')

            bfsSize = len(bfsQueue)
            for _ in range(bfsSize):
                current = bfsQueue.popleft()
                value = current.val
                if level % 2 == 0:
                    if value % 2 == 0:
                        return retVal
                    elif value <= previous:
                        return retVal
                    previous = value
                else:
                    if value % 2 != 0:
                        return retVal
                    elif value >= previous:
                        return retVal
                    previous = value

                if current.left:
                    bfsQueue.append(current.left)
                if current.right:
                    bfsQueue.append(current.right)

            level += 1

        retVal = True

        return retVal
```

</details>

## [2096. Step-By-Step Directions From a Binary Tree Node to Another](https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/)  1804

- [Official](https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/editorial/)
- [Official](https://leetcode.cn/problems/step-by-step-directions-from-a-binary-tree-node-to-another/solutions/1140772/cong-er-cha-shu-yi-ge-jie-dian-dao-ling-hsoh1/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n.
You are also given an integer startValue representing the value of the start node s,
and a different integer destValue representing the value of the destination node t.

Find the shortest path starting from node s and ending at node t.
Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'.
Each letter indicates a specific direction:
- 'L' means to go from a node to its left child node.
- 'R' means to go from a node to its right child node.
- 'U' means to go from a node to its parent node.

Return the step-by-step directions of the shortest path from node s to node t.

Example 1:
Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
Output: "UURL"
Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.

Example 2:
Input: root = [2,1], startValue = 2, destValue = 1
Output: "L"
Explanation: The shortest path is: 2 → 1.

Constraints:
The number of nodes in the tree is n.
2 <= n <= 10^5
1 <= Node.val <= n
All the values in the tree are unique.
1 <= startValue, destValue <= n
startValue != destValue
```

<details><summary>Hint</summary>

```text
1. The shortest path between any two nodes in a tree must pass through their Lowest Common Ancestor (LCA).
   The path will travel upwards from node s to the LCA and then downwards from the LCA to node t.
2. Find the path strings from root → s, and root → t. Can you use these two strings to prepare the final answer?
3. Remove the longest common prefix of the two path strings to get the path LCA → s, and LCA → t.
   Each step in the path of LCA → s should be reversed as 'U'.
```

</details>

</details>

<details><summary>C</summary>

```c
bool findPath(struct TreeNode* node, int target, char* path, int* pathSize) {
    bool retVal = false;

    if (node == NULL) {
        return retVal;
    }

    if (node->val == target) {
        retVal = true;
        return retVal;
    }

    // Try left subtree
    path[(*pathSize)] = 'L';
    (*pathSize) += 1;
    if (findPath(node->left, target, path, pathSize)) {
        retVal = true;
        return retVal;
    }

    // Remove last character
    path[(*pathSize)] = '\0';
    (*pathSize) -= 1;

    // Try right subtree
    path[(*pathSize)] = 'R';
    (*pathSize) += 1;
    if (findPath(node->right, target, path, pathSize)) {
        return true;
    }

    // Remove last character
    path[(*pathSize)] = '\0';
    (*pathSize) -= 1;

    return retVal;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* getDirections(struct TreeNode* root, int startValue, int destValue) {
    char* pRetVal = NULL;

    // Find paths from root to start and destination nodes
    int maxSize = (1e5);  // The number of nodes in the tree is n. 2 <= n <= 10 ^ 5
    char* pPath = (char*)malloc(maxSize * sizeof(char));
    if (pPath == NULL) {
        perror("malloc");
        return pRetVal;
    }
    //
    int startPathSize = 0;
    memset(pPath, 0, (maxSize * sizeof(char)));
    findPath(root, startValue, pPath, &startPathSize);
    char startPath[startPathSize + 1];
    memset(startPath, 0, sizeof(startPath));
    snprintf(startPath, sizeof(startPath), "%s", pPath);
    //
    int destPathSize = 0;
    memset(pPath, 0, (maxSize * sizeof(char)));
    findPath(root, destValue, pPath, &destPathSize);
    char destPath[destPathSize + 1];
    memset(destPath, 0, sizeof(destPath));
    snprintf(destPath, sizeof(destPath), "%s", pPath);
    //
    free(pPath);
    pPath = NULL;

    //
    int returnSize = startPathSize + destPathSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

    // Find the length of the common path
    int commonPathLength = 0;
    while ((commonPathLength < startPathSize) && (commonPathLength < destPathSize) &&
           (startPath[commonPathLength] == destPath[commonPathLength])) {
        commonPathLength++;
    }

    // Add "U" for each step to go up from start to common ancestor
    returnSize = 0;
    int i;
    for (i = 0; i < startPathSize - commonPathLength; i++) {
        pRetVal[returnSize++] = 'U';
    }
    // Add directions from common ancestor to destination
    for (i = commonPathLength; i < destPathSize; i++) {
        pRetVal[returnSize++] = destPath[i];
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    bool findPath(TreeNode* node, int target, string& path) {
        bool retVal = false;

        if (node == nullptr) {
            return retVal;
        }

        if (node->val == target) {
            retVal = true;
            return retVal;
        }

        // Try left subtree
        path += "L";
        if (findPath(node->left, target, path)) {
            retVal = true;
            return retVal;
        }

        // Remove last character
        path.pop_back();

        // Try right subtree
        path += "R";
        if (findPath(node->right, target, path)) {
            return true;
        }

        // Remove last character
        path.pop_back();

        return retVal;
    }

   public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string retVal = "";

        // Find paths from root to start and destination nodes
        string startPath;
        findPath(root, startValue, startPath);
        int startPathSize = startPath.length();
        string destPath;
        findPath(root, destValue, destPath);
        int destPathSize = destPath.length();

        // Find the length of the common path
        int commonPathLength = 0;
        while ((commonPathLength < startPathSize) && (commonPathLength < destPathSize) &&
               (startPath[commonPathLength] == destPath[commonPathLength])) {
            commonPathLength++;
        }

        // Add "U" for each step to go up from start to common ancestor
        for (int i = 0; i < startPathSize - commonPathLength; i++) {
            retVal += "U";
        }

        // Add directions from common ancestor to destination
        for (int i = commonPathLength; i < destPathSize; i++) {
            retVal += destPath[i];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def findPath(self, node: TreeNode, target: int, path: List[str]) -> bool:
        retVal = False

        if node is None:
            return retVal

        if node.val == target:
            retVal = True
            return retVal

        # Try left subtree
        path.append("L")
        if self.findPath(node.left, target, path):
            retVal = True
            return retVal

        # Remove last character
        path.pop()

        # Try right subtree
        path.append("R")
        if self.findPath(node.right, target, path):
            retVal = True
            return retVal

        # Remove last character
        path.pop()

        return retVal

    def getDirections(self, root: Optional[TreeNode], startValue: int, destValue: int) -> str:
        retVal = ""

        # Find paths from root to start and destination nodes
        startPath = []
        self.findPath(root, startValue, startPath)
        startPathSize = len(startPath)
        destPath = []
        self.findPath(root, destValue, destPath)
        destPathSize = len(destPath)

        # Find the length of the common path
        commonPathLength = 0
        while ((commonPathLength < startPathSize) and (commonPathLength < destPathSize)
               and (startPath[commonPathLength] == destPath[commonPathLength])):
            commonPathLength += 1

        directions = []
        # Add "U" for each step to go up from start to common ancestor
        directions.extend("U" * (startPathSize - commonPathLength))
        # Add directions from common ancestor to destination
        directions.extend(destPath[commonPathLength:])

        retVal = "".join(directions)

        return retVal
```

</details>

## [2196. Create Binary Tree From Descriptions](https://leetcode.com/problems/create-binary-tree-from-descriptions/)  1643

- [Official](https://leetcode.com/problems/create-binary-tree-from-descriptions/editorial/)
- [Official](https://leetcode.cn/problems/create-binary-tree-from-descriptions/solutions/1365049/gen-ju-miao-shu-chuang-jian-er-cha-shu-b-sqrk/)

<details><summary>Description</summary>

```text
You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that
parenti is the parent of childi in a binary tree of unique values.
Furthermore,
- If isLefti == 1, then childi is the left child of parenti.
- If isLefti == 0, then childi is the right child of parenti.
Construct the binary tree described by descriptions and return its root.

The test cases will be generated such that the binary tree is valid.

Example 1:
        50
     /      \
   20        80
  /  \      /
15    17  19
Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
Output: [50,20,80,15,17,19]
Explanation: The root node is the node with value 50 since it has no parent.
The resulting binary tree is shown in the diagram.

Example 2:
  1
 /
2
 \
  3
 /
4
Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
Output: [1,2,null,null,3,4]
Explanation: The root node is the node with value 1 since it has no parent.
The resulting binary tree is shown in the diagram.

Constraints:
1 <= descriptions.length <= 10^4
descriptions[i].length == 3
1 <= parenti, childi <= 10^5
0 <= isLefti <= 1
The binary tree described by descriptions is valid.
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    int key;
    struct TreeNode* value;
    UT_hash_handle hh;
} HashMapTree;
typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} HashMapChild;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
    struct TreeNode* pRetVal = NULL;

    HashMapTree* pTreeHashTable = NULL;
    HashMapTree *pParent, *pChild;
    HashMapChild* pChildHashTable = NULL;
    HashMapChild* pChildDegree;
    int parent, child, isLeft;
    int i;
    for (i = 0; i < descriptionsSize; ++i) {
        parent = descriptions[i][0];
        child = descriptions[i][1];
        isLeft = descriptions[i][2];

        // parent node
        pParent = NULL;
        HASH_FIND_INT(pTreeHashTable, &parent, pParent);
        if (pParent == NULL) {
            pParent = (HashMapTree*)malloc(sizeof(HashMapTree));
            if (pParent == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pParent->key = parent;
            pParent->value = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pParent->value == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pParent->value->val = parent;
            pParent->value->left = NULL;
            pParent->value->right = NULL;
            HASH_ADD_INT(pTreeHashTable, key, pParent);
        }
        // parent degree
        pChildDegree = NULL;
        HASH_FIND_INT(pChildHashTable, &parent, pChildDegree);
        if (pChildDegree == NULL) {
            pChildDegree = (HashMapChild*)malloc(sizeof(HashMapChild));
            if (pChildDegree == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChildDegree->key = parent;
            pChildDegree->value = 0;
            HASH_ADD_INT(pChildHashTable, key, pChildDegree);
        }

        // child node
        pChild = NULL;
        HASH_FIND_INT(pTreeHashTable, &child, pChild);
        if (pChild == NULL) {
            pChild = (HashMapTree*)malloc(sizeof(HashMapTree));
            if (pChild == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChild->key = child;
            pChild->value = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pChild->value == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChild->value->val = child;
            pChild->value->left = NULL;
            pChild->value->right = NULL;
            HASH_ADD_INT(pTreeHashTable, key, pChild);
        }
        // child degree
        pChildDegree = NULL;
        HASH_FIND_INT(pChildHashTable, &child, pChildDegree);
        if (pChildDegree == NULL) {
            pChildDegree = (HashMapChild*)malloc(sizeof(HashMapChild));
            if (pChildDegree == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pChildDegree->key = child;
            pChildDegree->value = 1;
            HASH_ADD_INT(pChildHashTable, key, pChildDegree);
        } else {
            pChildDegree->value += 1;
        }

        // isLeft
        if (isLeft == 1) {
            pParent->value->left = pChild->value;
        } else {
            pParent->value->right = pChild->value;
        }
    }

    // get root by degree
    parent = 0;
    HashMapChild* pCurrentChild;
    HashMapChild* pTempChild;
    HASH_ITER(hh, pChildHashTable, pCurrentChild, pTempChild) {
        if (pCurrentChild->value == 0) {
            parent = pCurrentChild->key;
        }
        HASH_DEL(pChildHashTable, pCurrentChild);
        free(pCurrentChild);
    }
    // get root node to return value
    HashMapTree* pCurrentParent;
    HashMapTree* pTempParent;
    HASH_ITER(hh, pTreeHashTable, pCurrentParent, pTempParent) {
        if (pCurrentParent->value->val == parent) {
            pRetVal = pCurrentParent->value;
        }
        HASH_DEL(pTreeHashTable, pCurrentParent);
        free(pCurrentParent);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        TreeNode* pRetVal = nullptr;

        unordered_map<int, TreeNode*> treeHashTable;
        unordered_map<int, int> childHashTable;
        for (auto& iter : descriptions) {
            int parent = iter[0];
            int child = iter[1];
            int isLeft = iter[2];

            if (treeHashTable.count(parent) == 0) {
                treeHashTable[parent] = new TreeNode(parent);
            }
            if (treeHashTable.count(child) == 0) {
                treeHashTable[child] = new TreeNode(child);
            }

            if (isLeft == 1) {
                treeHashTable[parent]->left = treeHashTable[child];
            } else {
                treeHashTable[parent]->right = treeHashTable[child];
            }

            ++childHashTable[child];
        }

        for (auto& [key, value] : treeHashTable) {
            if (childHashTable.count(key) == 0) {
                pRetVal = value;
                break;
            }
        }

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def createBinaryTree(self, descriptions: List[List[int]]) -> Optional[TreeNode]:
        retVal = None

        treeHashTable = defaultdict(TreeNode)
        childHashTable = defaultdict(int)
        for parent, child, isLeft in descriptions:
            if parent not in treeHashTable:
                treeHashTable[parent] = TreeNode(parent)

            if child not in treeHashTable:
                treeHashTable[child] = TreeNode(child)

            if isLeft == 1:
                treeHashTable[parent].left = treeHashTable[child]
            else:
                treeHashTable[parent].right = treeHashTable[child]

            childHashTable[child] += 1

        for key, value in treeHashTable.items():
            if key not in childHashTable:
                retVal = value
                break

        return retVal
```

</details>

## [2265. Count Nodes Equal to Average of Subtree](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/)  1472

- [Official](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/editorial/)

<details><summary>Description</summary>

```text
Given the root of a binary tree,
return the number of nodes where the value of the node is equal to the average of the values in its subtree.

Note:
- The average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
- A subtree of root is a tree consisting of root and all of its descendants.

Example 1:
    4
   / \
  8   5
 / \   \
0   1   6
Input: root = [4,8,5,0,1,null,6]
Output: 5
Explanation:
For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4.
For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 / 2 = 5.
For the node with value 0: The average of its subtree is 0 / 1 = 0.
For the node with value 1: The average of its subtree is 1 / 1 = 1.
For the node with value 6: The average of its subtree is 6 / 1 = 6.

Example 2:
Input: root = [1]
Output: 1
Explanation: For the node with value 1: The average of its subtree is 1 / 1 = 1.

Constraints:
The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 1000
```

<details><summary>Hint</summary>

```text
1. What information do we need to calculate the average? We need the sum of the values and the number of values.
2. Create a recursive function that returns the size of a node’s subtree, and the sum of the values of its subtree.
```

</details>

</details>

<details><summary>C</summary>

```c
void postorder(struct TreeNode* root, int* subtreeSum, int* subtreeNode, int* answer) {
    if (root == NULL) {
        (*subtreeSum) = 0;
        (*subtreeNode) = 0;
        return;
    }

    int leftSum, leftNode;
    postorder(root->left, &leftSum, &leftNode, answer);
    int rightSum, rightNode = 0;
    postorder(root->right, &rightSum, &rightNode, answer);

    (*subtreeSum) = leftSum + rightSum + root->val;
    (*subtreeNode) = leftNode + rightNode + 1;
    if (root->val == (*subtreeSum) / (*subtreeNode)) {
        (*answer) += 1;
    }
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int averageOfSubtree(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int subtreeSum = 0;
    int subtreeNode = 0;
    postorder(root, &subtreeSum, &subtreeNode, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    int answer = 0;

   public:
    pair<int, int> postorder(TreeNode* root) {
        pair<int, int> retval = {0, 0};
        if (root == nullptr) {
            return retval;
        }

        pair<int, int> left = postorder(root->left);
        pair<int, int> right = postorder(root->right);

        int subtreeSum = left.first + right.first + root->val;
        int subtreeNode = left.second + right.second + 1;
        if (root->val == subtreeSum / subtreeNode) {
            answer += 1;
        }
        retval = {subtreeSum, subtreeNode};

        return retval;
    }
    int averageOfSubtree(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        answer = 0;
        postorder(root);
        retVal = answer;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self) -> None:
        self.answer = 0

    def postorder(self, root: Optional[TreeNode]) -> List[int]:
        if root == None:
            return [0, 0]

        leftSum, leftNode = self.postorder(root.left)
        rightSum, rightNode = self.postorder(root.right)

        subtreeSum = leftSum + rightSum + root.val
        subtreeNode = leftNode + rightNode + 1
        if root.val == subtreeSum // subtreeNode:
            self.answer += 1

        return [subtreeSum, subtreeNode]

    def averageOfSubtree(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        self.answer = 0
        self.postorder(root)
        retVal = self.answer

        return retVal
```

</details>

## [2331. Evaluate Boolean Binary Tree](https://leetcode.com/problems/evaluate-boolean-binary-tree/)  1303

- [Official](https://leetcode.cn/problems/evaluate-boolean-binary-tree/solutions/2091770/ji-suan-bu-er-er-cha-shu-de-zhi-by-leetc-4g8f/)

<details><summary>Description</summary>

```text
You are given the root of a full binary tree with the following properties:
- Leaf nodes have either the value 0 or 1, where 0 represents False and 1 represents True.
- Non-leaf nodes have either the value 2 or 3, where 2 represents the boolean OR and 3 represents the boolean AND.

The evaluation of a node is as follows:
- If the node is a leaf node, the evaluation is the value of the node, i.e. True or False.
- Otherwise, evaluate the node's two children and apply the boolean operation of its value with the children's evaluations.

Return the boolean result of evaluating the root node.

A full binary tree is a binary tree where each node has either 0 or 2 children.

A leaf node is a node that has zero children.

Example 1:
     OR                 OR                 True
    /  \               /  \
True    AND        True    False
       /   \
  False     True
Input: root = [2,1,3,null,null,0,1]
Output: true
Explanation: The above diagram illustrates the evaluation process.
The AND node evaluates to False AND True = False.
The OR node evaluates to True OR False = True.
The root node evaluates to True, so we return true.

Example 2:
Input: root = [0]
Output: false
Explanation: The root node is a leaf node and it evaluates to false, so we return false.

Constraints:
The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 3
Every node has either 0 or 2 children.
Leaf nodes have a value of 0 or 1.
Non-leaf nodes have a value of 2 or 3.
```

<details><summary>Hint</summary>

```text
1. Traverse the tree using depth-first search in post-order.
2. Can you use recursion to solve this easily?
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool evaluateTree(struct TreeNode* root) {
    bool retVal = false;

    if ((root->left == NULL) && (root->right == NULL)) {
        if (root->val == 0) {
            retVal = false;
        } else if (root->val == 1) {
            retVal = true;
        }

        return retVal;
    }

    if (root->val == 2) {
        retVal = (evaluateTree(root->left) | evaluateTree(root->right));
    } else if (root->val == 3) {
        retVal = (evaluateTree(root->left) & evaluateTree(root->right));
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    bool evaluateTree(TreeNode* root) {
        bool retVal = false;

        if ((root->left == nullptr) && (root->right == nullptr)) {
            if (root->val == 0) {
                retVal = false;
            } else if (root->val == 1) {
                retVal = true;
            }

            return retVal;
        }

        if (root->val == 2) {
            retVal = (evaluateTree(root->left) | evaluateTree(root->right));
        } else if (root->val == 3) {
            retVal = (evaluateTree(root->left) & evaluateTree(root->right));
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def evaluateTree(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        if (root.left is None) and (root.right is None):
            if root.val == 0:
                retVal = False
            elif root.val == 1:
                retVal = True
            return retVal

        if root.val == 2:
            retVal = self.evaluateTree(root.left) or self.evaluateTree(root.right)
        elif root.val == 3:
            retVal = self.evaluateTree(root.left) and self.evaluateTree(root.right)

        return retVal
```

</details>

## [2385. Amount of Time for Binary Tree to Be Infected](https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/)  1711

- [Official](https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/editorial/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree with unique values, and an integer start.
At minute 0, an infection starts from the node with value start.

Each minute, a node becomes infected if:
- The node is currently uninfected.
- The node is adjacent to an infected node.

Return the number of minutes needed for the entire tree to be infected.

Example 1:
Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.

Example 2:
Input: root = [1], start = 1
Output: 0
Explanation: At minute 0, the only node in the tree is infected so we return 0.

Constraints:
The number of nodes in the tree is in the range [1, 10^5].
1 <= Node.val <= 10^5
Each node has a unique value.
A node with a value of start exists in the tree.
```

<details><summary>Hint</summary>

```text
1. Convert the tree to an undirected graph to make it easier to handle.
2. Use BFS starting at the start node to find the distance between each node and the start node.
   The answer is the maximum distance.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX_NODE_ROW_SIZE (int)(1e5 + 4)  // 1 <= Node.val <= 10^5
#define MAX_NODE_COL_SIZE (3)             // TreeNode
void toUndirectedGraph(struct TreeNode* root, int** adjacency, int* adjacencyColSize) {
    if (root->left != NULL) {
        adjacency[root->val][adjacencyColSize[root->val]++] = root->left->val;
        adjacency[root->left->val][adjacencyColSize[root->left->val]++] = root->val;
        toUndirectedGraph(root->left, adjacency, adjacencyColSize);
    }

    if (root->right != NULL) {
        adjacency[root->val][adjacencyColSize[root->val]++] = root->right->val;
        adjacency[root->right->val][adjacencyColSize[root->right->val]++] = root->val;
        toUndirectedGraph(root->right, adjacency, adjacencyColSize);
    }
}
int amountOfTime(struct TreeNode* root, int start) {
    int retVal = 0;

    int i, j;

    //
    int* adjacencyColSize = (int*)malloc(MAX_NODE_ROW_SIZE * sizeof(int));
    if (adjacencyColSize == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(adjacencyColSize, 0, (MAX_NODE_ROW_SIZE * sizeof(int)));
    //
    int** adjacency = (int**)malloc(MAX_NODE_ROW_SIZE * sizeof(int*));
    if (adjacency == NULL) {
        perror("malloc");
        free(adjacencyColSize);
        adjacencyColSize = NULL;
        return retVal;
    }
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        adjacency[i] = (int*)malloc(MAX_NODE_COL_SIZE * sizeof(int));
        if (adjacency[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(adjacency[j]);
                adjacency[j] = NULL;
            }
            free(adjacency);
            adjacency = NULL;
            free(adjacencyColSize);
            adjacencyColSize = NULL;
            return retVal;
        }
        memset(adjacency[i], 0, (MAX_NODE_COL_SIZE * sizeof(int)));  // 1 <= Node.val <= 10^5
    }
    //
    toUndirectedGraph(root, adjacency, adjacencyColSize);
#if (0)
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        if (adjacencyColSize[i] != 0) {
            printf("%d: ", i);
            for (j = 0; j < adjacencyColSize[i]; ++j) {
                printf("%d ", adjacency[i][j]);
            }
            printf("\n");
        }
    }
#endif

    //
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueue[MAX_NODE_ROW_SIZE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueTail++] = start;
    //
    int visited[MAX_NODE_ROW_SIZE];
    memset(visited, 0, sizeof(visited));
    visited[start] = 1;
    //
    retVal = -1;
    int bfsQueueSize, leaf, neighbor;
    while (bfsQueueHead < bfsQueueTail) {
        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            leaf = bfsQueue[bfsQueueHead++];
            for (j = 0; j < adjacencyColSize[leaf]; ++j) {
                neighbor = adjacency[leaf][j];
                if (visited[neighbor] == 0) {
                    visited[neighbor] = 1;
                    bfsQueue[bfsQueueTail++] = neighbor;
                }
            }
        }
        ++retVal;
    }

    //
    for (i = 0; i < MAX_NODE_ROW_SIZE; ++i) {
        free(adjacency[i]);
        adjacency[i] = NULL;
    }
    free(adjacency);
    adjacency = NULL;
    free(adjacencyColSize);
    adjacencyColSize = NULL;

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    void toUndirectedGraph(TreeNode* root, unordered_map<int, vector<int>>& adjacency) {
        if (root->left != nullptr) {
            adjacency[root->val].emplace_back(root->left->val);
            adjacency[root->left->val].emplace_back(root->val);
            toUndirectedGraph(root->left, adjacency);
        }

        if (root->right != nullptr) {
            adjacency[root->val].emplace_back(root->right->val);
            adjacency[root->right->val].emplace_back(root->val);
            toUndirectedGraph(root->right, adjacency);
        }
    }
    int amountOfTime(TreeNode* root, int start) {
        int retVal = 0;

        unordered_map<int, vector<int>> adjacency;
        toUndirectedGraph(root, adjacency);

        queue<int> bfsQueue;
        bfsQueue.push(start);
        unordered_set<int> visited;
        visited.insert(start);

        retVal = -1;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                int leaf = bfsQueue.front();
                bfsQueue.pop();
                for (int neighbor : adjacency[leaf]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        bfsQueue.push(neighbor);
                    }
                }
            }
            retVal++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self) -> None:
        self.adjacency = None

    def toUndirectedGraph(self, root: Optional[TreeNode]) -> None:
        if root.left:
            self.adjacency[root.val].append(root.left.val)
            self.adjacency[root.left.val].append(root.val)
            self.toUndirectedGraph(root.left)

        if root.right:
            self.adjacency[root.val].append(root.right.val)
            self.adjacency[root.right.val].append(root.val)
            self.toUndirectedGraph(root.right)

    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        retVal = 0

        self.adjacency = defaultdict(list)
        self.toUndirectedGraph(root)

        bfsQueue = deque([start])
        visited = set()
        visited.add(start)

        retVal = -1
        while bfsQueue:
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                leaf = bfsQueue.popleft()
                for neighbor in self.adjacency[leaf]:
                    if neighbor in visited:
                        continue
                    visited.add(neighbor)
                    bfsQueue.append(neighbor)
            retVal += 1

        return retVal
```

</details>

## [2415. Reverse Odd Levels of Binary Tree](https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/)  1431

- [Official](https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/reverse-odd-levels-of-binary-tree/solutions/2562073/fan-zhuan-er-cha-shu-de-qi-shu-ceng-by-l-n034/)

<details><summary>Description</summary>

```text
Given the root of a perfect binary tree, reverse the node values at each odd level of the tree.
- For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18], then it should become [18,29,11,7,4,3,1,2].

Return the root of the reversed tree.

A binary tree is perfect if all parent nodes have two children and all leaves are on the same level.
The level of a node is the number of edges along the path between it and the root node.

Example 1:
     2              2
   /   \          /   \
  3     5        5     3
 /\     /\      /\     /\
8  13 21  34   8  13 21  34
Input: root = [2,3,5,8,13,21,34]
Output: [2,5,3,8,13,21,34]
Explanation:
The tree has only one odd level.
The nodes at level 1 are 3, 5 respectively, which are reversed and become 5, 3.

Example 2:
   7         7
  / \       / \
13   11   11   13
Input: root = [7,13,11]
Output: [7,11,13]
Explanation:
The nodes at level 1 are 13, 11, which are reversed and become 11, 13.

Example 3:
Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
Explanation:
The odd levels have non-zero values.
The nodes at level 1 were 1, 2, and are 2, 1 after the reversal.
The nodes at level 3 were 1, 1, 1, 1, 2, 2, 2, 2, and are 2, 2, 2, 2, 1, 1, 1, 1 after the reversal.

Constraints:
The number of nodes in the tree is in the range [1, 2^14].
0 <= Node.val <= 10^5
root is a perfect binary tree.
```

<details><summary>Hint</summary>

```text
1. Try to solve recursively for each level independently.
2. While performing a depth-first search, pass the left and right nodes (which should be paired) to the next level.
   If the current level is odd, then reverse their values, or else recursively move to the next level.
```

</details>

</details>

<details><summary>C</summary>

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* reverseOddLevels(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    int bfsQueueSize = 1 << 14;  // The number of nodes in the tree is in the range [1, 2^14].
    struct TreeNode* bfsQueue[bfsQueueSize];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail++] = pRetVal;

    int left, right, temp;
    struct TreeNode* pNode;
    int currentLevelNodesSize;
    int level = 0;
    while (bfsQueueTail > bfsQueueHead) {
        currentLevelNodesSize = bfsQueueTail - bfsQueueHead;
        struct TreeNode* currentLevelNodes[currentLevelNodesSize];
        for (int i = 0; i < currentLevelNodesSize; i++) {
            pNode = bfsQueue[bfsQueueHead++];

            currentLevelNodes[i] = pNode;
            if (pNode->left) {
                bfsQueue[bfsQueueTail++] = pNode->left;
            }
            if (pNode->right) {
                bfsQueue[bfsQueueTail++] = pNode->right;
            }
        }

        if (level % 2 == 1) {
            left = 0;
            right = currentLevelNodesSize - 1;
            while (left < right) {
                temp = currentLevelNodes[left]->val;
                currentLevelNodes[left]->val = currentLevelNodes[right]->val;
                currentLevelNodes[right]->val = temp;
                left++;
                right--;
            }
        }

        level++;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        TreeNode* retVal = root;

        if (retVal == nullptr) {
            return retVal;
        }

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(retVal);

        int level = 0;
        while (bfsQueue.empty() == false) {
            vector<TreeNode*> currentLevelNodes;
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; i++) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();

                currentLevelNodes.push_back(node);
                if (node->left) {
                    bfsQueue.push(node->left);
                }
                if (node->right) {
                    bfsQueue.push(node->right);
                }
            }

            if (level % 2 == 1) {
                int left = 0;
                int right = currentLevelNodes.size() - 1;
                while (left < right) {
                    int temp = currentLevelNodes[left]->val;
                    currentLevelNodes[left]->val = currentLevelNodes[right]->val;
                    currentLevelNodes[right]->val = temp;
                    left++;
                    right--;
                }
            }

            level++;
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if not retVal:
            return retVal

        bfsQueue = [retVal]

        level = 0
        while bfsQueue:
            currentLevelNodes = []
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                node = bfsQueue.pop(0)

                currentLevelNodes.append(node)
                if node.left:
                    bfsQueue.append(node.left)
                if node.right:
                    bfsQueue.append(node.right)

            if level % 2 == 1:
                left = 0
                right = len(currentLevelNodes) - 1
                while left < right:
                    tmp = currentLevelNodes[left].val
                    currentLevelNodes[left].val = currentLevelNodes[right].val
                    currentLevelNodes[right].val = tmp
                    left += 1
                    right -= 1

            level += 1

        return retVal
```

</details>

## [2458. Height of Binary Tree After Subtree Removal Queries](https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/)  2298

- [Official](https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/editorial/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n.
You are also given an array queries of size m.

You have to perform m independent queries on the tree where in the ith query you do the following:
- Remove the subtree rooted at the node with the value queries[i] from the tree.
  It is guaranteed that queries[i] will not be equal to the value of the root.

Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.

Note:
- The queries are independent, so the tree returns to its initial state after each query.
- The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.

Example 1:
Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
Output: [2]
Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
The height of the tree is 2 (The path 1 -> 3 -> 2).

Example 2:
Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
Output: [3,2,3,2]
Explanation: We have the following queries:
- Removing the subtree rooted at node with value 3. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 4).
- Removing the subtree rooted at node with value 2. The height of the tree becomes 2 (The path 5 -> 8 -> 1).
- Removing the subtree rooted at node with value 4. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 6).
- Removing the subtree rooted at node with value 8. The height of the tree becomes 2 (The path 5 -> 9 -> 3).

Constraints:
The number of nodes in the tree is n.
2 <= n <= 10^5
1 <= Node.val <= n
All the values in the tree are unique.
m == queries.length
1 <= m <= min(n, 10^4)
1 <= queries[i] <= n
queries[i] != root.val
```

<details><summary>Hint</summary>

```text
1. Try pre-computing the answer for each node from 1 to n, and answer each query in O(1).
2. The answers can be precomputed in a single tree traversal after computing the height of each subtree.
```

</details>

</details>

<details><summary>C</summary>

```c
void traverseLeftToRight(struct TreeNode* node, int currentHeight, int* maxHeightAfterRemoval, int* currentMaxHeight) {
    if (node == NULL) {
        return;
    }

    // Store the maximum height if this node were removed
    maxHeightAfterRemoval[node->val] = (*currentMaxHeight);

    // Update the current maximum height
    (*currentMaxHeight) = fmax((*currentMaxHeight), currentHeight);

    // Traverse left subtree first, then right
    traverseLeftToRight(node->left, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
    traverseLeftToRight(node->right, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
}
void traverseRightToLeft(struct TreeNode* node, int currentHeight, int* maxHeightAfterRemoval, int* currentMaxHeight) {
    if (node == NULL) {
        return;
    }

    // Update the maximum height if this node were removed
    maxHeightAfterRemoval[node->val] = fmax(maxHeightAfterRemoval[node->val], (*currentMaxHeight));

    // Update the current maximum height
    (*currentMaxHeight) = fmax(currentHeight, (*currentMaxHeight));

    // Traverse right subtree first, then left
    traverseRightToLeft(node->right, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
    traverseRightToLeft(node->left, currentHeight + 1, maxHeightAfterRemoval, currentMaxHeight);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* treeQueries(struct TreeNode* root, int* queries, int queriesSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // Array to store the maximum height of the tree after removing each node
    int* maxHeightAfterRemoval = (int*)malloc(100001 * sizeof(int));
    if (maxHeightAfterRemoval == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(maxHeightAfterRemoval, 0, (100001 * sizeof(int)));
    int currentMaxHeight = 0;
    traverseLeftToRight(root, 0, maxHeightAfterRemoval, &currentMaxHeight);
    currentMaxHeight = 0;
    traverseRightToLeft(root, 0, maxHeightAfterRemoval, &currentMaxHeight);

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (queriesSize * sizeof(int)));

    int i;
    for (i = 0; i < queriesSize; ++i) {
        pRetVal[(*returnSize)++] = maxHeightAfterRemoval[queries[i]];
    }
    free(maxHeightAfterRemoval);
    maxHeightAfterRemoval = NULL;

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   private:
    void traverseLeftToRight(TreeNode* node, int currentHeight) {
        if (node == nullptr) {
            return;
        }

        // Store the maximum height if this node were removed
        maxHeightAfterRemoval[node->val] = currentMaxHeight;

        // Update the current maximum height
        currentMaxHeight = max(currentMaxHeight, currentHeight);

        // Traverse left subtree first, then right
        traverseLeftToRight(node->left, currentHeight + 1);
        traverseLeftToRight(node->right, currentHeight + 1);
    }
    void traverseRightToLeft(TreeNode* node, int currentHeight) {
        if (node == nullptr) {
            return;
        }

        // Update the maximum height if this node were removed
        maxHeightAfterRemoval[node->val] = max(maxHeightAfterRemoval[node->val], currentMaxHeight);

        // Update the current maximum height
        currentMaxHeight = max(currentHeight, currentMaxHeight);

        // Traverse right subtree first, then left
        traverseRightToLeft(node->right, currentHeight + 1);
        traverseRightToLeft(node->left, currentHeight + 1);
    }

   public:
    int maxHeightAfterRemoval[100001];  // Array to store the maximum height of the tree after removing each node
    int currentMaxHeight = 0;

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> retVal;

        currentMaxHeight = 0;
        traverseLeftToRight(root, 0);
        currentMaxHeight = 0;
        traverseRightToLeft(root, 0);

        for (int querie : queries) {
            retVal.emplace_back(maxHeightAfterRemoval[querie]);
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self) -> None:
        self.currentMaxHeight = 0
        self.maxHeightAfterRemoval = []

    def traverseLeftToRight(self, node, currentHeight):
        if not node:
            return

        # Store the maximum height if this node were removed
        self.maxHeightAfterRemoval[node.val] = self.currentMaxHeight

        # Update the current maximum height
        self.currentMaxHeight = max(self.currentMaxHeight, currentHeight)

        # Traverse left subtree first, then right
        self.traverseLeftToRight(node.left, currentHeight + 1)
        self.traverseLeftToRight(node.right, currentHeight + 1)

    def traverseRightToLeft(self, node, currentHeight):
        if not node:
            return

        # Update the maximum height if this node were removed
        self.maxHeightAfterRemoval[node.val] = max(self.maxHeightAfterRemoval[node.val], self.currentMaxHeight)

        # Update the current maximum height
        self.currentMaxHeight = max(currentHeight, self.currentMaxHeight)

        # Traverse right subtree first, then left
        self.traverseRightToLeft(node.right, currentHeight + 1)
        self.traverseRightToLeft(node.left, currentHeight + 1)

    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        retVal = []

        self.maxHeightAfterRemoval = [0] * 100001
        self.currentMaxHeight = 0
        self.traverseLeftToRight(root, 0)
        self.currentMaxHeight = 0
        self.traverseRightToLeft(root, 0)

        for querie in queries:
            retVal.append(self.maxHeightAfterRemoval[querie])

        return retVal
```

</details>

## [2583. Kth Largest Sum in a Binary Tree](https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/)  1374

- [Official](https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/kth-largest-sum-in-a-binary-tree/solutions/2645278/er-cha-shu-zhong-de-di-k-da-ceng-he-by-l-948i/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree and a positive integer k.

The level sum in the tree is the sum of the values of the nodes that are on the same level.

Return the kth largest level sum in the tree (not necessarily distinct).
If there are fewer than k levels in the tree, return -1.

Note that two nodes are on the same level if they have the same distance from the root.

Example 1:
Input: root = [5,8,9,2,1,3,7,4,6], k = 2
Output: 13
Explanation: The level sums are the following:
- Level 1: 5.
- Level 2: 8 + 9 = 17.
- Level 3: 2 + 1 + 3 + 7 = 13.
- Level 4: 4 + 6 = 10.
The 2nd largest level sum is 13.

Example 2:
Input: root = [1,2,null,3], k = 1
Output: 3
Explanation: The largest level sum is 3.

Constraints:
The number of nodes in the tree is n.
2 <= n <= 10^5
1 <= Node.val <= 10^6
1 <= k <= n
```

<details><summary>Hint</summary>

```text
1. Find the sum of values of nodes on each level and return the kth largest one.
2. To find the sum of the values of nodes on each level,
   you can use a DFS or BFS algorithm to traverse the tree and keep track of the level of each node.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_NODES_SIZE (int)(1e5)  // The number of nodes in the tree is n. 2 <= n <= 10 ^ 5
int compareLongLongInteger(const void* n1, const void* n2) {
    // descending order
    return (*(long long*)n1 < *(long long*)n2);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
long long kthLargestLevelSum(struct TreeNode* root, int k) {
    long long retVal = -1;  // If there are fewer than k levels in the tree, return -1.

    int traversalIndex = 0;
    long long traversal[MAX_NODES_SIZE];
    memset(traversal, 0, sizeof(traversal));

    int queueHead = 0;
    int queueTail = 0;
    struct TreeNode* queue[MAX_NODES_SIZE];
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = root;

    struct TreeNode* node;
    int currentLevelSize;
    long long levelSum;
    while (queueHead < queueTail) {
        levelSum = 0;

        currentLevelSize = queueTail - queueHead;
        for (int i = 1; i <= currentLevelSize; ++i) {
            node = queue[queueHead++];
            levelSum += (long long)node->val;
            if (node->left != NULL) {
                queue[queueTail++] = node->left;
            }
            if (node->right != NULL) {
                queue[queueTail++] = node->right;
            }
        }

        traversal[traversalIndex++] = levelSum;
    }

    if (k <= traversalIndex) {
        qsort(traversal, traversalIndex, sizeof(long long), compareLongLongInteger);
        retVal = traversal[k - 1];
    }

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        long long retVal = -1;  // If there are fewer than k levels in the tree, return -1.

        vector<long long> traversal;

        queue<TreeNode*> q;
        q.push(root);
        while (q.empty() == false) {
            long long levelSum = 0;

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                levelSum += (long long)node->val;
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
                }
            }

            traversal.emplace_back(levelSum);
        }

        int traversalSize = traversal.size();
        if (k <= traversalSize) {
            sort(traversal.begin(), traversal.end(), greater());
            retVal = traversal[k - 1];
        }

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        retVal = -1  # If there are fewer than k levels in the tree, return -1.

        traversal = []

        queue = deque([])
        queue.append(root)
        while queue:
            levelSum = 0

            queueSize = len(queue)
            for _ in range(queueSize):
                node = queue.popleft()
                levelSum += node.val
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)

            traversal.append(levelSum)

        traversalSize = len(traversal)
        if k <= traversalSize:
            traversal.sort(reverse=True)
            retVal = traversal[k-1]

        return retVal
```

</details>

## [2641. Cousins in Binary Tree II](https://leetcode.com/problems/cousins-in-binary-tree-ii/)  1676

- [Official](https://leetcode.com/problems/cousins-in-binary-tree-ii/editorial/)
- [Official](https://leetcode.cn/problems/cousins-in-binary-tree-ii/solutions/2626702/er-cha-shu-de-tang-xiong-di-jie-dian-ii-1b9oj/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Return the root of the modified tree.

Note that the depth of a node is the number of edges in the path from the root node to it.

Example 1:
Input: root = [5,4,9,1,10,null,7]
Output: [0,0,0,7,7,null,11]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 5 does not have any cousins so its sum is 0.
- Node with value 4 does not have any cousins so its sum is 0.
- Node with value 9 does not have any cousins so its sum is 0.
- Node with value 1 has a cousin with value 7 so its sum is 7.
- Node with value 10 has a cousin with value 7 so its sum is 7.
- Node with value 7 has cousins with values 1 and 10 so its sum is 11.

Example 2:
Input: root = [3,1,2]
Output: [0,0,0]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 3 does not have any cousins so its sum is 0.
- Node with value 1 does not have any cousins so its sum is 0.
- Node with value 2 does not have any cousins so its sum is 0.

Constraints:
The number of nodes in the tree is in the range [1, 10^5].
1 <= Node.val <= 10^4
```

<details><summary>Hint</summary>

```text
1. Use DFS two times.
2. For the first time, find the sum of values of all the levels of the binary tree.
3. For the second time,
   update the value of the node with the sum of the values of the current level - sibling node’s values.
```

</details>

</details>

<details><summary>C</summary>

```c
#define MAX_NODES_SIZE (int)(1e5)  // The number of nodes in the tree is in the range [1, 10^5].
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* replaceValueInTree(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }

    int queueHead = 0;
    int queueTail = 0;
    struct TreeNode* queue[MAX_NODES_SIZE];
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = pRetVal;

    int levelSumsIndex = 0;
    int levelSums[MAX_NODES_SIZE];
    memset(levelSums, 0, sizeof(levelSums));

    struct TreeNode* currentNode;
    int levelSize;
    int levelSum = 0;
    while (queueHead < queueTail) {
        levelSum = 0;

        levelSize = queueTail - queueHead;
        for (int i = 0; i < levelSize; ++i) {
            currentNode = queue[queueHead++];

            levelSum += currentNode->val;
            if (currentNode->left) {
                queue[queueTail++] = currentNode->left;
            }
            if (currentNode->right) {
                queue[queueTail++] = currentNode->right;
            }
        }

        levelSums[levelSumsIndex++] = levelSum;
    }

    queueHead = 0;
    queueTail = 0;
    memset(queue, 0, sizeof(queue));
    queue[queueTail++] = pRetVal;

    pRetVal->val = 0;
    int levelIndex = 1;
    int siblingSum = 0;
    while (queueHead < queueTail) {
        levelSize = queueTail - queueHead;
        for (int i = 0; i < levelSize; ++i) {
            currentNode = queue[queueHead++];

            siblingSum = 0;
            siblingSum += ((currentNode->left != NULL) ? (currentNode->left->val) : (0));
            siblingSum += ((currentNode->right != NULL) ? (currentNode->right->val) : (0));

            if (currentNode->left) {
                currentNode->left->val = levelSums[levelIndex] - siblingSum;
                queue[queueTail++] = currentNode->left;
            }
            if (currentNode->right) {
                currentNode->right->val = levelSums[levelIndex] - siblingSum;
                queue[queueTail++] = currentNode->right;
            }
        }

        ++levelIndex;
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    TreeNode *replaceValueInTree(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == nullptr) {
            return pRetVal;
        }

        queue<TreeNode *> nodeQueue;
        nodeQueue.push(pRetVal);

        vector<int> levelSums;
        while (nodeQueue.empty() == false) {
            int levelSum = 0;

            int levelSize = nodeQueue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode *currentNode = nodeQueue.front();
                nodeQueue.pop();

                levelSum += currentNode->val;
                if (currentNode->left) {
                    nodeQueue.push(currentNode->left);
                }
                if (currentNode->right) {
                    nodeQueue.push(currentNode->right);
                }
            }

            levelSums.push_back(levelSum);
        }

        nodeQueue.push(pRetVal);
        int levelIndex = 1;
        pRetVal->val = 0;
        while (nodeQueue.empty() == false) {
            int levelSize = nodeQueue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode *currentNode = nodeQueue.front();
                nodeQueue.pop();

                int siblingSum = 0;
                siblingSum += ((currentNode->left != nullptr) ? (currentNode->left->val) : (0));
                siblingSum += ((currentNode->right != nullptr) ? (currentNode->right->val) : (0));

                if (currentNode->left) {
                    currentNode->left->val = levelSums[levelIndex] - siblingSum;
                    nodeQueue.push(currentNode->left);
                }
                if (currentNode->right) {
                    currentNode->right->val = levelSums[levelIndex] - siblingSum;
                    nodeQueue.push(currentNode->right);
                }
            }

            ++levelIndex;
        }

        return pRetVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if not retVal:
            return retVal

        nodeQueue = deque([retVal])
        levelSums = []

        while nodeQueue:
            levelSum = 0

            levelSize = len(nodeQueue)
            for _ in range(levelSize):
                currentNode = nodeQueue.popleft()
                levelSum += currentNode.val
                if currentNode.left:
                    nodeQueue.append(currentNode.left)
                if currentNode.right:
                    nodeQueue.append(currentNode.right)

            levelSums.append(levelSum)

        nodeQueue.append(retVal)
        levelIndex = 1
        retVal.val = 0
        while nodeQueue:
            levelSize = len(nodeQueue)
            for _ in range(levelSize):
                currentNode = nodeQueue.popleft()

                siblingSum = 0
                if currentNode.left:
                    siblingSum += currentNode.left.val
                if currentNode.right:
                    siblingSum += currentNode.right.val

                if currentNode.left:
                    currentNode.left.val = levelSums[levelIndex] - siblingSum
                    nodeQueue.append(currentNode.left)
                if currentNode.right:
                    currentNode.right.val = levelSums[levelIndex] - siblingSum
                    nodeQueue.append(currentNode.right)

            levelIndex += 1

        return retVal
```

</details>

## [2872. Maximum Number of K-Divisible Components](https://leetcode.com/problems/maximum-number-of-k-divisible-components/)  1967

- [Official](https://leetcode.com/problems/maximum-number-of-k-divisible-components/editorial/)

<details><summary>Description</summary>

```text
There is an undirected tree with n nodes labeled from 0 to n - 1.
You are given the integer n and a 2D integer array edges of length n - 1,
where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

You are also given a 0-indexed integer array values of length n,
where values[i] is the value associated with the ith node, and an integer k.

A valid split of the tree is obtained by removing any set of edges, possibly empty,
from the tree such that the resulting components all have values that are divisible by k,
where the value of a connected component is the sum of the values of its nodes.

Return the maximum number of components in any valid split.

Example 1:
    1            1
   / \            \
  2   3  =>    2   3
 / \          / \
4   0        4   0
Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
Output: 2
Explanation: We remove the edge connecting node 1 with 2. The resulting split is valid because:
- The value of the component containing nodes 1 and 3 is values[1] + values[3] = 12.
- The value of the component containing nodes 0, 2, and 4 is values[0] + values[2] + values[4] = 6.
It can be shown that no other valid split has more than 2 connected components.

Example 2:
     0                0
   /   \
  2     1   =>     2     1
 / \   / \        / \   / \
6   5 4   3      6   5 4   3
Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
Output: 3
Explanation: We remove the edge connecting node 0 with 2, and the edge connecting node 0 with 1.
The resulting split is valid because:
- The value of the component containing node 0 is values[0] = 3.
- The value of the component containing nodes 2, 5, and 6 is values[2] + values[5] + values[6] = 9.
- The value of the component containing nodes 1, 3, and 4 is values[1] + values[3] + values[4] = 6.
It can be shown that no other valid split has more than 3 connected components.

Constraints:
1 <= n <= 3 * 10^4
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
values.length == n
0 <= values[i] <= 10^9
1 <= k <= 10^9
Sum of values is divisible by k.
The input is generated such that edges represents a valid tree.
```

<details><summary>Hint</summary>

```text
1. Root the tree at node 0.
2. If a leaf node is not divisible by k,
   it must be in the same component as its parent node so we merge it with its parent node.
3. If a leaf node is divisible by k, it will be in its own components so we separate it from its parent node.
4. In each step, we either cut a leaf node down or merge a leaf node.
   The number of nodes on the tree reduces by one. Repeat this process until only one node is left.
```

</details>

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/maximum-number-of-k-divisible-components/solutions/2464541/ke-yi-bei-k-zheng-chu-lian-tong-kuai-de-o8jw6/
struct ChildNode {
    int child;
    struct ChildNode* next;
};
long long dfs(struct ChildNode** head, int* values, int root, int father, int k, int* result) {
    long long retVal = values[root];

    long long subSum = 0;
    struct ChildNode* node = NULL;
    for (node = head[root]; NULL != node; node = node->next) {
        if (father != node->child) {
            subSum = dfs(head, values, node->child, root, k, result);
            retVal += subSum;
        }
    }
    if (0 == retVal % k) {
        (*result)++;
    }

    return retVal;
}
int maxKDivisibleComponents(int n, int** edges, int edgesSize, int* edgesColSize, int* values, int valuesSize, int k) {
    int retVal = 0;

    int buffSize = n << 1;
    struct ChildNode buff[buffSize];
    memset(buff, 0, sizeof(buff));

    struct ChildNode* head[n];
    memset(head, 0, sizeof(head));

    int x = 0, y = 0;
    for (x = 0; edgesSize > x; x++) {
        buff[y].child = edges[x][1];
        buff[y].next = head[edges[x][0]];
        head[edges[x][0]] = &buff[y];
        y++;

        buff[y].child = edges[x][0];
        buff[y].next = head[edges[x][1]];
        head[edges[x][1]] = &buff[y];
        y++;
    }

    int root = 0;
    dfs(head, values, root, -1, k, &retVal);

    return retVal;
}
```

</details>

<details><summary>C++</summary>

```c++
class Solution {
   public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        int retVal = 1;

        // Base case: if there are less than 2 nodes, return 1
        if (n < 2) {
            return retVal;
        }

        // Step 1: Build the graph
        unordered_map<int, unordered_set<int>> graph;
        for (const auto& edge : edges) {
            int node1 = edge[0];
            int node2 = edge[1];
            graph[node1].insert(node2);
            graph[node2].insert(node1);
        }

        // Convert values to long long to prevent overflow
        vector<long long> longValues(values.begin(), values.end());

        // Step 2: Initialize the BFS queue with leaf nodes (nodes with only one connection)
        queue<int> bfsQueue;
        for (const auto& [node, neighbors] : graph) {
            if (neighbors.size() == 1) {
                bfsQueue.push(node);
            }
        }

        // Step 3: Process nodes in BFS order
        int componentCount = 0;
        while (bfsQueue.empty() == false) {
            int currentNode = bfsQueue.front();
            bfsQueue.pop();

            // Find the neighbor node
            int neighborNode = -1;
            if (graph[currentNode].empty() == false) {
                neighborNode = *graph[currentNode].begin();
            }

            // Remove the edge between current and neighbor
            if (neighborNode >= 0) {
                graph[neighborNode].erase(currentNode);
                graph[currentNode].erase(neighborNode);
            }

            // Check divisibility of the current node's value
            if (longValues[currentNode] % k == 0) {
                componentCount++;
            } else if (neighborNode >= 0) {
                // Add current node's value to the neighbor
                longValues[neighborNode] += longValues[currentNode];
            }

            // If the neighbor becomes a leaf node, add it to the BFS queue
            int graphNeighborNodeSize = graph[neighborNode].size();
            if ((neighborNode >= 0) && (graphNeighborNodeSize == 1)) {
                bfsQueue.push(neighborNode);
            }
        }

        retVal = componentCount;

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
class Solution:
    def maxKDivisibleComponents(self, n: int, edges: List[List[int]], values: List[int], k: int) -> int:
        retVal = 1

        # Base case: if there are less than 2 nodes, return 1
        if n < 2:
            return retVal

        # Step 1: Build the graph
        graph = defaultdict(set)
        for node1, node2 in edges:
            graph[node1].add(node2)
            graph[node2].add(node1)

        # Step 2: Initialize the BFS queue with leaf nodes (nodes with only one connection)
        nodes = []
        for node, neighbors in graph.items():
            if len(neighbors) == 1:
                nodes.append(node)
        bfsQueue = deque(nodes)

        # Step 3: Process nodes in BFS order
        componentCount = 0
        while bfsQueue:
            currentNode = bfsQueue.popleft()

            # Find the neighbor node
            neighborNode = -1
            if graph[currentNode]:
                neighborNode = next(iter(graph[currentNode]))

            # Remove the edge between current and neighbor
            if neighborNode >= 0:
                graph[neighborNode].remove(currentNode)

            # Check divisibility of the current node's value
            if values[currentNode] % k == 0:
                componentCount += 1
            else:
                # Add current node's value to the neighbor
                values[neighborNode] += values[currentNode]

            # If the neighbor becomes a leaf node, add it to the BFS queue
            if (neighborNode >= 0) and (len(graph[neighborNode]) == 1):
                bfsQueue.append(neighborNode)

        retVal = componentCount

        return retVal
```

</details>
