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

## [2196. Create Binary Tree From Descriptions](https://leetcode.com/problems/create-binary-tree-from-descriptions/)  1643

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
