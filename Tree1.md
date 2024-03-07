# Tree

## [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)

- [Official](https://leetcode.com/problems/binary-tree-inorder-traversal/editorial/)
- [Official](https://leetcode.cn/problems/binary-tree-inorder-traversal/solutions/412886/er-cha-shu-de-zhong-xu-bian-li-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
1
 \
  2
 /
3
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up: Recursive solution is trivial, could you do it iteratively?
```

</details>

<details><summary>C</summary>

```c
#define RECURSIVE (0)
#define ITERATIVE (1)
void inorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
#if (RECURSIVE)
    printf("RECURSIVE\n");

    if (root == NULL) {
        return;
    }
    inorder(root->left, pTreeNodeCount, pTreeArray);
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    inorder(root->right, pTreeNodeCount, pTreeArray);
#elif (ITERATIVE)
    printf("ITERATIVE\n");

    // The number of nodes in the tree is in the range [0, 100].
    struct TreeNode** stackKeep = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 100);
    int top = 0;
    while ((root != NULL) || (top > 0)) {
        while (root != NULL) {
            stackKeep[top++] = root;
            root = root->left;
        }
        root = stackKeep[--top];
        *(pTreeArray + (*pTreeNodeCount)) = root->val;
        (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
        root = root->right;
    }

    free(stackKeep);
    stackKeep = NULL;
#endif
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
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 100].
    pRetVal = (int*)malloc(100 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    inorder(root, returnSize, pRetVal);

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
#define RECURSIVE (0)
#define ITERATIVE (1)
   public:
    Solution() {
#if (RECURSIVE)
        cout << "RECURSIVE\n\n";
#elif (ITERATIVE)
        cout << "ITERATIVE\n\n";
#endif
    }
    void inorder(TreeNode* root, vector<int>& retVal) {
#if (RECURSIVE)
        if (root == nullptr) {
            return;
        }
        inorder(root->left, retVal);
        retVal.push_back(root->val);
        inorder(root->right, retVal);
#elif (ITERATIVE)
        stack<TreeNode*> stackKeep;
        while ((root != nullptr) || (stackKeep.empty() == false)) {
            while (root != nullptr) {
                stackKeep.push(root);
                root = root->left;
            }
            root = stackKeep.top();
            stackKeep.pop();
            retVal.push_back(root->val);
            root = root->right;
        }
#endif
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> retVal;

        inorder(root, retVal);

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
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        retVal.extend(self.inorderTraversal(root.left))
        retVal.append(root.val)
        retVal.extend(self.inorderTraversal(root.right))

        return retVal
```

</details>

## [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)

- [Official](https://leetcode.com/problems/unique-binary-search-trees-ii/editorial/)
- [Official](https://leetcode.cn/problems/unique-binary-search-trees-ii/solutions/339143/bu-tong-de-er-cha-sou-suo-shu-ii-by-leetcode-solut/)

<details><summary>Description</summary>

```text
Given an integer n, return all the structurally unique BST's (binary search trees),
which has exactly n nodes of unique values from 1 to n.
Return the answer in any order.

Example 1:
Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

Example 2:
Input: n = 1
Output: [[1]]

Constraints:
1 <= n <= 8
```

</details>

<details><summary>C</summary>

```c
struct TreeNode** buildTree(int start, int end, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    if (start > end) {
        (*returnSize) = 1;
        pRetVal = malloc(sizeof(struct TreeNode*));
        pRetVal[0] = NULL;

        return pRetVal;
    }

    struct TreeNode** allTrees = (struct TreeNode**)malloc(0);
    struct TreeNode** leftTrees;
    int left;
    int leftTreesSize;
    struct TreeNode** rightTrees;
    int right;
    int rightTreesSize;
    struct TreeNode* pCurrTree;
    int i;
    for (i = start; i <= end; i++) {
        leftTrees = buildTree(start, i - 1, &leftTreesSize);
        rightTrees = buildTree(i + 1, end, &rightTreesSize);

        for (left = 0; left < leftTreesSize; left++) {
            for (right = 0; right < rightTreesSize; right++) {
                pCurrTree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                pCurrTree->val = i;
                pCurrTree->left = leftTrees[left];
                pCurrTree->right = rightTrees[right];

                (*returnSize)++;
                allTrees = (struct TreeNode**)realloc(allTrees, sizeof(struct TreeNode*) * (*returnSize));
                allTrees[(*returnSize) - 1] = pCurrTree;
            }
        }
        free(rightTrees);
        rightTrees = NULL;
        free(leftTrees);
        leftTrees = NULL;
    }
    return allTrees;
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
struct TreeNode** generateTrees(int n, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    (*returnSize) = 0;

    if (n == 0) {
        return pRetVal;
    }
    pRetVal = buildTree(1, n, returnSize);

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
    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> retVal;

        if (start > end) {
            retVal = {nullptr};
            return retVal;
        }

        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, end);

            for (auto& left : leftTrees) {
                for (auto& right : rightTrees) {
                    TreeNode* currTree = new TreeNode(i);
                    currTree->left = left;
                    currTree->right = right;
                    retVal.emplace_back(currTree);
                }
            }
        }

        return retVal;
    }
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> retVal;

        if (n == 0) {
            return retVal;
        }
        retVal = generateTrees(1, n);

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
    def generateTrees(self, n: int) -> List[Optional[TreeNode]]:
        retVal = []

        def generateTrees(start, end):
            if start > end:
                return [None,]

            allTrees = []
            for i in range(start, end + 1):
                leftTrees = generateTrees(start, i - 1)
                rightTrees = generateTrees(i + 1, end)
                for l in leftTrees:
                    for r in rightTrees:
                        currTree = TreeNode(i)
                        currTree.left = l
                        currTree.right = r
                        allTrees.append(currTree)
            return allTrees

        retVal = generateTrees(1, n) if n else []

        return retVal
```

</details>

## [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

<details><summary>Description</summary>

```text
Given an integer n, return the number of structurally unique BST's (binary search trees)
which has exactly n nodes of unique values from 1 to n.

Example 1:
Input: n = 3
Output: 5

Example 2:
Input: n = 1
Output: 1

Constraints:
1 <= n <= 19
```

</details>

<details><summary>C</summary>

```c
int numTrees(int n) {
    int retVal = 1;

/* Catalan number
 *  f(n) = f(0)f(n-1) + f(1)f(n-2) + f(2)f(n-3) + ... + f(n-1)f(0)
 *  C_n = C (2n, n) / (n+1) = (2n)! / (n! * (n+1)!)
 *  C_n+1 = (2x(2n+1) / (n+2))  x C_n, C_0 = 1.
 *  1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862,
 *  16796, 58786, 208012, 742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190
 *  https://en.wikipedia.org/wiki/Catalan_number
 */
#if 1  // f(n) = f(0)f(n-1) + f(1)f(n-2) + f(2)f(n-3) + ... + f(n-1)f(0)
    if ((n == 0) || (n == 1)) {
        return retVal;
    }

#define MAX_SIZW 20
    int CATALAN[MAX_SIZW] = {0};
    CATALAN[0] = 1;
    CATALAN[1] = 1;
    int i, j;
    for (i = 2; i <= n; ++i) {
        for (j = 0; j < i; ++j) {
            CATALAN[i] += (CATALAN[j] * CATALAN[i - j - 1]);
        }
    }
    retVal = CATALAN[n];
#else  // C_n+1 = (2x(2n+1) / (n+2))  x C_n, C_0 = 1.
    if (n == 0) {
        return retVal;
    }

    long tmp = retVal;
    int idx;
    int i;
    for (i = 1; i <= n; ++i) {
        idx = i - 1;
        tmp = tmp * (2 * (2 * idx + 1)) / (idx + 2);
    }
    retVal = tmp;
#endif

    return retVal;
}
```

</details>

## [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
  1
 / \
2   3
Input: root = [2,1,3]
Output: true

Example 2:
  5
 / \
1   4
   / \
  3   6
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-2^31 <= Node.val <= 2^31 - 1
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
void inOrder(struct TreeNode* pRoot, long* pMin) {
    if (pRoot != NULL) {
        inOrder(pRoot->left, pMin);
        if ((long)(pRoot->val) > *pMin) {
            *pMin = pRoot->val;
        }
        else {
            *pMin = LONG_MAX;
        }
        inOrder(pRoot->right, pMin);
    }
}

bool isValidBST(struct TreeNode* root) {
    bool retVal = true;

    long minLeaf = LONG_MIN;
    inOrder(root, &minLeaf);
    if (minLeaf == LONG_MAX) {
        retVal = false;
    }

    return retVal;
}
```

</details>

## [100. Same Tree](https://leetcode.com/problems/same-tree/)

- [Official](https://leetcode.cn/problems/same-tree/solutions/363636/xiang-tong-de-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

Example 1:
  1       1
 / \     / \
2   3   2   3
Input: p = [1,2,3], q = [1,2,3]
Output: true

Example 2:
  1   1
 /     \
2       2
Input: p = [1,2], q = [1,null,2]
Output: false

Example 3:
  1       1
 / \     / \
2   1   1   2
Input: p = [1,2,1], q = [1,1,2]
Output: false

Constraints:
The number of nodes in both trees is in the range [0, 100].
-10^4 <= Node.val <= 10^4
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
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    bool retVal = false;

    if ((p == NULL) && (q == NULL)) {
        retVal = true;
        return retVal;
    } else if ((p == NULL) && (q != NULL)) {
        return retVal;
    } else if ((p != NULL) && (q == NULL)) {
        return retVal;
    }

    if (isSameTree(p->left, q->left) == false) {
        return retVal;
    }
    if (p->val != q->val) {
        return retVal;
    }
    if (isSameTree(p->right, q->right) == false) {
        return retVal;
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool retVal = false;

        if ((p == nullptr) && (q == nullptr)) {
            retVal = true;
            return retVal;
        } else if ((p == nullptr) && (q != nullptr)) {
            return retVal;
        } else if ((p != nullptr) && (q == nullptr)) {
            return retVal;
        }

        if (isSameTree(p->left, q->left) == false) {
            return retVal;
        }
        if (p->val != q->val) {
            return retVal;
        }
        if (isSameTree(p->right, q->right) == false) {
            return retVal;
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
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        retVal = False

        if (p is None) and (q is None):
            retVal = True
            return retVal
        elif (p is None) and (q is not None):
            return retVal
        elif (p is not None) and (q is None):
            return retVal

        if self.isSameTree(p.left, q.left) == False:
            return retVal
        if p.val != q.val:
            return retVal
        if self.isSameTree(p.right, q.right) == False:
            return retVal
        retVal = True

        return retVal
```

</details>

## [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/)

- [Official](https://leetcode.cn/problems/symmetric-tree/solutions/268109/dui-cheng-er-cha-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Example 1:
       1
     /   \
    2     2
   / \   / \
  3   4 4   3
Input: root = [1,2,2,3,4,4,3]
Output: true

Example 2:
  1
 / \
2   2
 \   \
  3   3
Input: root = [1,2,2,null,3,null,3]
Output: false

Constraints:
The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100

Follow up: Could you solve it both recursively and iteratively?
```

</details>

<details><summary>C</summary>

```c
bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    bool retVal = false;

    if ((left == NULL) && (right == NULL)) {
        retVal = true;
        return retVal;
    } else if ((left == NULL) || (right == NULL)) {
        return retVal;
    } else if (left->val != right->val) {
        return retVal;
    }
    retVal = (isMirror(left->left, right->right)) && (isMirror(left->right, right->left));

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
bool isSymmetric(struct TreeNode* root) {
    bool retVal = true;

    if (root == NULL) {
        return retVal;
    }
    retVal = isMirror(root->left, root->right);

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
    bool isMirror(TreeNode* left, TreeNode* right) {
        bool retVal = false;

        if ((left == nullptr) && (right == nullptr)) {
            retVal = true;
            return retVal;
        } else if ((left == nullptr) || (right == nullptr)) {
            return retVal;
        } else if (left->val != right->val) {
            return retVal;
        }
        retVal = (isMirror(left->left, right->right) && isMirror(left->right, right->left));

        return retVal;
    }
    bool isSymmetric(TreeNode* root) {
        bool retVal = true;

        if (root == nullptr) {
            return retVal;
        }
        retVal = isMirror(root->left, root->right);

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
    def isMirror(self, left: Optional[TreeNode], right: Optional[TreeNode]) -> bool:
        retVal = False

        if (left is None) and (right is None):
            retVal = True
            return retVal
        elif (left is None) or (right is None):
            return retVal
        elif left.val != right.val:
            return retVal

        ret1 = self.isMirror(left.left, right.right)
        ret2 = self.isMirror(left.right, right.left)
        retVal = ret1 and ret2

        return retVal

    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        if root is None:
            return retVal
        retVal = self.isMirror(root.left, root.right)

        return retVal
```

</details>

## [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

- [Official](https://leetcode.cn/problems/binary-tree-level-order-traversal/solutions/241885/er-cha-shu-de-ceng-xu-bian-li-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the level order traversal of its nodes' values.
(i.e., from left to right, level by level).

Example 1:
  3
 / \
9   20
   /  \
 15    7
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
```

</details>

<details><summary>C</summary>

```c
int treeHeight(struct TreeNode* pRoot) {
    if (pRoot == NULL) {
        return 0;
    }

    int leftHeight = treeHeight(pRoot->left);
    int rightHeight = treeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}
void treeLevel(struct TreeNode* pRoot, int level, int* pReturnArray, int* pReturnArrayIndex) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        if (pReturnArray != NULL) {
            pReturnArray[(*pReturnArrayIndex)] = pRoot->val;
        }
        (*pReturnArrayIndex)++;
    } else {
        treeLevel(pRoot->left, level - 1, pReturnArray, pReturnArrayIndex);
        treeLevel(pRoot->right, level - 1, pReturnArray, pReturnArrayIndex);
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    if (root == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    (*returnSize) = treeHeight(root);
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int i;
    int index;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        pRetVal[level] = NULL;
        index = 0;
        treeLevel(root, level, pRetVal[level], &index);

        (*returnColumnSizes)[level] = index;
        pRetVal[level] = (int*)malloc(((*returnColumnSizes)[level]) * sizeof(int));
        if (pRetVal[level] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < level - 1; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            (*returnSize) = 0;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[level], 0, ((*returnColumnSizes)[level]) * sizeof(int));

        index = 0;
        treeLevel(root, level, pRetVal[level], &index);
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
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> retVal;

        if (root == NULL) {
            return retVal;
        }

        queue<TreeNode *> q;
        q.push(root);
        while (q.empty() == false) {
            retVal.push_back(vector<int>());

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                retVal.back().push_back(node->val);
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
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
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        retVal = []

        if root == None:
            return retVal

        queue = deque([])
        queue.append(root)

        while queue:
            levelVal = []
            for _ in range(len(queue)):
                node = queue.popleft()
                levelVal.append(node.val)
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)
            retVal.append(levelVal)

        return retVal
```

</details>

## [103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)

- [Official](https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/solutions/530400/er-cha-shu-de-ju-chi-xing-ceng-xu-bian-l-qsun/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values.
(i.e., from left to right, then right to left for the next level and alternate between).

Example 1:
  3
 / \
9   20
   /  \
 15    7
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:
Input: root = [1]
Output: [[1]]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
```

</details>

<details><summary>C</summary>

```c
int treeHeight(struct TreeNode* pRoot) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    int leftHeight = treeHeight(pRoot->left);
    int rightHeight = treeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        retVal = leftHeight + 1;
    } else {
        retVal = rightHeight + 1;
    }

    return retVal;
}
void treeLevel(struct TreeNode* pRoot, int level, int* startLevel, int* pReturnArray, int* pReturnArrayIndex) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        if (pReturnArray != NULL) {
            pReturnArray[(*pReturnArrayIndex)] = pRoot->val;
        }
        (*pReturnArrayIndex)++;
        return;
    }

    if ((*startLevel) % 2 == 0) {
        treeLevel(pRoot->left, level - 1, startLevel, pReturnArray, pReturnArrayIndex);
        treeLevel(pRoot->right, level - 1, startLevel, pReturnArray, pReturnArrayIndex);
    } else if ((*startLevel) % 2 == 1) {
        treeLevel(pRoot->right, level - 1, startLevel, pReturnArray, pReturnArrayIndex);
        treeLevel(pRoot->left, level - 1, startLevel, pReturnArray, pReturnArrayIndex);
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    if (root == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    (*returnSize) = treeHeight(root);
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int i;
    int index;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        pRetVal[level] = NULL;
        index = 0;
        treeLevel(root, level, &level, pRetVal[level], &index);

        (*returnColumnSizes)[level] = index;
        pRetVal[level] = (int*)malloc(((*returnColumnSizes)[level]) * sizeof(int));
        if (pRetVal[level] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < level - 1; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            (*returnSize) = 0;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[level], 0, ((*returnColumnSizes)[level]) * sizeof(int));

        index = 0;
        treeLevel(root, level, &level, pRetVal[level], &index);
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> retVal;

        if (root == NULL) {
            return retVal;
        }

        int level = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (q.empty() == false) {
            retVal.push_back(vector<int>());

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                retVal.back().push_back(node->val);
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
                }
            }
            if (level % 2 == 1) {
                reverse(retVal.back().begin(), retVal.back().end());
            }

            ++level;
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
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        retVal = []

        if root == None:
            return retVal

        queue = deque([])
        queue.append(root)
        while queue:
            tmp = []
            for _ in range(len(queue)):
                node = queue.popleft()
                tmp.append(node.val)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            if len(retVal) % 2 == 1:
                retVal.append(tmp[::-1])
            else:
                retVal.append(tmp)

        return retVal
```

</details>

## [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

- [Official](https://leetcode.cn/problems/maximum-depth-of-binary-tree/solutions/349250/er-cha-shu-de-zui-da-shen-du-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path
from the root node down to the farthest leaf node.

Example 1:
     3
    / \
   9   20
  / \
15   7
Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:
Input: root = [1,null,2]
Output: 2

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-100 <= Node.val <= 100
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
int maxDepth(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    retVal = (left > right ? left : right) + 1;

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
    int maxDepth(TreeNode* root) {
        int retVal = 0;

        if (root == NULL) {
            return retVal;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        retVal = max(left, right) + 1;

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
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        left = self.maxDepth(root.left)
        right = self.maxDepth(root.right)
        retVal = max(left, right) + 1

        return retVal
```

</details>

## [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

- [Official](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solutions/255811/cong-qian-xu-yu-zhong-xu-bian-li-xu-lie-gou-zao-9/)

<details><summary>Description</summary>

```text
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree
and inorder is the inorder traversal of the same tree, construct and return the binary tree.

Example 1:
     3
    / \
   9   20
  / \
15   7
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]

Constraints:
1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
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
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    struct TreeNode* pRetVal = NULL;

    if (preorderSize == 0) {
        return pRetVal;
    }

    int preorderIndex = preorderSize;
    int inorderIndex = 0;
    struct TreeNode* stack[preorderSize];
    int stackTop = -1;

    /* Example
     *      (3)        v  pre: 3  9 20 15  7
     *   (9)   (20)    v   in: 9  3 15 20  7
     *      (15)  (7)    post: 9 15  7 20  3
     */
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = preorder[0];
    pRetVal->left = NULL;
    pRetVal->right = NULL;
    stack[++stackTop] = pRetVal;

    int preorderVal;
    struct TreeNode* pTop;
    int i;
    for (i = 1; i < preorderIndex; ++i) {
        preorderVal = preorder[i];
        pTop = stack[stackTop];
        if (pTop->val != inorder[inorderIndex]) {
            pTop->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->left == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->left->val = preorderVal;
            pTop->left->left = NULL;
            pTop->left->right = NULL;
            stack[++stackTop] = pTop->left;
        } else {
            while ((stackTop != -1) && (stack[stackTop]->val == inorder[inorderIndex])) {
                pTop = stack[stackTop--];
                ++inorderIndex;
            }
            pTop->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->right == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->right->val = preorderVal;
            pTop->right->left = NULL;
            pTop->right->right = NULL;
            stack[++stackTop] = pTop->right;
        }
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* pRetVal = nullptr;

        if (preorder.size() == 0) {
            return pRetVal;
        }

        int preorderIndex = preorder.size();
        int inorderIndex = 0;
        stack s = stack<TreeNode*>();

        /* Example
         *      (3)        v  pre: 3  9 20 15  7
         *   (9)   (20)    v   in: 9  3 15 20  7
         *      (15)  (7)    post: 9 15  7 20  3
         */
        pRetVal = new TreeNode(preorder[0]);
        s.push(pRetVal);
        for (int i = 1; i < preorderIndex; ++i) {
            int preorderVal = preorder[i];
            auto node = s.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                s.push(node->left);
            } else {
                while ((s.empty() == false) && (s.top()->val == inorder[inorderIndex])) {
                    node = s.top();
                    s.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                s.push(node->right);
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
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        retVal = None

        inorderSize = len(inorder)
        preorderSize = len(preorder)

        if preorderSize == 0:
            return retVal

        preorderIndex = preorderSize
        inorderIndex = 0
        stack = []

        # /* Example
        #  *      (3)        v  pre: 3  9 20 15  7
        #  *   (9)   (20)    v   in: 9  3 15 20  7
        #  *      (15)  (7)    post: 9 15  7 20  3
        #  */
        retVal = TreeNode(preorder[0])
        stack.append(retVal)
        for i in range(1, preorderIndex):
            preorderVal = preorder[i]
            node = stack[-1]
            if node.val != inorder[inorderIndex]:
                node.left = TreeNode(preorderVal)
                stack.append(node.left)
            else:
                while (len(stack) != 0) and (stack[-1].val == inorder[inorderIndex]):
                    node = stack[-1]
                    stack.pop()
                    inorderIndex += 1
                node.right = TreeNode(preorderVal)
                stack.append(node.right)

        return retVal
```

</details>

## [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)

- [Official](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solutions/426738/cong-zhong-xu-yu-hou-xu-bian-li-xu-lie-gou-zao-14/)

<details><summary>Description</summary>

```text
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree
and postorder is the postorder traversal of the same tree, construct and return the binary tree.

Example 1:
     3
    / \
   9   20
  / \
15   7
Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: inorder = [-1], postorder = [-1]
Output: [-1]

Constraints:
1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.
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
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    struct TreeNode* pRetVal = NULL;

    if (postorderSize == 0) {
        return pRetVal;
    }

    int postorderIndex = postorderSize - 1;
    int inorderIndex = inorderSize - 1;
    struct TreeNode* stack[postorderSize];
    int stackTop = -1;

    /* Example
     *      (3)           pre: 3  9 20 15  7
     *   (9)   (20)    v   in: 9  3 15 20  7
     *      (15)  (7)  v post: 9 15  7 20  3
     */
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = postorder[postorderIndex];
    pRetVal->left = NULL;
    pRetVal->right = NULL;
    stack[++stackTop] = pRetVal;

    int postorderVal;
    struct TreeNode* pTop;
    int i;
    for (i = postorderIndex - 1; i >= 0; --i) {
        postorderVal = postorder[i];
        pTop = stack[stackTop];
        if (pTop->val != inorder[inorderIndex]) {
            pTop->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->right == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->right->val = postorderVal;
            pTop->right->left = NULL;
            pTop->right->right = NULL;
            stack[++stackTop] = pTop->right;
        } else {
            while ((stackTop != -1) && (stack[stackTop]->val == inorder[inorderIndex])) {
                pTop = stack[stackTop--];
                --inorderIndex;
            }
            pTop->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            if (pTop->left == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pTop->left->val = postorderVal;
            pTop->left->left = NULL;
            pTop->left->right = NULL;
            stack[++stackTop] = pTop->left;
        }
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* pRetVal = nullptr;

        if (postorder.size() == 0) {
            return pRetVal;
        }

        int postorderIndex = postorder.size() - 1;
        int inorderIndex = inorder.size() - 1;
        stack s = stack<TreeNode*>();

        /* Example
         *      (3)           pre: 3  9 20 15  7
         *   (9)   (20)    v   in: 9  3 15 20  7
         *      (15)  (7)  v post: 9 15  7 20  3
         */
        pRetVal = new TreeNode(postorder[postorderIndex]);
        s.push(pRetVal);
        for (int i = postorderIndex - 1; i >= 0; --i) {
            int postorderVal = postorder[i];
            auto node = s.top();
            if (node->val != inorder[inorderIndex]) {
                node->right = new TreeNode(postorderVal);
                s.push(node->right);
            } else {
                while ((s.empty() == false) && (s.top()->val == inorder[inorderIndex])) {
                    node = s.top();
                    s.pop();
                    --inorderIndex;
                }
                node->left = new TreeNode(postorderVal);
                s.push(node->left);
            }
        }

        return pRetVal;
    }
};
```

</details>

## [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

- [Official](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/solutions/312607/jiang-you-xu-shu-zu-zhuan-huan-wei-er-cha-sou-s-33/)

<details><summary>Description</summary>

```text
Given an integer array nums where the elements are sorted in ascending order,
convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree
in which the depth of the two subtrees of every node never differs by more than one.

Example 1:
Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:
Input: nums = [1,3]
Output: [3,1]
Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.

Constraints:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in a strictly increasing order.
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
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    struct TreeNode* pRetVal = NULL;

    if (numsSize == 0) {
        return pRetVal;
    }

    int middle = numsSize / 2;
    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = *(nums + middle);
    pRetVal->left = sortedArrayToBST(nums, middle);
    pRetVal->right = sortedArrayToBST(nums + middle + 1, numsSize - middle - 1);

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
    TreeNode* buildBSTbyPreorder(vector<int>& nums, int left, int right) {
        TreeNode* pRetVal = nullptr;

        if (left > right) {
            return pRetVal;
        }

        int middle = (left + right + 1) / 2;
        pRetVal = new TreeNode(nums[middle]);
        pRetVal->left = buildBSTbyPreorder(nums, left, middle - 1);
        pRetVal->right = buildBSTbyPreorder(nums, middle + 1, right);

        return pRetVal;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* pRetVal = nullptr;

        pRetVal = buildBSTbyPreorder(nums, 0, nums.size() - 1);

        return pRetVal;
    }
};
```

</details>

## [109. Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/)

- [Official](https://leetcode.cn/problems/convert-sorted-list-to-binary-search-tree/solutions/378582/you-xu-lian-biao-zhuan-huan-er-cha-sou-suo-shu-1-3/)

<details><summary>Description</summary>

```text
Given the head of a singly linked list where elements are sorted in ascending order,
convert it to a height-balanced binary search tree.

Example 1:
Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.

Example 2:
Input: head = []
Output: []

Constraints:
The number of nodes in head is in the range [0, 2 * 10^4].
-10^5 <= Node.val <= 10^5
```

</details>

<details><summary>C</summary>

```c
struct TreeNode* buildBinarySearchTree(struct ListNode** pHead, int left, int right) {
    struct TreeNode* pRetVal = NULL;

    if (left > right) {
        return pRetVal;
    }
    int middle = (left + right + 1) / 2;

    pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    // Binary Tree Inorder Traversal: left -> root -> right
    pRetVal->left = buildBinarySearchTree(pHead, left, middle - 1);
    pRetVal->val = (*pHead)->val;
    (*pHead) = (*pHead)->next;
    pRetVal->right = buildBinarySearchTree(pHead, middle + 1, right);

    return pRetVal;
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
struct TreeNode* sortedListToBST(struct ListNode* head) {
    struct TreeNode* pRetVal = NULL;

    struct ListNode* pNext = head;
    int listLength = 0;
    while (pNext != NULL) {
        ++listLength;
        pNext = pNext->next;
    }
    pRetVal = buildBinarySearchTree(&head, 0, listLength - 1);

    return pRetVal;
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
   public:
    TreeNode* buildBSTbyInorder(ListNode** pHead, int left, int right) {
        TreeNode* pRetVal = nullptr;

        if (left > right) {
            return pRetVal;
        }

        int middle = (left + right + 1) / 2;
        pRetVal = new TreeNode();
        pRetVal->left = buildBSTbyInorder(pHead, left, middle - 1);
        pRetVal->val = (*pHead)->val;
        (*pHead) = (*pHead)->next;
        pRetVal->right = buildBSTbyInorder(pHead, middle + 1, right);

        return pRetVal;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* pRetVal = nullptr;

        int headCount = 0;
        ListNode* pNext = head;
        while (pNext != nullptr) {
            ++headCount;
            pNext = pNext->next;
        }
        pNext = head;
        pRetVal = buildBSTbyInorder(&pNext, 0, headCount - 1);

        return pRetVal;
    }
};
```

</details>

## [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)

- [Balanced Binary Tree](https://www.tutorialcup.com/interview/tree/balanced-binary-tree.htm)

<details><summary>Description</summary>

```text
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:
a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

Example 1:
     3
    / \
   9   20
  / \
15   7
Input: root = [3,9,20,null,null,15,7]
Output: true

Example 2:
      1
     / \
    2   2
   / \
  3   3
 / \
4   4
Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Example 3:
Input: root = []
Output: true

Constraints:
The number of nodes in the tree is in the range [0, 5000].
-10^4 <= Node.val <= 10^4
```

</details>

<details><summary>C</summary>

```c
int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left = height(root->left);
    if (left == -1) {
        return -1;
    }

    int right = height(root->right);
    if (right == -1) {
        return -1;
    }

    if (abs(left - right) > 1) {
        return -1;
    }

    return ((left > right) ? (left + 1) : (right + 1));
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isBalanced(struct TreeNode* root) {
    bool retVal = true;

    if (root == NULL) {
        return retVal;
    }

    if (height(root) == -1) {
        retVal = false;
    }

    return retVal;
}
```

</details>

## [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)

- [Official](https://leetcode.com/problems/minimum-depth-of-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/minimum-depth-of-binary-tree/solutions/382646/er-cha-shu-de-zui-xiao-shen-du-by-leetcode-solutio/)

<details><summary>Description</summary>

```text
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example 1:
   3
  / \
 9  20
   /  \
  15   7
Input: root = [3,9,20,null,null,15,7]
Output: 2

Example 2:
Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5

Constraints:
The number of nodes in the tree is in the range [0, 10^5].
-1000 <= Node.val <= 1000
```

</details>

<details><summary>C</summary>

```c
#define DFS (1)
#define BFS (1)
#if (DFS)
int dfs(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if ((root->left == NULL) && (root->right == NULL)) {
        retVal += 1;
        return retVal;
    }

    if (root->left == NULL) {
        retVal = 1 + dfs(root->right);
    } else if (root->right == NULL) {
        retVal = 1 + dfs(root->left);
    } else {
        retVal = 1 + fmin(dfs(root->left), dfs(root->right));
    }

    return retVal;
}
#elif (BFS)
#define MAX_QUEUE_SIZE (100000 * 2)  // The number of nodes in the tree is in the range [0, 10^5].
int bfs(struct TreeNode* root) {
    int retVal = 0;

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail] = root;
    ++bfsQueueTail;
    retVal = 1;

    int bfsQueueSize;
    struct TreeNode* pCurrent;
    int i;
    while (bfsQueueHead < bfsQueueTail) {
        bfsQueueSize = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < bfsQueueSize; ++i) {
            pCurrent = bfsQueue[bfsQueueHead];
            ++bfsQueueHead;

            if ((pCurrent->left == NULL) && (pCurrent->right == NULL)) {
                return retVal;
            }

            if (pCurrent->left != NULL) {
                bfsQueue[bfsQueueTail] = pCurrent->left;
                ++bfsQueueTail;
            }
            if (pCurrent->right != NULL) {
                bfsQueue[bfsQueueTail] = pCurrent->right;
                ++bfsQueueTail;
            }
        }
        ++retVal;
    }

    return retVal;
}
#endif
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDepth(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

#if (DFS)
    printf("Depth-First Search\n\n");
    retVal = dfs(root);
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
#define DFS (1)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
#if (DFS)
    int dfs(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            retVal += 1;
            return retVal;
        }

        if (root->left == nullptr) {
            retVal = 1 + dfs(root->right);
        } else if (root->right == nullptr) {
            retVal = 1 + dfs(root->left);
        } else {
            retVal = 1 + min(dfs(root->left), dfs(root->right));
        }

        return retVal;
    }
#elif (BFS)
    int bfs(TreeNode* root) {
        int retVal = 0;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);
        retVal = 1;
        while (bfsQueue.empty() == false) {
            int bfsQueueSize = bfsQueue.size();
            for (int i = 0; i < bfsQueueSize; ++i) {
                TreeNode* pCurrent = bfsQueue.front();
                bfsQueue.pop();

                if ((pCurrent->left == nullptr) && (pCurrent->right == nullptr)) {
                    return retVal;
                }

                if (pCurrent->left != nullptr) {
                    bfsQueue.emplace(pCurrent->left);
                }
                if (pCurrent->right != nullptr) {
                    bfsQueue.emplace(pCurrent->right);
                }
            }
            ++retVal;
        }

        return retVal;
    }
#endif
    int minDepth(TreeNode* root) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        retVal = dfs(root);
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
        self.method = 1

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if (root.left == None) and (root.right == None):
            retVal += 1
            return retVal

        if root.left == None:
            retVal = 1 + self.dfs(root.right)
        elif root.right == None:
            retVal = 1 + self.dfs(root.left)
        else:
            retVal = 1 + min(self.dfs(root.left), self.dfs(root.right))

        return retVal

    def bfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        bfsQueue = deque()
        bfsQueue.append(root)
        retVal = 1
        while bfsQueue:
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()

                if (node.left == None) and (node.right == None):
                    return retVal

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            retVal += 1

        return retVal

    def minDepth(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if self.method == 1:
            retVal = self.dfs(root)
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal
```

</details>

## [112. Path Sum](https://leetcode.com/problems/path-sum/)

<details><summary>Description</summary>

```text
Given the root of a binary tree and an integer targetSum,
return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

Example 1:
       5
     /   \
    4     8
   /     / \
  11   13   4
 /  \        \
7    2        1
Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.

Example 2:
  1
 / \
2   3
Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.

Example 3:
Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.

Constraints:
The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
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
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return false;
    }

    if ((root->left == NULL) && (root->right == NULL)) {
        if (root->val == targetSum) {
            return true;
        }
    }
    targetSum -= root->val;

    return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
}
```

</details>

## [113. Path Sum II](https://leetcode.com/problems/path-sum-ii/)

- [Official](https://leetcode.cn/problems/path-sum-ii/solutions/427759/lu-jing-zong-he-ii-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree and an integer targetSum,
return all root-to-leaf paths where the sum of the node values in the path equals targetSum.
Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.

Example 1:
        5
      /   \
     4     8
    /     / \
  11    13   4
 /  \       / \
7    2     5   1
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22

Example 2:
  1
 / \
2   3
Input: root = [1,2,3], targetSum = 5
Output: []

Example 3:
Input: root = [1,2], targetSum = 0
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
```

</details>

<details><summary>C</summary>

```c
#define DFS (1)
#define BFS (1)
#define MAX_RETURN_SIZE (5000)  // The number of nodes in the tree is in the range [0, 5000].
#if (DFS)
void dfs(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes, int** retVal, int* path,
         int* pathSize) {
    if (root == NULL) {
        return;
    }

    path[(*pathSize)] = root->val;
    (*pathSize) += 1;

    targetSum -= root->val;

    int i;
    if ((root->left == NULL) && (root->right == NULL) && (targetSum == 0)) {
        retVal[(*returnSize)] = (int*)malloc((*pathSize) * sizeof(int));
        if (retVal[(*returnSize)] == NULL) {
            perror("malloc");
            for (i = 0; i < (*returnSize); ++i) {
                free(retVal[i]);
                retVal[i] = NULL;
            }
            return;
        }
        memset(retVal[(*returnSize)], 0, ((*pathSize) * sizeof(int)));
        memcpy(retVal[(*returnSize)], path, ((*pathSize) * sizeof(int)));
        (*returnColumnSizes)[(*returnSize)] = (*pathSize);
        (*returnSize) += 1;
    }
    dfs(root->left, targetSum, returnSize, returnColumnSizes, retVal, path, pathSize);
    dfs(root->right, targetSum, returnSize, returnColumnSizes, retVal, path, pathSize);

    (*pathSize) -= 1;
}
#elif (BFS)
struct hashTable {
    struct TreeNode* key;
    struct TreeNode* value;
    UT_hash_handle hh;
};
struct hashTable* parent = NULL;
void insertHashTable(struct TreeNode* x, struct TreeNode* y) {
    struct hashTable* pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
    if (pTmp == NULL) {
        perror("mallpc");
        return;
    }
    pTmp->key = x;
    pTmp->value = y;

    HASH_ADD_PTR(parent, key, pTmp);
}
struct TreeNode* queryHashTable(struct TreeNode* x) {
    struct hashTable* pTmp;
    HASH_FIND_PTR(parent, &x, pTmp);

    return pTmp->value;
}
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
void bfs(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes, int** retVal) {
    if (root == NULL) {
        return;
    }

    insertHashTable(root, NULL);

    struct TreeNode* bfsQueue[MAX_RETURN_SIZE];
    int targetSumQueue[MAX_RETURN_SIZE];
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail] = root;
    targetSumQueue[bfsTail] = 0;
    bfsTail++;

    int i, colSize, tmp;
    struct TreeNode* node = NULL;
    int sum;
    while (bfsHead < bfsTail) {
        node = bfsQueue[bfsHead];
        sum = targetSumQueue[bfsHead] + node->val;
        bfsHead++;

        if ((node->left == NULL) && (node->right == NULL)) {
            if (sum == targetSum) {
                retVal[(*returnSize)] = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
                if (retVal[(*returnSize)] == NULL) {
                    perror("malloc");
                    for (i = 0; i < (*returnSize); ++i) {
                        free(retVal[i]);
                        retVal[i] = NULL;
                    }
                    freeAll(parent);
                    parent = NULL;
                    return;
                }

                colSize = 0;
                while (node != NULL) {
                    retVal[(*returnSize)][colSize++] = node->val;
                    node = queryHashTable(node);
                }

                for (i = 0; i < colSize / 2; i++) {
                    tmp = retVal[(*returnSize)][i];
                    retVal[(*returnSize)][i] = retVal[(*returnSize)][colSize - 1 - i];
                    retVal[(*returnSize)][colSize - 1 - i] = tmp;
                }
                (*returnColumnSizes)[(*returnSize)] = colSize;
                (*returnSize) += 1;
            }
        } else {
            if (node->left != NULL) {
                insertHashTable(node->left, node);
                bfsQueue[bfsTail] = node->left;
                targetSumQueue[bfsTail] = sum;
                bfsTail++;
            }
            if (node->right != NULL) {
                insertHashTable(node->right, node);
                bfsQueue[bfsTail] = node->right;
                targetSumQueue[bfsTail] = sum;
                bfsTail++;
            }
        }
    }

    freeAll(parent);
    parent = NULL;
}
#endif
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int targetSum, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (MAX_RETURN_SIZE * sizeof(int)));

#if (DFS)
    printf("Depth-First Search\n\n");

    int* path = NULL;
    path = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(path, 0, (MAX_RETURN_SIZE * sizeof(int)));
    int pathSize = 0;

    dfs(root, targetSum, returnSize, returnColumnSizes, pRetVal, path, &pathSize);
    free(path);
    path = NULL;
#elif (BFS)
    printf("Breadth-First Search\n\n");

    bfs(root, targetSum, returnSize, returnColumnSizes, pRetVal);
#endif

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
#define DFS (1)
#define BFS (1)
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& retVal) {
        if (root == nullptr) {
            return;
        }

        path.emplace_back(root->val);
        targetSum -= root->val;

        if ((root->left == nullptr) && (root->right == nullptr) && (targetSum == 0)) {
            retVal.emplace_back(path);
        }
        dfs(root->left, targetSum, path, retVal);
        dfs(root->right, targetSum, path, retVal);

        path.pop_back();
    }
    void bfs(TreeNode* root, int targetSum, vector<vector<int>>& retVal) {
        if (root == nullptr) {
            return;
        }

        unordered_map<TreeNode*, TreeNode*> parent;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);

        queue<int> targetSumQueue;
        targetSumQueue.emplace(0);

        while (bfsQueue.empty() == false) {
            TreeNode* node = bfsQueue.front();
            bfsQueue.pop();

            int sum = targetSumQueue.front() + node->val;
            targetSumQueue.pop();

            if ((node->left == nullptr) && (node->right == nullptr)) {
                if (sum == targetSum) {
                    vector<int> tmp;
                    while (node != nullptr) {
                        tmp.emplace_back(node->val);
                        node = parent[node];
                    }
                    reverse(tmp.begin(), tmp.end());
                    retVal.emplace_back(tmp);
                }
            } else {
                if (node->left != nullptr) {
                    parent[node->left] = node;
                    bfsQueue.emplace(node->left);
                    targetSumQueue.emplace(sum);
                }
                if (node->right != nullptr) {
                    parent[node->right] = node;
                    bfsQueue.emplace(node->right);
                    targetSumQueue.emplace(sum);
                }
            }
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> retVal;

#if (DFS)
        vector<int> path;
        dfs(root, targetSum, path, retVal);
#elif (BFS)
        bfs(root, targetSum, retVal);
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
        self.method = 1

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, root: Optional[TreeNode], targetSum: int, path: List[int], retVal: List[List[int]]) -> None:
        if root is None:
            return

        path.append(root.val)

        targetSum -= root.val
        if (root.left is None) and (root.right is None) and (targetSum == 0):
            retVal.append(path[:])
        self.dfs(root.left, targetSum, path, retVal)
        self.dfs(root.right, targetSum, path, retVal)

        path.pop()

    def bfs(self, root: Optional[TreeNode], targetSum: int, retVal: List[List[int]]) -> None:
        if root is None:
            return

        parent = defaultdict(lambda: None)
        targetSumQueue = deque([0])

        bfsQueue = deque([root])
        while bfsQueue:
            node = bfsQueue.popleft()
            sum = targetSumQueue.popleft() + node.val

            if (node.left is None) and (node.right is None):
                if sum == targetSum:
                    tmp = []
                    while node:
                        tmp.append(node.val)
                        node = parent[node]
                    retVal.append(tmp[::-1])
            else:
                if node.left:
                    parent[node.left] = node
                    bfsQueue.append(node.left)
                    targetSumQueue.append(sum)
                if node.right:
                    parent[node.right] = node
                    bfsQueue.append(node.right)
                    targetSumQueue.append(sum)

    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            path = []
            self.dfs(root, targetSum, path, retVal)
        elif self.method == 2:
            self.bfs(root, targetSum, retVal)

        return retVal
```

</details>

## [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

- [Official](https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/297005/er-cha-shu-zhong-de-zui-da-lu-jing-he-by-leetcode-)

<details><summary>Description</summary>

```text
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes
in the sequence has an edge connecting them.
A node can only appear in the sequence at most once.
Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.

Example 1:
  1
 / \
2   3
Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

Example 2:
 -10
 /  \
9    20
    /  \
  15    7
Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.

Constraints:
The number of nodes in the tree is in the range [1, 3 * 10^4].
-1000 <= Node.val <= 1000
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
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int dfs(struct TreeNode* root, int* returnMax) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int left = dfs(root->left, returnMax);
    int right = dfs(root->right, returnMax);

    retVal = MAX((left + root->val), (right + root->val));
    retVal = MAX(retVal, root->val);

    (*returnMax) = MAX((*returnMax), MAX(retVal, (left + right + root->val)));

    return retVal;
}
/* Official
 *  https://leetcode.com/problems/binary-tree-maximum-path-sum/solutions/2827786/binary-tree-maximum-path-sum/
 *  https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/297005/er-cha-shu-zhong-de-zui-da-lu-jing-he-by-leetcode-/
 */
int maxPathSum(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    retVal = INT_MIN;
#if (1)
    // https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/298031/di-gui-zui-you-jie-bu-jing-guo-gen-jie-dian-de-chu/
    dfs(root, &retVal);
#else
    // https://leetcode.cn/problems/binary-tree-maximum-path-sum/solutions/1731711/by-xun-ge-v-7r1v/
    int left;
    int right;
    int val = root->val;

    if (root->left) {
        left = maxPathSum(root->left);
        retVal = MAX(retVal, left);
        val = MAX(val, (root->val + root->left->val));
    }

    if (root->right) {
        right = maxPathSum(root->right);
        retVal = MAX(retVal, right);
        val = MAX(val, (root->val + root->right->val));
    }

    if (root->left && root->right) {
        retVal = MAX(retVal, (root->val + root->left->val + root->right->val));
    }

    root->val = val;

    retVal = MAX(retVal, root->val);
#endif

    return retVal;
}
```

</details>

## [129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/)

- [Official](https://leetcode.cn/problems/sum-root-to-leaf-numbers/solutions/464666/qiu-gen-dao-xie-zi-jie-dian-shu-zi-zhi-he-by-leetc/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.
- For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.

Return the total sum of all root-to-leaf numbers.
Test cases are generated so that the answer will fit in a 32-bit integer.

A leaf node is a node with no children.

Example 1:
  1
 / \
2   3
Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:
    4
   / \
  9   0
 / \
5   1
Input: root = [4,9,0,5,1]
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.

Constraints:
The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 9
The depth of the tree will not exceed 10.
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
#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (1)
#if (DEPTH_FIRST_SEARCH)
int dfs(struct TreeNode* pRoot, int sum) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    retVal = 10 * sum + pRoot->val;
    if ((pRoot->left == NULL) && (pRoot->right == NULL)) {
        return retVal;
    }
    retVal = dfs(pRoot->left, retVal) + dfs(pRoot->right, retVal);

    return retVal;
}
#elif (BREADTH_FIRST_SEARCH)
#define MAX_QUEUE_SIZE (1000 * 2)  // The number of nodes in the tree is in the range [1, 1000].
int bfs(struct TreeNode* pRoot) {
    int retVal = 0;

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsNodeQueue[MAX_QUEUE_SIZE];
    int bfsSumQueue[MAX_QUEUE_SIZE];
    bfsNodeQueue[bfsQueueTail] = pRoot;
    bfsSumQueue[bfsQueueTail] = pRoot->val;
    ++bfsQueueTail;

    struct TreeNode* pCurrent;
    int sum;
    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsNodeQueue[bfsQueueHead];
        sum = bfsSumQueue[bfsQueueHead];
        ++bfsQueueHead;

        if ((pCurrent->left == NULL) && (pCurrent->right == NULL)) {
            retVal += sum;
            continue;
        }

        if (pCurrent->left != NULL) {
            bfsNodeQueue[bfsQueueTail] = pCurrent->left;
            bfsSumQueue[bfsQueueTail] = sum * 10 + pCurrent->left->val;
            ++bfsQueueTail;
        }
        if (pCurrent->right != NULL) {
            bfsNodeQueue[bfsQueueTail] = pCurrent->right;
            bfsSumQueue[bfsQueueTail] = sum * 10 + pCurrent->right->val;
            ++bfsQueueTail;
        }
    }

    return retVal;
}
#endif
int sumNumbers(struct TreeNode* root) {
    int retVal = 0;

#if (DEPTH_FIRST_SEARCH)
    printf("DEPTH_FIRST_SEARCH\n");
    retVal = dfs(root, 0);
#elif (BREADTH_FIRST_SEARCH)
    printf("BREADTH_FIRST_SEARCH\n");
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
#define DEPTH_FIRST_SEARCH (1)
#define BREADTH_FIRST_SEARCH (1)
   public:
#if (DEPTH_FIRST_SEARCH)
    int dfs(TreeNode* pRoot, int sum) {
        int retVal = 0;

        if (pRoot == nullptr) {
            return retVal;
        }

        retVal = 10 * sum + pRoot->val;
        if ((pRoot->left == nullptr) && (pRoot->right == nullptr)) {
            return retVal;
        }
        retVal = dfs(pRoot->left, retVal) + dfs(pRoot->right, retVal);

        return retVal;
    }
#elif (BREADTH_FIRST_SEARCH)
    int bfs(TreeNode* pRoot) {
        int retVal = 0;

        queue<TreeNode*> bfsNodeQueue;
        bfsNodeQueue.push(pRoot);

        queue<int> bfsSumQueue;
        bfsSumQueue.push(pRoot->val);

        while (bfsNodeQueue.empty() == false) {
            TreeNode* pCurrent = bfsNodeQueue.front();
            bfsNodeQueue.pop();

            int sum = bfsSumQueue.front();
            bfsSumQueue.pop();

            if ((pCurrent->left == nullptr) && (pCurrent->right == nullptr)) {
                retVal += sum;
                continue;
            }

            if (pCurrent->left != nullptr) {
                bfsNodeQueue.push(pCurrent->left);
                bfsSumQueue.push(sum * 10 + pCurrent->left->val);
            }
            if (pCurrent->right != nullptr) {
                bfsNodeQueue.push(pCurrent->right);
                bfsSumQueue.push(sum * 10 + pCurrent->right->val);
            }
        }

        return retVal;
    }
#endif
    int sumNumbers(TreeNode* root) {
        int retVal = 0;

#if (DEPTH_FIRST_SEARCH)
        cout << "DEPTH_FIRST_SEARCH\n";
        retVal = dfs(root, 0);
#elif (BREADTH_FIRST_SEARCH)
        cout << "BREADTH_FIRST_SEARCH\n";
        retVal = bfs(root);
#endif

        return retVal;
    }
};
```

</details>

## [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)

- [Official](https://leetcode.cn/problems/binary-tree-preorder-traversal/solutions/461821/er-cha-shu-de-qian-xu-bian-li-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the preorder traversal of its nodes' values.

Example 1:
1
 \
  2
 /
3
Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up: Recursive solution is trivial, could you do it iteratively?
```

</details>

<details><summary>C</summary>

```c
void preorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    preorder(root->left, pTreeNodeCount, pTreeArray);
    preorder(root->right, pTreeNodeCount, pTreeArray);
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
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 100].
    pRetVal = (int*)malloc(100 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    preorder(root, returnSize, pRetVal);

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
    void preorder(TreeNode* root, vector<int>& retVal) {
        if (root == nullptr) {
            return;
        }
        retVal.push_back(root->val);
        preorder(root->left, retVal);
        preorder(root->right, retVal);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> retVal;

        preorder(root, retVal);

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
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        retVal.append(root.val)
        retVal.extend(self.preorderTraversal(root.left))
        retVal.extend(self.preorderTraversal(root.right))

        return retVal
```

</details>

## [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

- [Official](https://leetcode.cn/problems/binary-tree-postorder-traversal/solutions/431066/er-cha-shu-de-hou-xu-bian-li-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the preorder traversal of its nodes' values.

Example 1:
1
 \
  2
 /
3
Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

Follow up: Recursive solution is trivial, could you do it iteratively?
```

</details>

<details><summary>C</summary>

```c
void postorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    postorder(root->left, pTreeNodeCount, pTreeArray);
    postorder(root->right, pTreeNodeCount, pTreeArray);
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
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
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 100].
    pRetVal = (int*)malloc(100 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    postorder(root, returnSize, pRetVal);

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
    void postorder(TreeNode *root, vector<int> &retVal) {
        if (root == nullptr) {
            return;
        }
        postorder(root->left, retVal);
        postorder(root->right, retVal);
        retVal.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> retVal;

        postorder(root, retVal);

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
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        retVal.extend(self.postorderTraversal(root.left))
        retVal.extend(self.postorderTraversal(root.right))
        retVal.append(root.val)

        return retVal
```

</details>

## [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/description)

- [Official](https://leetcode.cn/problems/binary-tree-right-side-view/solutions/213494/er-cha-shu-de-you-shi-tu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, imagine yourself standing on the right side of it,
return the values of the nodes you can see ordered from top to bottom.

Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,null,3]
Output: [1,3]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
```

</details>

<details><summary>C</summary>

```c
int treeHeight(struct TreeNode* pRoot) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    int leftHeight = treeHeight(pRoot->left);
    int rightHeight = treeHeight(pRoot->right);
    if (leftHeight > rightHeight) {
        retVal = leftHeight + 1;
    } else {
        retVal = rightHeight + 1;
    }

    return retVal;
}
void treeLevel(struct TreeNode* pRoot, int level, int* pRetVal) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        (*pRetVal) = pRoot->val;
    } else {
        treeLevel(pRoot->left, level - 1, pRetVal);
        treeLevel(pRoot->right, level - 1, pRetVal);
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    //
    (*returnSize) = treeHeight(root);
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int value;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        treeLevel(root, level, &value);
        pRetVal[level] = value;
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> retVal;

        if (root == NULL) {
            return retVal;
        }

        queue<TreeNode*> q;
        q.push(root);
        while (q.empty() == false) {
            TreeNode* node = nullptr;

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                node = q.front();
                q.pop();
                if (node->left != NULL) {
                    q.push(node->left);
                }
                if (node->right != NULL) {
                    q.push(node->right);
                }
            }

            if (node != nullptr) {
                retVal.emplace_back(node->val);
            }
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
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal

        queue = deque([])
        queue.append(root)

        while queue:
            for _ in range(len(queue)):
                node = queue.popleft()
                if node.left != None:
                    queue.append(node.left)
                if node.right != None:
                    queue.append(node.right)
            retVal.append(node.val)

        return retVal
```

</details>

## [222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)

<details><summary>Description</summary>

```text
Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree,
and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Design an algorithm that runs in less than O(n) time complexity.

Example 1:
     1
   /   \
  2     3
 / \   /
4   5 6
Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1

Constraints:
The number of nodes in the tree is in the range [0, 5 * 10^4].
0 <= Node.val <= 5 * 10^4
The tree is guaranteed to be complete.
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
int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);

    return (1 + leftCount + rightCount);
}
```

</details>

## [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, invert the tree, and return its root.

Example 1:
     4             4
   /   \         /   \
  2     7       7     2
 / \   / \     / \   / \
1   3 6   9   9   6 3   1
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Example 2:
  2       2
 / \     / \
1   3   3   1
Input: root = [2,1,3]
Output: [2,3,1]

Example 3:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
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
struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        return pRetVal;
    }
    struct TreeNode* pTmp = pRetVal->left;
    pRetVal->left = pRetVal->right;
    pRetVal->right = pTmp;
    pRetVal->left = invertTree(pRetVal->left);
    pRetVal->right = invertTree(pRetVal->right);

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
    TreeNode *invertTree(TreeNode *root) {
        TreeNode *pRetVal = root;

        if (pRetVal == NULL) {
            return pRetVal;
        }
        TreeNode *pTemp = pRetVal->left;
        pRetVal->left = pRetVal->right;
        pRetVal->right = pTemp;
        invertTree(pRetVal->left);
        invertTree(pRetVal->right);

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
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if retVal is None:
            return retVal
        temp = retVal.left
        retVal.left = retVal.right
        retVal.right = temp
        self.invertTree(retVal.left)
        self.invertTree(retVal.right)

        return retVal
```

</details>

## [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)

<details><summary>Description</summary>

```text
Given the root of a binary search tree, and an integer k,
return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

Example 1:
  3
 / \
1   4
 \
  2
Input: root = [3,1,4,null,2], k = 1
Output: 1

Example 2:
      5
     / \
    3   6
   / \
  2   4
 /
1
Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3

Constraints:
The number of nodes in the tree is n.
1 <= k <= n <= 10^4
0 <= Node.val <= 10^4
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
#define MAX_NODE    (10000)
void inorder(struct TreeNode* root, int* pTreeNodeCount, int* pTreeArray)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, pTreeNodeCount, pTreeArray);
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
    inorder(root->right, pTreeNodeCount, pTreeArray);
}

int kthSmallest(struct TreeNode* root, int k){
    int retVal = 0;

    int *pTreeArray = (int *)malloc(MAX_NODE * sizeof(int));
    if (pTreeArray == NULL)
    {
        perror("malloc");
        return retVal;
    }
    int treeNodeCount = 0;
    inorder(root, &treeNodeCount, pTreeArray);
    if (k <= treeNodeCount)
    {
        retVal = *(pTreeArray + k - 1);
    }
    free(pTreeArray);

    return retVal;
}
```

</details>

## [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)

<details><summary>Description</summary>

```text
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: "The lowest common ancestor is defined between two nodes p and q
as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself)."

Example 1:
      6
   /     \
  2       8
 / \     / \
0   4   7   9
   / \
  3   5
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:
      6
   /     \
  2       8
 / \     / \
0   4   7   9
   / \
  3   5
Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [2,1], p = 2, q = 1
Output: 2

Constraints:
The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q will exist in the BST.
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
#define RECURSION   1
#define ITERATIVE   1

/* Lowest Common Ancestor: https://en.wikipedia.org/wiki/Lowest_common_ancestor
 *  if root are bigger than p and q, then the Lowest Common Ancestor in root->left
 *  if root are smaller than p and q, then the Lowest Common Ancestor in root->right
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL) {
        return root;
    }

#if (RECURSION)
    if ((root->val > p->val) && (root->val > q->val)) {
        return lowestCommonAncestor(root->left, p, q);
    }
    else if ((root->val < p->val) && (root->val < q->val)) {
        return lowestCommonAncestor(root->right, p, q);
    }
#elif (ITERATIVE)
    while (root != NULL) {
        if ((root->val > p->val) && (root->val > q->val)) {
            root = root->left;
        }
        else if ((root->val < p->val) && (root->val < q->val)) {
            root = root->right;
        }
        else {
            break;
        }
    }
#endif

    return root;
}
```

</details>

## [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

- [Official](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/solutions/238552/er-cha-shu-de-zui-jin-gong-gong-zu-xian-by-leetc-2/)

<details><summary>Description</summary>

```text
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia:
"The lowest common ancestor is defined between two nodes p and q as the lowest node in T
that has both p and q as descendants (where we allow a node to be a descendant of itself)."

Example 1:
      3
   /     \
  5       1
 / \     / \
6   2   0   8
   / \
  7   4
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
      3
   /     \
  5       1
 / \     / \
6   2   0   8
   / \
  7   4
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:
Input: root = [1,2], p = 1, q = 2
Output: 1

Constraints:
The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q will exist in the tree.
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
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* pRetVal = root;

    if ((root == NULL) || (root == p) || (root == q)) {
        return pRetVal;
    }

    struct TreeNode* pLeft = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* pRight = lowestCommonAncestor(root->right, p, q);
    if ((pLeft == NULL) && (pRight == NULL)) {
        pRetVal = NULL;
    } else if (pLeft == NULL) {
        pRetVal = pRight;
    } else if (pRight == NULL) {
        pRetVal = pLeft;
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* pRetVal = root;

        if ((root == nullptr) || (root == p) || (root == q)) {
            return pRetVal;
        }

        TreeNode* pLeft = lowestCommonAncestor(root->left, p, q);
        TreeNode* pRight = lowestCommonAncestor(root->right, p, q);
        if ((pLeft == nullptr) && (pRight == nullptr)) {
            pRetVal = nullptr;
        } else if (pLeft == nullptr) {
            pRetVal = pRight;
        } else if (pRight == nullptr) {
            pRetVal = pLeft;
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
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        retVal = root

        if (root is None) or (root == p) or (root == q):
            return retVal

        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if (left is None) and (right is None):
            retVal = None
        elif (left is None):
            retVal = right
        elif (right is None):
            retVal = left

        return retVal
```

</details>

## [285. Inorder Successor in BST](https://leetcode.com/problems/inorder-successor-in-bst/)  unlock

- Subscribe to unlock
  - Arista Networks
  - Microsoft
  - Google
- [285. Inorder Successor in BST](https://leetcode.ca/2016-09-10-285-Inorder-Successor-in-BST/)

<details><summary>Description</summary>

```text
Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST.
If the given node has no in-order successor in the tree, return null.

The successor of a node p is the node with the smallest key greater than p.val.

Example 1:
  2
 / \
1   3
Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.

Example 2:
      5
     / \
    3   6
   / \
  2   4
 /
1
Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5
All Nodes will have unique values.
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
struct TreeNode* inorderSuccessor(struct TreeNode* root, struct TreeNode* p) {
    /* Algorithm
     *  If the value of the root node is less than or equal to the value of the p node,
     *  it means that the successor node of p must be in the right subtree,
     *  so this function is recursively called on the right child node.
     *
     *  If the value of the root node is greater than the value of p,
     *  then it is possible that the root node is the successor of p,
     *  or a node in the left subtree is a successor of p,
     *  * So first call this function recursively on the left child node,
     *  * If it returns empty, indicating that the root node is a successor node, just return,
     *  * If it is not empty, return that node
     */

    struct TreeNode* pRetVal = NULL;

    if (root == NULL) {
        return pRetVal;
    }

    if (root->val <= p->val) {
        pRetVal = inorderSuccessor(root->right, p);
    } else {
        pRetVal = inorderSuccessor(root->left, p);
        if (pRetVal == NULL) {
            pRetVal = root;
        }
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* pRetVal = NULL;

        if ((root == NULL) || (p == NULL)) {
            return pRetVal;
        }

        while (root != NULL) {
            if (root->val <= p->val) {
                root = root->right;
            } else {
                pRetVal = root;
                root = root->left;
            }
        }

        return pRetVal;
    }
};
```

</details>

## [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

- [Official](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/solutions/290065/er-cha-shu-de-xu-lie-hua-yu-fan-xu-lie-hua-by-le-2/)

<details><summary>Description</summary>

```text
Serialization is the process of converting a data structure or object into a sequence of bits
so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary tree can be serialized to a string
and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree.
You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000
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
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {

}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {

}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
   public:
    // Encodes a tree to a single string.
    void rserialize(TreeNode *root, string &retVal) {
        if (root == nullptr) {
            retVal += "None,";
            return;
        }
        retVal += to_string(root->val) + ",";
        rserialize(root->left, retVal);
        rserialize(root->right, retVal);
    }
    string serialize(TreeNode *root) {
        string retVal;

        rserialize(root, retVal);

        return retVal;
    }

    // Decodes your encoded data to tree.
    TreeNode *rdeserialize(list<string> &dataArray) {
        TreeNode *pRoot = nullptr;

        if (dataArray.front() == "None") {
            dataArray.erase(dataArray.begin());
            return pRoot;
        }
        pRoot = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        pRoot->left = rdeserialize(dataArray);
        pRoot->right = rdeserialize(dataArray);

        return pRoot;
    }
    TreeNode *deserialize(string data) {
        TreeNode *pRetVal = nullptr;

        list<string> dataArray;
        string str;
        for (auto &ch : data) {
            if (ch == ',') {
                dataArray.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        if (str.empty() == false) {
            dataArray.push_back(str);
            str.clear();
        }
        pRetVal = rdeserialize(dataArray);

        return pRetVal;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

</details>

## [404. Sum of Left Leaves](https://leetcode.com/problems/sum-of-left-leaves/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the sum of all left leaves.

A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.

Example 1:
     3
    / \
   9   20
      /  \
    15    7
Input: root = [3,9,20,null,null,15,7]
Output: 24
Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.

Example 2:
Input: root = [1]
Output: 0

Constraints:
The number of nodes in the tree is in the range [1, 1000].
-1000 <= Node.val <= 1000
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
int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left != NULL) {
        if ((root->left->left == NULL) && (root->left->right == NULL)) {
            return root->left->val + sumOfLeftLeaves(root->right);
        }
    }

    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}
```

</details>

## [427. Construct Quad Tree](https://leetcode.com/problems/construct-quad-tree/)

- [Official](https://leetcode.cn/problems/construct-quad-tree/solutions/1449809/jian-li-si-cha-shu-by-leetcode-solution-gcru/)

<details><summary>Description</summary>

```text
Given a n * n matrix grid of 0's and 1's only. We want to represent the grid with a Quad-Tree.

Return the root of the Quad-Tree representing the grid.

Notice that you can assign the value of a node to True or False when isLeaf is False, and both are accepted in the answer.

A Quad-Tree is a tree data structure in which each internal node has exactly four children.
Besides, each node has two attributes:
- val: True if the node represents a grid of 1's or False if the node represents a grid of 0's.
- isLeaf: True if the node is leaf node on the tree or False if the node has the four children.
```

```c++
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
```

```text
We can construct a Quad-Tree from a two-dimensional area using the following steps:

If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True
and set val to the value of the grid and set the four children to Null and stop.
If the current grid has different values,
set isLeaf to False and set val to any value and divide the current grid into four sub-grids as shown in the photo.
Recurse for each of the children with the proper sub-grid.
+--------------------------+
|    topLeft |    topRight |
+------------+-------------+
| bottomLeft | bottomRight |
+------------+-------------+
If you want to know more about the Quad-Tree, you can refer to the wiki.

Quad-Tree format:
The output represents the serialized format of a Quad-Tree using level order traversal,
where null signifies a path terminator where no node exists below.

It is very similar to the serialization of the binary tree.
The only difference is that the node is represented as a list [isLeaf, val].

If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val]
and if the value of isLeaf or val is False we represent it as 0.
```

```text
Example 1:
+-------+
| 0 | 1 |
+---+---+
| 1 | 0 |
+---+---+
Input: grid = [[0,1],[1,0]]
Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
Explanation: The explanation of this example is shown below:
Notice that 0 represnts False and 1 represents True in the photo representing the Quad-Tree.
                                         +----------+
+-------+          +---------------------| isLeaf:0 |---------------------+
| 0 | 1 |          |                 +---|    val:1 |----+                |
+---+---+          |                 |   +----------+    |                |
| 1 | 0 |          |                 |                   |                |
+---+---+   +------+------+   +------+------+   +--------+----+   +-------+-----+
            |   topLeft   |   |   topRight  |   |  bottomLeft |   | bottomRight |
            +-------------+   +-------------+   +-------------+   +-------------+
            |   isLeaf:1  |   |   isLeaf:1  |   |   isLeaf:1  |   |   isLeaf:1  |
            |      val:0  |   |      val:1  |   |      val:1  |   |      val:0  |
            +-------------+   +-------------+   +-------------+   +-------------+
```

```text
Example 2:
+-------------------------------+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
| 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
+---+---+---+---+---+---+---+---+
Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],
                [1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
The topLeft, bottomLeft and bottomRight each has the same value.
The topRight have different values so we divide it into 4 sub-grids where each has the same value.
Explanation is shown in the photo below:
                                                            +----------+
+------------+------+------+          +---------------------| isLeaf:0 |---------------------+
| 1  1  1  1 | 0  0 | 0  0 |          |                 +---|    val:1 |----+                |
| 1  1  1  1 | 0  0 | 0  0 |          |                 |   +----------+    |                |
|            +------+------|          |                 |                   |                |
| 1  1  1  1 | 1  1 | 1  1 |   +------+------+   +------+------+   +--------+----+   +-------+-----+
| 1  1  1  1 | 1  1 | 1  1 |   |   topLeft   |   |   topRight  |   |  bottomLeft |   | bottomRight |
+------------+------+------+   +-------------+   +-------------+   +-------------+   +-------------+
| 1  1  1  1 | 0  0   0  0 |   |   isLeaf:1  |   |   isLeaf:0  |   |   isLeaf:1  |   |   isLeaf:1  |
| 1  1  1  1 | 0  0   0  0 |   |      val:1  |   |      val:1  |   |      val:1  |   |      val:0  |
| 1  1  1  1 | 0  0   0  0 |   +-------------+   +-------------+   +-------------+   +-------------+
| 1  1  1  1 | 0  0   0  0 |                     |   |     |   |
+------------+-------------+   +-----------------+   |     |   +----------------+
                               |               +-----+     +-----+              |
                               |               |                 |              |
                        +------+------+ +------+------+ +--------+----+ +-------+-----+
                        |   topLeft   | |   topRight  | |  bottomLeft | | bottomRight |
                        +-------------+ +-------------+ +-------------+ +-------------+
                        |   isLeaf:1  | |   isLeaf:1  | |   isLeaf:1  | |   isLeaf:1  |
                        |      val:0  | |      val:0  | |      val:1  | |      val:1  |
                        +-------------+ +-------------+ +-------------+ +-------------+
```

```text
Constraints:
n == grid.length == grid[i].length
n == 2x where 0 <= x <= 6
```

</details>

<details><summary>C++</summary>

```c++
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
   public:
    void printNode(Node* pRoot, string fmt) {
        if (pRoot == nullptr) {
            return;
        }
        cout << fmt << "[" << pRoot->isLeaf << "," << pRoot->val << "]";
        printNode(pRoot->topLeft, ",");
        printNode(pRoot->topRight, ",");
        printNode(pRoot->bottomLeft, ",");
        printNode(pRoot->bottomRight, ",");
    }
    void freeNode(Node* pRoot) {
        if (pRoot == nullptr) {
            return;
        }
        freeNode(pRoot->topLeft);
        freeNode(pRoot->topRight);
        freeNode(pRoot->bottomLeft);
        freeNode(pRoot->bottomRight);
        delete pRoot;
        pRoot = nullptr;
    }

    // https://leetcode.cn/problems/construct-quad-tree/solutions/1457070/c-di-gui-qie-fen-by-lchaok-vus6/
    bool checkLeaf(int top, int left, int bottom, int right, vector<vector<int>>& grid) {
        int retVal = false;

        int same = grid[top][left];
        for (int i = top; i <= bottom; ++i) {
            for (int j = left; j <= right; ++j) {
                if (grid[i][j] != same) {
                    return retVal;
                }
            }
        }
        retVal = true;

        return retVal;
    }
    Node* recursion(int top, int left, int bottom, int right, vector<vector<int>>& grid) {
        Node* pRetVal = new Node();

        if (checkLeaf(top, left, bottom, right, grid)) {
            pRetVal->val = grid[top][left];
            pRetVal->isLeaf = true;
            return pRetVal;
        }
        pRetVal->isLeaf = false;
        pRetVal->val = 1;
        pRetVal->topLeft = recursion(top, left, top + (bottom - top) / 2, left + (right - left) / 2, grid);
        pRetVal->topRight = recursion(top, right - (right - left) / 2, top + (bottom - top) / 2, right, grid);
        pRetVal->bottomLeft = recursion(bottom - (bottom - top) / 2, left, bottom, left + (right - left) / 2, grid);
        pRetVal->bottomRight = recursion(bottom - (bottom - top) / 2, right - (right - left) / 2, bottom, right, grid);

        return pRetVal;
    }
    Node* construct(vector<vector<int>>& grid) {
        Node* pRetVal = NULL;

        pRetVal = recursion(0, 0, grid.size() - 1, grid.size() - 1, grid);

        return pRetVal;
    }
};
```

</details>

## [429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)

- [Official](https://leetcode.cn/problems/n-ary-tree-level-order-traversal/solutions/1400623/n-cha-shu-de-ceng-xu-bian-li-by-leetcode-lxdr/)

<details><summary>Description</summary>

```text
Given an n-ary tree, return the level order traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal,
each group of children is separated by the null value (See examples).

Example 1:
     1
   / | \
  3  2  4
 / \
5   6
Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]

Example 2:
        1
 /    /   \    \
2    3     4    5
    / \    |   / \
   6   7   8  9   10
       |   |  |
      11  12 13
       |
      14
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

Constraints:
The height of the n-ary tree is less than or equal to 1000
The total number of nodes is between [0, 104^]
```

</details>

<details><summary>C</summary>

```c
int treeHeight(struct Node* pRoot) {
    int retVal = 0;

    if (pRoot == NULL) {
        return retVal;
    }

    int height = 0;
    int i;
    for (i = 0; i < pRoot->numChildren; ++i) {
        height = treeHeight(pRoot->children[i]);
        retVal = (retVal > height) ? retVal : height;
    }

    return retVal + 1;
}
void treeLevel(struct Node* pRoot, int level, int* pReturnArray, int* pReturnArrayIndex) {
    if (pRoot == NULL) {
        return;
    }

    if (level == 0) {
        if (pReturnArray != NULL) {
            pReturnArray[(*pReturnArrayIndex)] = pRoot->val;
        }
        (*pReturnArrayIndex)++;
        return;
    }

    int i;
    for (i = 0; i < pRoot->numChildren; ++i) {
        treeLevel(pRoot->children[i], level - 1, pReturnArray, pReturnArrayIndex);
    }
}
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = treeHeight(root);
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    if (root == NULL) {
        (*returnSize) = 0;
        return pRetVal;
    }

    //
    int i;
    int index;
    int level;
    for (level = 0; level < (*returnSize); ++level) {
        pRetVal[level] = NULL;
        index = 0;
        treeLevel(root, level, pRetVal[level], &index);

        (*returnColumnSizes)[level] = index;
        pRetVal[level] = (int*)malloc(((*returnColumnSizes)[level]) * sizeof(int));
        if (pRetVal[level] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < level - 1; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            (*returnSize) = 0;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[level], 0, ((*returnColumnSizes)[level]) * sizeof(int));

        index = 0;
        treeLevel(root, level, pRetVal[level], &index);
    }

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
   public:
    vector<vector<int>> levelOrder(Node *root) {
        vector<vector<int>> retVal;

        if (root == NULL) {
            return retVal;
        }

        queue<Node *> q;
        q.push(root);
        while (q.empty() == false) {
            retVal.push_back(vector<int>());

            int currentLevelSize = q.size();
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                retVal.back().push_back(node->val);
                for (auto iter : node->children) {
                    q.push(iter);
                }
            }
        }

        return retVal;
    }
};
```

</details>

## [437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)

- [Official](https://leetcode.cn/problems/path-sum-iii/solutions/1021296/lu-jing-zong-he-iii-by-leetcode-solution-z9td/)

<details><summary>Description</summary>

```text
Given the root of a binary tree and an integer targetSum,
return the number of paths where the sum of the values along the path equals targetSum.

The path does not need to start or end at the root or a leaf,
but it must go downwards (i.e., traveling only from parent nodes to child nodes).

Example 1:
      10
     /  \
    5    -3
   / \     \
  3   2     11
 / \   \
3   -2  1
Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.

Example 2:
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: 3

Constraints:
The number of nodes in the tree is in the range [0, 1000].
-10^9 <= Node.val <= 10^9
-1000 <= targetSum <= 1000
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
int dfs(struct TreeNode* root, long targetSum) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    if (root->val == targetSum) {
        retVal += 1;
    }
    retVal += dfs(root->left, targetSum - root->val);
    retVal += dfs(root->right, targetSum - root->val);

    return retVal;
}
int pathSum(struct TreeNode* root, int targetSum) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    retVal = dfs(root, targetSum);
    retVal += pathSum(root->left, targetSum);
    retVal += pathSum(root->right, targetSum);

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
    int dfs(TreeNode* root, long targetSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        if (root->val == targetSum) {
            retVal += 1;
        }
        retVal += dfs(root->left, targetSum - root->val);
        retVal += dfs(root->right, targetSum - root->val);

        return retVal;
    }
    int pathSum(TreeNode* root, int targetSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        retVal = dfs(root, targetSum);
        retVal += pathSum(root->left, targetSum);
        retVal += pathSum(root->right, targetSum);

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
    def dfs(self, root: Optional[TreeNode], targetSum: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        if root.val == targetSum:
            retVal += 1
        retVal += self.dfs(root.left, targetSum - root.val)
        retVal += self.dfs(root.right, targetSum - root.val)

        return retVal

    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        retVal = self.dfs(root, targetSum)
        retVal += self.pathSum(root.left, targetSum)
        retVal += self.pathSum(root.right, targetSum)

        return retVal
```

</details>

## [449. Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/)

- [Official](https://leetcode.cn/problems/serialize-and-deserialize-bst/solutions/1479903/xu-lie-hua-he-fan-xu-lie-hua-er-cha-sou-5m9r4/)

<details><summary>Description</summary>

```text
Serialization is converting a data structure or object into a sequence of bits
so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You need to ensure that a binary search tree can be serialized to a string,
and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Example 1:
Input: root = [2,1,3]
Output: [2,1,3]

Example 2:
Input: root = []
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
0 <= Node.val <= 104
The input tree is guaranteed to be a binary search tree.
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
/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {

}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {

}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
   public:
    // Encodes a tree to a single string.
    void rserialize(TreeNode *root, string &retVal) {
        if (root == nullptr) {
            retVal += "None,";
            return;
        }
        retVal += to_string(root->val) + ",";
        rserialize(root->left, retVal);
        rserialize(root->right, retVal);
    }
    string serialize(TreeNode *root) {
        string retVal;

        rserialize(root, retVal);

        return retVal;
    }

    // Decodes your encoded data to tree.
    TreeNode *rdeserialize(list<string> &dataArray) {
        TreeNode *pRoot = nullptr;

        if (dataArray.front() == "None") {
            dataArray.erase(dataArray.begin());
            return pRoot;
        }
        pRoot = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        pRoot->left = rdeserialize(dataArray);
        pRoot->right = rdeserialize(dataArray);

        return pRoot;
    }
    TreeNode *deserialize(string data) {
        TreeNode *pRetVal = nullptr;

        list<string> dataArray;
        string str;
        for (auto &ch : data) {
            if (ch == ',') {
                dataArray.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        if (str.empty() == false) {
            dataArray.push_back(str);
            str.clear();
        }
        pRetVal = rdeserialize(dataArray);

        return pRetVal;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
```

</details>

## [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/description)

- [Official](https://leetcode.cn/problems/delete-node-in-a-bst/solutions/1529700/shan-chu-er-cha-sou-suo-shu-zhong-de-jie-n6vo/)

<details><summary>Description</summary>

```text
Given a root node reference of a BST and a key, delete the node with the given key in the BST.
Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:
1. Search for a node to remove.
2. If the node is found, delete the node.


Example 1:
     5             5            5
   /   \          / \          / \
  3     6   =>   4   6   or   2   6
 / \     \      /     \        \   \
2   4     7    2       7        4   7
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:
Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.

Example 3:
Input: root = [], key = 0
Output: []

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
Each node has a unique value.
root is a valid binary search tree.
-10^5 <= key <= 10^5

Follow up: Could you solve it with time complexity O(height of tree)?
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
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode* pRetVal = root;

    struct TreeNode* current = root;
    struct TreeNode* currentParent = NULL;
    while ((current != NULL) && (current->val != key)) {
        currentParent = current;
        if (current->val > key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return pRetVal;
    }

    struct TreeNode* successor = NULL;
    struct TreeNode* successorParent = NULL;
    if ((current->left == NULL) && (current->right == NULL)) {
        current = NULL;
    } else if (current->right == NULL) {
        current = current->left;
    } else if (current->left == NULL) {
        current = current->right;
    } else {
        successor = current->right;
        successorParent = current;
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        if (successorParent->val == current->val) {
            successorParent->right = successor->right;
        } else {
            successorParent->left = successor->right;
        }
        successor->right = current->right;
        successor->left = current->left;
        current = successor;
    }

    if (currentParent == NULL) {
        pRetVal = current;
        return pRetVal;
    }

    struct TreeNode* pFree = NULL;
    if ((currentParent->left != NULL) && (currentParent->left->val == key)) {
        pFree = currentParent->left;
        currentParent->left = current;
    } else {
        pFree = currentParent->right;
        currentParent->right = current;
    }
    free(pFree);
    pFree = NULL;

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
    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* pRetVal = root;

        TreeNode* current = root;
        TreeNode* currentParent = nullptr;
        while ((current != nullptr) && (current->val != key)) {
            currentParent = current;
            if (current->val > key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return pRetVal;
        }

        if ((current->left == nullptr) && (current->right == nullptr)) {
            current = nullptr;
        } else if (current->right == nullptr) {
            current = current->left;
        } else if (current->left == nullptr) {
            current = current->right;
        } else {
            TreeNode* successor = current->right;
            TreeNode* successorParent = current;
            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }

            if (successorParent->val == current->val) {
                successorParent->right = successor->right;
            } else {
                successorParent->left = successor->right;
            }
            successor->right = current->right;
            successor->left = current->left;
            current = successor;
        }

        if (currentParent == nullptr) {
            pRetVal = current;
            return pRetVal;
        }

        TreeNode* pFree = nullptr;
        if ((currentParent->left != nullptr) && (currentParent->left->val == key)) {
            pFree = currentParent->left;
            currentParent->left = current;
        } else {
            pFree = currentParent->right;
            currentParent->right = current;
        }
        delete pFree;
        pFree = nullptr;

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
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        retVal = root

        current = root
        currentParent = None
        while current and current.val != key:
            currentParent = current
            if current.val > key:
                current = current.left
            else:
                current = current.right

        if current is None:
            return retVal
        if current.left is None and current.right is None:
            current = None
        elif current.right is None:
            current = current.left
        elif current.left is None:
            current = current.right
        else:
            successor = current.right
            successorParent = current
            while successor.left:
                successorParent = successor
                successor = successor.left

            if successorParent.val == current.val:
                successorParent.right = successor.right
            else:
                successorParent.left = successor.right
            successor.right = current.right
            successor.left = current.left
            current = successor

        if currentParent is None:
            retVal = current
            return retVal

        if currentParent.left and currentParent.left.val == key:
            currentParent.left = current
        else:
            currentParent.right = current

        return retVal
```

</details>

## [501. Find Mode in Binary Search Tree](https://leetcode.com/problems/find-mode-in-binary-search-tree/)

- [Official](https://leetcode.com/problems/find-mode-in-binary-search-tree/editorial/)
- [Official](https://leetcode.cn/problems/find-mode-in-binary-search-tree/solutions/425430/er-cha-sou-suo-shu-zhong-de-zhong-shu-by-leetcode-/)

<details><summary>Description</summary>

```text
Given the root of a binary search tree (BST) with duplicates, return all the mode(s)
(i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

Assume a BST is defined as follows:
- The left subtree of a node contains only nodes with keys less than or equal to the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

Example 1:
1
 \
  2
 /
2
Input: root = [1,null,2,2]
Output: [2]

Example 2:
Input: root = [0]
Output: [0]

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^5 <= Node.val <= 10^5

Follow up: Could you do that without using any extra space?
(Assume that the implicit stack space incurred due to recursion does not count).
```

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
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
void inorder(struct TreeNode* root, struct hashTable** pCounter) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, pCounter);

    int key = root->val;
    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(*pCounter, &key, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            return;
        }
        pTemp->key = key;
        pTemp->value = 1;
        HASH_ADD_INT(*pCounter, key, pTemp);
    } else {
        pTemp->value += 1;
    }

    inorder(root->right, pCounter);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMode(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    struct hashTable* pCounter = NULL;
    inorder(root, &pCounter);

    int maxValue = 0;
    struct hashTable* pTmp = NULL;
    for (pTmp = pCounter; pTmp != NULL; pTmp = pTmp->hh.next) {
        maxValue = fmax(maxValue, pTmp->value);
    }

#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree is in the range [1, 104].
    pRetVal = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_TREE_NODE * sizeof(int)));
    for (pTmp = pCounter; pTmp != NULL; pTmp = pTmp->hh.next) {
        if (pTmp->value == maxValue) {
            pRetVal[(*returnSize)++] = pTmp->key;
        }
    }

    freeAll(pCounter);

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
    void inorder(TreeNode* root, unordered_map<int, int>& counter) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, counter);
        counter[root->val]++;
        inorder(root->right, counter);
    }
    vector<int> findMode(TreeNode* root) {
        vector<int> retVal;

        unordered_map<int, int> counter;
        inorder(root, counter);

        int maxValue = 0;
        for (auto& [key, value] : counter) {
            maxValue = max(maxValue, value);
        }

        for (auto& [key, value] : counter) {
            if (value == maxValue) {
                retVal.emplace_back(key);
            }
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
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        retVal.extend(self.inorderTraversal(root.left))
        retVal.append(root.val)
        retVal.extend(self.inorderTraversal(root.right))

        return retVal

    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root == None:
            return retVal
        record = Counter(self.inorderTraversal(root)).most_common()

        maxValue = record[0][1]
        retVal.append(record[0][0])
        record = record[1:]
        for key, value in record:
            if maxValue == value:
                retVal.append(key)
            else:
                break

        return retVal
```

</details>

## [513. Find Bottom Left Tree Value](https://leetcode.com/problems/find-bottom-left-tree-value/)

- [Official](https://leetcode.com/problems/find-bottom-left-tree-value/editorial/)
- [Official](https://leetcode.cn/problems/find-bottom-left-tree-value/solutions/1614779/zhao-shu-zuo-xia-jiao-de-zhi-by-leetcode-weeh/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the leftmost value in the last row of the tree.

Example 1:
  2
 / \
1   3
Input: root = [2,1,3]
Output: 1

Example 2:
    1
   / \
  2   3
 /   / \
4   5   6
   /
  7
Input: root = [1,2,3,4,null,5,6,null,null,7]
Output: 7

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-2^31 <= Node.val <= 2^31 - 1
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
int findBottomLeftValue(struct TreeNode* root) {
    int retVal = 0;

#define MAX_QUEUE_SIZE (int)(1e4)  // The number of nodes in the tree is in the range [1, 10^4].
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;

    struct TreeNode* pCurrent = root;
    bfsQueue[bfsQueueTail++] = pCurrent;

    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsQueue[bfsQueueHead++];

        if (pCurrent->right != NULL) {
            bfsQueue[bfsQueueTail++] = pCurrent->right;
        }

        if (pCurrent->left != NULL) {
            bfsQueue[bfsQueueTail++] = pCurrent->left;
        }
    }
    retVal = pCurrent->val;

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
    int findBottomLeftValue(TreeNode* root) {
        int retVal = 0;

        queue<TreeNode*> bfsQueue;
        TreeNode* current = root;
        bfsQueue.push(current);
        while (bfsQueue.empty() == false) {
            current = bfsQueue.front();
            bfsQueue.pop();
            if (current->right != nullptr) {
                bfsQueue.push(current->right);
            }
            if (current->left != nullptr) {
                bfsQueue.push(current->left);
            }
        }
        retVal = current->val;

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
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        bfsQueue = deque()
        current = root
        bfsQueue.append(current)
        while bfsQueue:
            current = bfsQueue.popleft()
            if current.right:
                bfsQueue.append(current.right)
            if current.left:
                bfsQueue.append(current.left)
        retVal = current.val

        return retVal
```

</details>

## [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)

- [Official](https://leetcode.com/problems/find-largest-value-in-each-tree-row/editorial/)
- [Official](https://leetcode.cn/problems/find-largest-value-in-each-tree-row/solutions/1619294/zai-mei-ge-shu-xing-zhong-zhao-zui-da-zh-6xbs/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: [1,3,9]

Example 2:
Input: root = [1,2,3]
Output: [1,3]

Constraints:
The number of nodes in the tree will be in the range [0, 10^4].
-2^31 <= Node.val <= 2^31 - 1
```

</details>

<details><summary>C</summary>

```c
#define DFS (0)
#define BFS (1)
#define MAX_TREE_NODE (int)(1e4)  // The number of nodes in the tree will be in the range [0, 10^4].
void dfs(struct TreeNode* root, int level, int* answer, int* answerSize) {
    if (root == NULL) {
        return;
    }

    if (level == (*answerSize)) {
        answer[(*answerSize)++] = root->val;
    } else {
        answer[level] = fmax(answer[level], root->val);
    }

    dfs(root->left, level + 1, answer, answerSize);
    dfs(root->right, level + 1, answer, answerSize);
}
void bfs(struct TreeNode* root, int* answer, int* answerSize) {
    struct TreeNode* bfsQueue[MAX_TREE_NODE];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = root;

    int maxValue;
    int bfsQueueCount;
    int i;
    struct TreeNode* node = NULL;
    while (bfsQueueHead > bfsQueueTail) {
        maxValue = INT_MIN;  // -2^31 <= Node.val <= 2^31 - 1

        bfsQueueCount = bfsQueueHead - bfsQueueTail;
        for (i = 0; i < bfsQueueCount; ++i) {
            node = bfsQueue[bfsQueueTail];
            ++bfsQueueTail;

            maxValue = fmax(maxValue, node->val);

            if (node->left != NULL) {
                bfsQueue[bfsQueueHead++] = node->left;
            }
            if (node->right != NULL) {
                bfsQueue[bfsQueueHead++] = node->right;
            }
        }

        answer[(*answerSize)++] = maxValue;
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestValues(struct TreeNode* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(MAX_TREE_NODE * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (MAX_TREE_NODE * sizeof(int)));

#if (DFS)
    printf("Depth-First Search\n\n");
    dfs(root, 0, pRetVal, returnSize);
#elif (BFS)
    printf("Breadth-First Search\n\n");
    bfs(root, pRetVal, returnSize);
#endif

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
#define DFS (0)
#define BFS (1)
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
    void dfs(TreeNode* root, int level, vector<int>& answer) {
        if (root == nullptr) {
            return;
        }

        int answerSize = answer.size();
        if (level == answerSize) {
            answer.emplace_back(root->val);
        } else {
            answer[level] = max(answer[level], root->val);
        }

        dfs(root->left, level + 1, answer);
        dfs(root->right, level + 1, answer);
    }
    vector<int> bfs(TreeNode* root) {
        vector<int> retVal;

        queue<TreeNode*> bfsQueue;
        bfsQueue.emplace(root);

        while (bfsQueue.empty() == false) {
            int maxValue = numeric_limits<int>::min();  // -2^31 <= Node.val <= 2^31 - 1

            int bfsQueueCount = bfsQueue.size();
            for (int i = 0; i < bfsQueueCount; ++i) {
                TreeNode* node = bfsQueue.front();
                bfsQueue.pop();

                maxValue = max(maxValue, node->val);

                if (node->left != nullptr) {
                    bfsQueue.emplace(node->left);
                }
                if (node->right != nullptr) {
                    bfsQueue.emplace(node->right);
                }
            }

            retVal.emplace_back(maxValue);
        }

        return retVal;
    }
    vector<int> largestValues(TreeNode* root) {
        vector<int> retVal;

        if (root == nullptr) {
            return retVal;
        }

#if (DFS)
        dfs(root, 0, retVal);
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

    def dfs(self, root: Optional[TreeNode], level: int, answer: List[int]) -> None:
        if root is None:
            return

        if level == len(answer):
            answer.append(root.val)
        else:
            answer[level] = max(answer[level], root.val)

        self.dfs(root.left, level + 1, answer)
        self.dfs(root.right, level + 1, answer)

    def bfs(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        bfsQueue = deque([])
        bfsQueue.append(root)

        while bfsQueue:
            maxValue = float('-inf')    # -2^31 <= Node.val <= 2^31 - 1
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()

                maxValue = max(maxValue, node.val)

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            retVal.append(maxValue)

        return retVal

    def largestValues(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root is None:
            return retVal

        if self.method == 1:
            self.dfs(root, 0, retVal)
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal
```

</details>

## [530. Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/)

- [Official](https://leetcode.com/problems/minimum-absolute-difference-in-bst/editorial/)
- [Official](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/solutions/443276/er-cha-sou-suo-shu-de-zui-xiao-jue-dui-chai-by-lee/)

<details><summary>Description</summary>

```text
Given the root of a Binary Search Tree (BST),
return the minimum absolute difference between the values of any two different nodes in the tree.

Example 1:
Input: root = [4,2,6,1,3]
Output: 1

Example 2:
Input: root = [1,0,48,null,null,12,49]
Output: 1

Constraints:
The number of nodes in the tree is in the range [2, 10^4].
0 <= Node.val <= 10^5

Note: This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
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
void inorderTraversal(struct TreeNode* root, int* previous, int* miniDiff) {
    if (root == NULL) {
        return ;
    }
    inorderTraversal(root->left, previous, miniDiff);
    if ((*previous) != -1) {
        (*miniDiff) = fmin((*miniDiff), root->val-(*previous));
    }
    (*previous) = root->val;
    inorderTraversal(root->right, previous, miniDiff);
}
int getMinimumDifference(struct TreeNode* root){
    int retVal = INT_MAX;

    // 0 <= Node.val <= 10^5
    int previous = -1;
    inorderTraversal(root, &previous, &retVal);

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
    void inorderTraversal(struct TreeNode *root, int *previous, int *miniDiff) {
        if (root == NULL) {
            return;
        }
        inorderTraversal(root->left, previous, miniDiff);
        if ((*previous) != -1) {
            (*miniDiff) = min((*miniDiff), root->val - (*previous));
        }
        (*previous) = root->val;
        inorderTraversal(root->right, previous, miniDiff);
    }
    int getMinimumDifference(TreeNode* root) {
        int retVal = numeric_limits<int>::max();

        // 0 <= Node.val <= 10^5
        int previous = -1;
        inorderTraversal(root, &previous, &retVal);

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
        self.prevNode = None
        self.minDistance = float('inf')

    def inorderTraversal(self, root: Optional[TreeNode]):
        if root == None:
            return

        self.inorderTraversal(root.left)
        if self.prevNode != None:
            self.minDistance = min(self.minDistance, root.val - self.prevNode)
        self.prevNode = root.val
        self.inorderTraversal(root.right)

    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        self.inorderTraversal(root)
        retVal = self.minDistance

        return retVal
```

</details>

## [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

- [Official](https://leetcode.cn/problems/diameter-of-binary-tree/solutions/139683/er-cha-shu-de-zhi-jing-by-leetcode-solution/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

Example 1:
    1
   / \
  2   3
 / \
4   5
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

Example 2:
Input: root = [1,2]
Output: 1

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-100 <= Node.val <= 100
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
int maxDepth(struct TreeNode* root, int* diameter) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    int left = maxDepth(root->left, diameter);
    int right = maxDepth(root->right, diameter);
    (*diameter) = fmax(left + right, (*diameter));
    retVal = fmax(left, right) + 1;

    return retVal;
}
int diameterOfBinaryTree(struct TreeNode* root) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    maxDepth(root, &retVal);

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
    int diameter = 0;

   public:
    int maxDepth(TreeNode* root) {
        int retVal = 0;

        if (root == NULL) {
            return retVal;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        diameter = max(diameter, left + right);
        retVal = max(left, right) + 1;

        return retVal;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int retVal = 0;

        diameter = 0;

        if (root == nullptr) {
            return retVal;
        }
        maxDepth(root);
        retVal = diameter;

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
        self.diameter = 0

    def maxDepth(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        left = self.maxDepth(root.left)
        right = self.maxDepth(root.right)
        self.diameter = max(self.diameter, left+right)
        retVal = max(left, right) + 1

        return retVal

    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        self.diameter = 0

        if root is None:
            return retVal
        self.maxDepth(root)
        retVal = self.diameter

        return retVal
```

</details>

## [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)

- [Official](https://leetcode.com/problems/subtree-of-another-tree/solutions/2645723/subtree-of-another-tree/)
- [Official](https://leetcode.cn/problems/subtree-of-another-tree/solutions/233896/ling-yi-ge-shu-de-zi-shu-by-leetcode-solution)

<details><summary>Description</summary>

```text
Given the roots of two binary trees root and subRoot,
return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.

A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants.
The tree tree could also be considered as a subtree of itself.

Example 1:
    3
   / \
  4   5     4
 / \       / \
1   2     1   2
Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true

Example 2:
    3
   / \
  4   5     4
 / \       / \
1   2     1   2
   /
  0
Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false

Constraints:
The number of nodes in the root tree is in the range [1, 2000].
The number of nodes in the subRoot tree is in the range [1, 1000].
-10^4 <= root.val <= 10^4
-10^4 <= subRoot.val <= 10^4
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
bool isIdentical(struct TreeNode* pRoot1, struct TreeNode* pRoot2) {
    /* If any of the nodes is null, then both must be null.
     *
     *  isIdentical    | pRoot2 == NULL | pRoot2 != NULL
     *---------------------------------------------------
     *  pRoot1 == NULL |      true      |      false
     *  pRoot1 != NULL |      false     |      recursive
     *
     * If both nodes are non-empty, then they are identical only if
     *  1. Their values are equal
     *  2. Their left subtrees are identical
     *  3. Their right subtrees are identical
     */

    if ((pRoot1==NULL) && (pRoot2==NULL)) {
        return true;
    }

    if (((pRoot1!=NULL)&&(pRoot2==NULL)) || ((pRoot1==NULL)&&(pRoot2!=NULL))) {
        return false;
    }

    if (pRoot1->val != pRoot2->val) {
        return false;
    }

    if (isIdentical(pRoot1->left, pRoot2->left) == false) {
        return false;
    }

    if (isIdentical(pRoot1->right, pRoot2->right) == false) {
        return false;
    }

    return true;
}

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot) {
    if (root == NULL) {
        return false;
    }

    if (isIdentical(root, subRoot) == true) {
        return true;
    }

    if (isSubtree(root->left, subRoot) == true) {
        return true;
    }

    if (isSubtree(root->right, subRoot) == true) {
        return true;
    }

    return false;
}
```

</details>

</details>

## [589. N-ary Tree Preorder Traversal](https://leetcode.com/problems/n-ary-tree-preorder-traversal/)

- [Official](https://leetcode.cn/problems/n-ary-tree-preorder-traversal/solutions/1317175/n-cha-shu-de-qian-xu-bian-li-by-leetcode-bg99/)

<details><summary>Description</summary>

```text
Given the root of an n-ary tree, return the preorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal.
Each group of children is separated by the null value (See examples)

Example 1:
     1
   / | \
  3  2  4
 / \
5   6
Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]

Example 2:
        1
 /    /   \    \
2    3     4    5
    / \    |   / \
   6   7   8  9   10
       |   |  |
      11  12 13
       |
      14
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
0 <= Node.val <= 10^4
The height of the n-ary tree is less than or equal to 1000.

Follow up: Recursive solution is trivial, could you do it iteratively?
```

</details>

<details><summary>C</summary>

```c
void preorderTraversal(struct Node* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount)++;
    int i;
    for (i = 0; i < root->numChildren; ++i) {
        preorderTraversal(root->children[i], pTreeNodeCount, pTreeArray);
    }
}
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorder(struct Node* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 10^4].
    pRetVal = (int*)malloc(10000 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    preorderTraversal(root, returnSize, pRetVal);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
   public:
    void preorderTraversal(Node *root, vector<int> &retVal) {
        if (root == NULL) {
            return;
        }
        retVal.push_back(root->val);
        int i;
        for (auto iter : root->children) {
            preorderTraversal(iter, retVal);
        }
    }
    vector<int> preorder(Node *root) {
        vector<int> retVal;

        preorderTraversal(root, retVal);

        return retVal;
    }
};
```

</details>

## [590. N-ary Tree Postorder Traversal](https://leetcode.com/problems/n-ary-tree-postorder-traversal/)

- [Official](https://leetcode.cn/problems/n-ary-tree-postorder-traversal/solutions/1327327/n-cha-shu-de-hou-xu-bian-li-by-leetcode-txesi/)

<details><summary>Description</summary>

```text
Given the root of an n-ary tree, return the postorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal.
Each group of children is separated by the null value (See examples)

Example 1:
     1
   / | \
  3  2  4
 / \
5   6
Input: root = [1,null,3,2,4,null,5,6]
Output: [5,6,3,2,4,1]

Example 2:
        1
 /    /   \    \
2    3     4    5
    / \    |   / \
   6   7   8  9   10
       |   |  |
      11  12 13
       |
      14
Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
0 <= Node.val <= 10^4
The height of the n-ary tree is less than or equal to 1000.

Follow up: Recursive solution is trivial, could you do it iteratively?
```

</details>

<details><summary>C</summary>

```c
void postorderTraversal(struct Node* root, int* pTreeNodeCount, int* pTreeArray) {
    if (root == NULL) {
        return;
    }
    int i;
    for (i = 0; i < root->numChildren; ++i) {
        postorderTraversal(root->children[i], pTreeNodeCount, pTreeArray);
    }
    *(pTreeArray + (*pTreeNodeCount)) = root->val;
    (*pTreeNodeCount) = (*pTreeNodeCount) + 1;
}
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* postorder(struct Node* root, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    if (root == NULL) {
        return pRetVal;
    }

    // The number of nodes in the tree is in the range [0, 10^4].
    pRetVal = (int*)malloc(10000 * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    postorderTraversal(root, returnSize, pRetVal);

    return pRetVal;
}
```

</details>

<details><summary>C++</summary>

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
   public:
    void postorderTraversal(Node *root, vector<int> &retVal) {
        if (root == NULL) {
            return;
        }
        int i;
        for (auto iter : root->children) {
            postorderTraversal(iter, retVal);
        }
        retVal.push_back(root->val);
    }
    vector<int> postorder(Node *root) {
        vector<int> retVal;

        postorderTraversal(root, retVal);

        return retVal;
    }
};
```

</details>

## [606. Construct String from Binary Tree](https://leetcode.com/problems/construct-string-from-binary-tree/)

- [Official](https://leetcode.cn/problems/construct-string-from-binary-tree/solutions/1343920/gen-ju-er-cha-shu-chuang-jian-zi-fu-chua-e1af/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, construct a string
consisting of parenthesis and integers from a binary tree with the preorder traversal way, and return it.

Omit all the empty parenthesis pairs
that do not affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: root = [1,2,3,4]
Output: "1(2(4))(3)"
Explanation: Originally, it needs to be "1(2(4)())(3()())",
but you need to omit all the unnecessary empty parenthesis pairs.
And it will be "1(2(4))(3)"

Example 2:
Input: root = [1,2,3,null,4]
Output: "1(2()(4))(3)"
Explanation: Almost the same as the first example,
except we cannot omit the first parenthesis pair
to break the one-to-one mapping relationship between the input and the output.

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-1000 <= Node.val <= 1000
```

</details>

<details><summary>C</summary>

```c
void inorder(struct TreeNode* root, char* pRetVal, int* returnSize) {
    if (root == NULL) {
        return;
    }

    snprintf(pRetVal + strlen(pRetVal), (*returnSize), "%d", root->val);

    if (root->left != NULL) {
        pRetVal[strlen(pRetVal)] = '(';
        inorder(root->left, pRetVal, returnSize);
        pRetVal[strlen(pRetVal)] = ')';
    }

    if (root->right != NULL) {
        if (root->left == NULL) {
            pRetVal[strlen(pRetVal)] = '(';
            pRetVal[strlen(pRetVal)] = ')';
        }

        pRetVal[strlen(pRetVal)] = '(';
        inorder(root->right, pRetVal, returnSize);
        pRetVal[strlen(pRetVal)] = ')';
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
char* tree2str(struct TreeNode* root) {
    char* pRetVal = NULL;

    /* Constraints
     *  The number of nodes in the tree is in the range [1, 10^4].
     *  -1000 <= Node.val <= 1000
     */
    int returnSize = 1e5;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    inorder(root, pRetVal, &returnSize);
    pRetVal[strlen(pRetVal)] = '\0';

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
    string tree2str(TreeNode* root) {
        string retVal = "";

        if (root == nullptr) {
            return retVal;
        }

        retVal += to_string(root->val);

        if (root->left != nullptr) {
            retVal += "(" + tree2str(root->left) + ")";
        }

        if (root->right != nullptr) {
            if (root->left == nullptr) {
                retVal += "()";
            }
            retVal += "(" + tree2str(root->right) + ")";
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
    def tree2str(self, root: Optional[TreeNode]) -> str:
        retVal = ""

        if root == None:
            return retVal

        retVal += str(root.val)

        if root.left != None:
            retVal += "(" + self.tree2str(root.left) + ")"

        if root.right != None:
            if root.left == None:
                retVal += "()"
            retVal += "(" + self.tree2str(root.right) + ")"

        return retVal
```

</details>

## [617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/)

- [Official](https://leetcode.com/problems/merge-two-binary-trees/editorial/)
- [Official](https://leetcode.cn/problems/merge-two-binary-trees/solutions/424201/he-bing-er-cha-shu-by-leetcode-solution/)

<details><summary>Description</summary>

```text
You are given two binary trees root1 and root2.

Imagine that when you put one of them to cover the other,
some nodes of the two trees are overlapped while the others are not.
You need to merge the two trees into a new binary tree.
The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node.
Otherwise, the NOT null node will be used as the node of the new tree.

Return the merged tree.

Note: The merging process must start from the root nodes of both trees.

Example 1:
    1       2           3
   / \     / \         / \
  3   2   1   3       4   5
 /         \   \     / \   \
5           4   7   5   4   7
Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
Output: [3,4,5,5,4,null,7]

Example 2:
Input: root1 = [1], root2 = [1,2]
Output: [2,2]

Constraints:
The number of nodes in both trees is in the range [0, 2000].
-10^4 <= Node.val <= 10^4
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
struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
    struct TreeNode* pRetVal = NULL;

    if ((root1 == NULL) && (root2 == NULL)) {
        return pRetVal;
    } else if ((root1 != NULL) && (root2 == NULL)) {
        pRetVal = root1;
        return pRetVal;
    } else if ((root1 == NULL) && (root2 != NULL)) {
        pRetVal = root2;
        return pRetVal;
    }

    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    root1->val += root2->val;
    pRetVal = root1;

    return pRetVal;
}
```

</details>

## [652. Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/)

- [Official](https://leetcode.cn/problems/find-duplicate-subtrees/solutions/1798953/xun-zhao-zhong-fu-de-zi-shu-by-leetcode-zoncw/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

Example 1:
             (1)
         /         \
       (2)         (3)
       / \         / \
     (4) (null)  (2) (4)
     / \         /
(null) (null)  (4)
Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:
  (2)
  / \
(1) (1)
Input: root = [2,1,1]
Output: [[1]]

Example 3:
        (2)
    /         \
  (2)         (2)
  / \         / \
(3) (null)  (3) (null)
Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]

Constraints:
The number of the nodes in the tree will be in the range [1, 5000]
-200 <= Node.val <= 200
```

</details>

<details><summary>C</summary>

```c
typedef struct {
    char *key;
    struct TreeNode *val;
    UT_hash_handle hh;
} HashMapItem;
typedef struct {
    void *key;
    UT_hash_handle hh;
} HashSetItem;
char *inorder(struct TreeNode *node, HashMapItem **seen, HashSetItem **repeat) {
    char *pSerial = NULL;

    if (node == NULL) {
        return "";
    }

    char *pLeftStr = inorder(node->left, seen, repeat);
    char *pRightStr = inorder(node->right, seen, repeat);
    // -200 <= Node.val <= 200
    pSerial = (char *)calloc(8 + strlen(pLeftStr) + strlen(pRightStr), sizeof(char));
    if (pSerial == NULL) {
        perror("calloc");
        return "";
    }
    sprintf(pSerial, "(%s%d%s)", pLeftStr, node->val, pRightStr);

    HashMapItem *pHashMapEntry = NULL;
    HASH_FIND_STR(*seen, pSerial, pHashMapEntry);
    if (pHashMapEntry != NULL) {
        HashSetItem *pHashSetEntry = NULL;
        HASH_FIND_PTR(*repeat, &(pHashMapEntry->val), pHashSetEntry);
        if (pHashSetEntry == NULL) {
            pHashSetEntry = (HashSetItem *)malloc(sizeof(HashSetItem));
            if (pHashSetEntry == NULL) {
                perror("malloc");
                return "";
            }
            pHashSetEntry->key = (void *)pHashMapEntry->val;
            HASH_ADD_PTR(*repeat, key, pHashSetEntry);
        }
    } else {
        pHashMapEntry = (HashMapItem *)malloc(sizeof(HashMapItem));
        if (pHashMapEntry == NULL) {
            perror("malloc");
            return "";
        }
        pHashMapEntry->key = pSerial;
        pHashMapEntry->val = node;
        HASH_ADD_STR(*seen, key, pHashMapEntry);
    }

    return pSerial;
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
struct TreeNode **findDuplicateSubtrees(struct TreeNode *root, int *returnSize) {
    struct TreeNode **pRetVal = NULL;

    HashMapItem *seen = NULL;
    HashSetItem *repeat = NULL;
    inorder(root, &seen, &repeat);

    (*returnSize) = HASH_COUNT(repeat);
    pRetVal = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * (*returnSize));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int pos = 0;
    HashSetItem *pCurrent;
    HashSetItem *pTemp;
    HASH_ITER(hh, repeat, pCurrent, pTemp) {
        pRetVal[pos++] = (struct TreeNode *)pCurrent->key;
        HASH_DEL(repeat, pCurrent);
        free(pCurrent);
    }

    HashMapItem *pCurrentMap;
    HashMapItem *pTempMap;
    HASH_ITER(hh, seen, pCurrentMap, pTempMap) {
        HASH_DEL(seen, pCurrentMap);
        free(pCurrentMap->key);
        free(pCurrentMap);
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
    string serialize(TreeNode* node, unordered_map<string, vector<TreeNode*>>& map) {
        if (node == nullptr) {
            return "";
        }

        string s = "(" + serialize(node->left, map) + to_string(node->val) + serialize(node->right, map) + ")";
        map[s].push_back(node);

        return s;
    }

   public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> retVal;

        // https://leetcode.com/problems/find-duplicate-subtrees/solutions/106055/c-java-clean-code-with-explanation/
        unordered_map<string, vector<TreeNode*>> map;
        serialize(root, map);
        for (auto it = map.begin(); it != map.end(); it++) {
            if (it->second.size() > 1) {
                retVal.push_back(it->second[0]);
            }
        }

        return retVal;
    }
};
```

</details>

## [653. Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)

<details><summary>Description</summary>

```text
Given the root of a Binary Search Tree and a target number k,
return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
    5
   / \
  3   6
 / \   \
2   4   7
Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:
    5
   / \
  3   6
 / \   \
2   4   7
Input: root = [5,3,6,2,4,null,7], k = 28
Output: false

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^4 <= Node.val <= 10^4
root is guaranteed to be a valid binary search tree.
-10^5 <= k <= 10^5
```

</details>

<details><summary>C</summary>

```c
void inOrder(struct TreeNode* pRoot, int* pTreeArray, int* pTreeNode) {
    if (pRoot == NULL) {
        return;
    }
    inOrder(pRoot->left, pTreeArray, pTreeNode);
    pTreeArray[(*pTreeNode)++] = pRoot->val;
    inOrder(pRoot->right, pTreeArray, pTreeNode);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool findTarget(struct TreeNode* root, int k) {
    bool retVal = false;

    // get sorted array by Binary Search Tree Inorder Traversal
#define MAX_NODE (10000)  // The number of nodes in the tree is in the range [1, 10^4]
    int treeArray[MAX_NODE];
    memset(treeArray, 0, sizeof(treeArray));
    int treeNode = 0;
    inOrder(root, treeArray, &treeNode);

    // move head and tail index of sorted array to check target sum
    int head = 0;
    int tail = treeNode - 1;
    while (head < tail) {
        if (treeArray[head] + treeArray[tail] == k) {
            retVal = true;
            break;
        } else if (treeArray[head] + treeArray[tail] > k) {
            --tail;
        } else if (treeArray[head] + treeArray[tail] < k) {
            ++head;
        }
    }

    return retVal;
}
```

</details>

## [655. Print Binary Tree](https://leetcode.com/problems/print-binary-tree/)

- [Official](https://leetcode.cn/problems/print-binary-tree/solutions/1763780/shu-chu-er-cha-shu-by-leetcode-solution-cnxu/)

<details><summary>Description</summary>

```text
Given the root of a binary tree,
construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree.

The formatted layout matrix should be constructed using the following rules:
- The height of the tree is height and the number of rows m should be equal to height + 1.
- The number of columns n should be equal to 2height+1 - 1.
- Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
- For each node that has been placed in the matrix at position res[r][c],
  place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
- Continue this process until all the nodes in the tree have been placed.
- Any empty cells should contain the empty string "".

Return the constructed matrix res.

Example 1:
Input: root = [1,2]
Output:
[["","1",""],
 ["2","",""]]

Example 2:
Input: root = [1,2,3,null,4]
Output:
[["","","","1","","",""],
 ["","2","","","","3",""],
 ["","","4","","","",""]]

Constraints:
The number of nodes in the tree is in the range [1, 2^10].
-99 <= Node.val <= 99
The depth of the tree will be in the range [1, 10].
```

</details>

<details><summary>C</summary>

```c
#define DFS (0)
#define BFS (1)
#define MAX_VAL_LEN (32)
#if (DFS)
int dfsDepth(struct TreeNode* root) {
    int retVal = 0;

    if (root->left) {
        retVal = fmax(retVal, dfsDepth(root->left) + 1);
    }
    if (root->right) {
        retVal = fmax(retVal, dfsDepth(root->right) + 1);
    }

    return retVal;
}
void dfs(char*** pRetVal, struct TreeNode* root, int row, int col, int height) {
    sprintf(pRetVal[row][col], "%d", root->val);
    if (root->left) {
        dfs(pRetVal, root->left, row + 1, col - (1 << (height - row - 1)), height);
    }
    if (root->right) {
        dfs(pRetVal, root->right, row + 1, col + (1 << (height - row - 1)), height);
    }
}
#elif (BFS)
#define MAX_NODE_SIZE (1024)

typedef struct {
    struct TreeNode* node;
    int row;
    int col;
} Tuple;

int bfsDepth(struct TreeNode* root) {
    int retVal = -1;

    struct TreeNode** bfsQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAX_NODE_SIZE);
    if (bfsQueue == NULL) {
        perror("malloc");
        return retVal;
    }
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail++] = root;

    struct TreeNode* pTmp;
    int bfsQueueSize;
    while (bfsHead != bfsTail) {
        bfsQueueSize = bfsTail - bfsHead;
        retVal++;

        while (bfsQueueSize) {
            bfsQueueSize--;

            pTmp = bfsQueue[bfsHead++];
            if (pTmp->left) {
                bfsQueue[bfsTail++] = pTmp->left;
            }
            if (pTmp->right) {
                bfsQueue[bfsTail++] = pTmp->right;
            }
        }
    }
    free(bfsQueue);
    bfsQueue = NULL;

    return retVal;
}
Tuple* creatTuple(struct TreeNode* node, int row, int col) {
    Tuple* pObj = (Tuple*)malloc(sizeof(Tuple));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->node = node;
    pObj->row = row;
    pObj->col = col;

    return pObj;
}
void bfs(char*** pRetVal, struct TreeNode* root, int n, int height) {
    Tuple** bfsQueue = (Tuple**)malloc(sizeof(Tuple*) * n);
    if (bfsQueue == NULL) {
        perror("malloc");
        return;
    }
    int bfsHead = 0;
    int bfsTail = 0;
    bfsQueue[bfsTail++] = creatTuple(root, 0, (n - 1) / 2);

    int row, col;
    Tuple* pTmp;
    while (bfsHead != bfsTail) {
        pTmp = bfsQueue[bfsHead++];

        row = pTmp->row;
        col = pTmp->col;
        sprintf(pRetVal[row][col], "%d", pTmp->node->val);
        if (pTmp->node->left) {
            bfsQueue[bfsTail++] = creatTuple(pTmp->node->left, row + 1, col - (1 << (height - row - 1)));
        }
        if (pTmp->node->right) {
            bfsQueue[bfsTail++] = creatTuple(pTmp->node->right, row + 1, col + (1 << (height - row - 1)));
        }
    }

    int i;
    for (i = 0; i < bfsTail; i++) {
        free(bfsQueue[i]);
        bfsQueue[i] = NULL;
    }
    free(bfsQueue);
    bfsQueue = NULL;
}
#endif
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** printTree(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

#if (DFS)
    int height = dfsDepth(root);
    int m = height + 1;
    int n = (1 << (height + 1)) - 1;
#elif (BFS)
    int height = bfsDepth(root);
    int m = height + 1;
    int n = (1 << (height + 1)) - 1;
#endif

    (*returnSize) = 0;
    pRetVal = (char***)malloc(sizeof(char**) * m);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int i, j;
    for (i = 0; i < m; i++) {
        pRetVal[i] = (char**)malloc(sizeof(char*) * n);
        if (pRetVal[i] == NULL) {
            perror("malloc");
            return pRetVal;
        }
        for (j = 0; j < n; j++) {
            pRetVal[i][j] = (char*)malloc(sizeof(char) * MAX_VAL_LEN);
            if (pRetVal[i][j] == NULL) {
                perror("malloc");
                return pRetVal;
            }
            pRetVal[i][j][0] = '\0';
        }
    }
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * m);
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = m;

#if (DFS)
    printf("Depth-First Search\n\n");
    dfs(pRetVal, root, 0, (n - 1) / 2, height);
#elif (BFS)
    printf("Breadth-First Search\n\n");
    bfs(pRetVal, root, n, height);
#endif

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
#define DFS (0)
#define BFS (1)
   public:
    Solution() {
#if (DFS)
        cout << "Depth-First Search\n\n";
#elif (BFS)
        cout << "Breadth-First Search\n\n";
#endif
    }
#if (DFS)
    int dfsDepth(TreeNode* root) {
        int retVal = 0;

        if (root->left) {
            retVal = max(retVal, dfsDepth(root->left) + 1);
        }
        if (root->right) {
            retVal = max(retVal, dfsDepth(root->right) + 1);
        }

        return retVal;
    }
    void dfs(vector<vector<string>>& retVal, TreeNode* root, int row, int col, int& height) {
        retVal[row][col] = to_string(root->val);
        if (root->left) {
            dfs(retVal, root->left, row + 1, col - (1 << (height - row - 1)), height);
        }
        if (root->right) {
            dfs(retVal, root->right, row + 1, col + (1 << (height - row - 1)), height);
        }
    }
#elif (BFS)
    int bfsDepth(TreeNode* root) {
        int retVal = -1;

        queue<TreeNode*> record;
        record.push(root);
        while (record.empty() == false) {
            int recordSize = record.size();
            retVal++;
            while (recordSize) {
                recordSize--;

                auto node = record.front();
                record.pop();
                if (node->left) {
                    record.push(node->left);
                }
                if (node->right) {
                    record.push(node->right);
                }
            }
        }

        return retVal;
    }
    void bfs(vector<vector<string>>& retVal, TreeNode* root, int n, int height) {
        queue<tuple<TreeNode*, int, int>> bfsQueue;
        bfsQueue.push({root, 0, (n - 1) / 2});

        while (bfsQueue.empty() == false) {
            auto node = bfsQueue.front();
            bfsQueue.pop();

            int row = get<1>(node);
            int col = get<2>(node);
            retVal[row][col] = to_string(get<0>(node)->val);

            if (get<0>(node)->left) {
                bfsQueue.push({get<0>(node)->left, row + 1, col - (1 << (height - row - 1))});
            }
            if (get<0>(node)->right) {
                bfsQueue.push({get<0>(node)->right, row + 1, col + (1 << (height - row - 1))});
            }
        }
    }
#endif
    vector<vector<string>> printTree(TreeNode* root) {
#if (DFS)
        int height = dfsDepth(root);
        int m = height + 1;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> retVal(m, vector<string>(n, ""));
        dfs(retVal, root, 0, (n - 1) / 2, height);
#elif (BFS)
        int height = bfsDepth(root);
        int m = height + 1;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> retVal(m, vector<string>(n, ""));
        bfs(retVal, root, n, height);
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

    def dfsDepth(self, node: Optional[TreeNode]) -> int:
        retVal = 0

        leftDepth = self.dfsDepth(node.left) + 1 if node.left else 0
        rightDepth = self.dfsDepth(node.right) + 1 if node.right else 0
        retVal = max(leftDepth, rightDepth)

        return retVal

    def dfs(self, node: Optional[TreeNode], height: int, row: int, col: int, retVal: List[List[str]]) -> None:
        retVal[row][col] = str(node.val)
        if node.left:
            self.dfs(node.left, height, row + 1, col - 2 ** (height - row - 1), retVal)
        if node.right:
            self.dfs(node.right, height, row + 1, col + 2 ** (height - row - 1), retVal)

    def bfsDepth(self, root: Optional[TreeNode]) -> int:
        retVal = -1

        record = [root]
        while record:
            retVal += 1
            tmp = record
            record = []
            for node in tmp:
                if node.left:
                    record.append(node.left)
                if node.right:
                    record.append(node.right)

        return retVal

    def bfs(self, root: Optional[TreeNode], height: int, n: int, retVal: List[List[str]]) -> None:
        bfsQueue = deque([(root, 0, (n - 1) // 2)])
        while bfsQueue:
            node, row, col = bfsQueue.popleft()
            retVal[row][col] = str(node.val)
            if node.left:
                bfsQueue.append((node.left, row + 1, col - 2 ** (height - row - 1)))
            if node.right:
                bfsQueue.append((node.right, row + 1, col + 2 ** (height - row - 1)))

    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        retVal = []

        if self.method == 1:
            height = self.dfsDepth(root)
            m = height + 1
            n = 2 ** m - 1
            retVal = [[''] * n for _ in range(m)]
            self.dfs(root, height, 0, (n - 1) // 2, retVal)
        elif self.method == 2:
            height = self.bfsDepth(root)
            m = height + 1
            n = 2 ** m - 1
            retVal = [[''] * n for _ in range(m)]
            self.bfs(root, height, n, retVal)

        return retVal
```

</details>

## [662. Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/)

- [Official](https://leetcode.cn/problems/maximum-width-of-binary-tree/solutions/1776589/er-cha-shu-zui-da-kuan-du-by-leetcode-so-9zp3/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes),
where the null nodes between the end-nodes that would be present in a complete binary tree
extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed integer.

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).

Constraints:
The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100
```

</details>

<details><summary>C</summary>

```c
#define MAX_NODE_SIZE (3000)  // The number of nodes in the tree is in the range [1, 3000].
typedef struct {
    struct TreeNode* node;
    unsigned long long index;
} Pair;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int widthOfBinaryTree(struct TreeNode* root) {
    int retVal = 1;

    int levelSize = 0;
    Pair* pLevel = (Pair*)malloc(MAX_NODE_SIZE * sizeof(Pair));
    if (pLevel == NULL) {
        perror("malloc");
        return retVal;
    }
    pLevel[levelSize].node = root;
    pLevel[levelSize].index = 1LL;
    levelSize++;

    int tmpSize = 0;
    Pair* pTmp = (Pair*)malloc(MAX_NODE_SIZE * sizeof(Pair));
    if (pTmp == NULL) {
        perror("malloc");
        free(pLevel);
        pLevel = NULL;
        return retVal;
    }
    unsigned long long maxValue;
    int i;
    Pair* pSwap = NULL;
    while (levelSize > 0) {
        maxValue = retVal;
        retVal = fmax(maxValue, pLevel[levelSize - 1].index - pLevel[0].index + 1);

        tmpSize = 0;
        for (i = 0; i < levelSize; ++i) {
            if (pLevel[i].node->left) {
                pTmp[tmpSize].node = pLevel[i].node->left;
                pTmp[tmpSize].index = pLevel[i].index * 2;
                tmpSize++;
            }
            if (pLevel[i].node->right) {
                pTmp[tmpSize].node = pLevel[i].node->right;
                pTmp[tmpSize].index = pLevel[i].index * 2 + 1;
                tmpSize++;
            }
        }
        levelSize = tmpSize;
        pSwap = pLevel;
        pLevel = pTmp;
        pTmp = pSwap;
    }

    free(pLevel);
    pLevel = NULL;
    free(pTmp);
    pTmp = NULL;

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
    int widthOfBinaryTree(TreeNode* root) {
        int retVal = 1;

        vector<pair<TreeNode*, unsigned long long>> level;
        level.emplace_back(root, 1L);
        while (level.empty() == false) {
            unsigned long long maxValue = retVal;
            retVal = max(maxValue, level.back().second - level[0].second + 1);

            vector<pair<TreeNode*, unsigned long long>> tmp;
            for (auto& [node, index] : level) {
                if (node->left) {
                    tmp.emplace_back(node->left, index * 2);
                }
                if (node->right) {
                    tmp.emplace_back(node->right, index * 2 + 1);
                }
            }
            level = move(tmp);
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
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        retVal = 1

        level = [[root, 1]]
        while level:
            retVal = max(retVal, level[-1][1] - level[0][1] + 1)

            tmp = []
            for node, index in level:
                if node.left:
                    tmp.append([node.left, index * 2])
                if node.right:
                    tmp.append([node.right, index * 2 + 1])
            level = tmp

        return retVal
```

</details>

## [700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)

<details><summary>Description</summary>

```text
You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree rooted with that node.
If such a node does not exist, return null.

Example 1:
    4
   / \
  2   7
 / \
1   3
Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]

Example 2:
    4
   / \
  2   7
 / \
1   3
Input: root = [4,2,7,1,3], val = 5
Output: []

Constraints:
The number of nodes in the tree is in the range [1, 5000].
1 <= Node.val <= 10^7
root is a binary search tree.
1 <= val <= 10^7
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
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    struct TreeNode* pRetVal = NULL;

    if (root == NULL) {
        return pRetVal;
    }

    if (root->val == val) {
        pRetVal = root;
    } else if (root->val > val) {
        pRetVal = searchBST(root->left, val);
    } else if (root->val < val) {
        pRetVal = searchBST(root->right, val);
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
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* pRetVal = nullptr;

        if (root == nullptr) {
            return pRetVal;
        }

        if (root->val == val) {
            pRetVal = root;
        } else if (root->val > val) {
            pRetVal = searchBST(root->left, val);
        } else if (root->val < val) {
            pRetVal = searchBST(root->right, val);
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
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        retVal = None

        if (root == None):
            return retVal

        if root.val == val:
            retVal = root
        elif root.val > val:
            retVal = self.searchBST(root.left, val)
        elif root.val < val:
            retVal = self.searchBST(root.right, val)

        return retVal
```

</details>

## [701. Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)

<details><summary>Description</summary>

```text
You are given the root node of a binary search tree (BST) and a value to insert into the tree.
Return the root node of the BST after the insertion.
It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion.
You can return any of them.

Example 1:
    4          4           5
   / \       /   \       /   \
  2   7     2     7     2     7
 / \       / \   /     / \
1   3     1   3 5     1   3
                           \
                            4
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]
Explanation: Another accepted tree is:

Example 2:
Input: root = [40,20,60,10,30,50,70], val = 25
Output: [40,20,60,10,30,50,70,null,null,25]

Constraints:
The number of nodes in the tree will be in the range [0, 10^4].
-10^8 <= Node.val <= 10^8
All the values Node.val are unique.
-10^8 <= val <= 10^8
It's guaranteed that val does not exist in the original BST.
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
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    struct TreeNode* pRetVal = root;

    if (pRetVal == NULL) {
        pRetVal = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (pRetVal == NULL) {
            perror("malloc");
            return pRetVal;
        }
        pRetVal->val = val;
        pRetVal->left = NULL;
        pRetVal->right = NULL;

        return pRetVal;
    }

    if (pRetVal->val > val) {
        pRetVal->left = insertIntoBST(pRetVal->left, val);
    } else if (pRetVal->val <= val) {
        pRetVal->right = insertIntoBST(pRetVal->right, val);
    }

    return pRetVal;
}
```

</details>

## [783. Minimum Distance Between BST Nodes](https://leetcode.com/problems/minimum-distance-between-bst-nodes/)  1303

- [Official](https://leetcode.com/problems/minimum-distance-between-bst-nodes/solutions/3070288/minimum-distance-between-bst-nodes/)
- [Official](https://leetcode.cn/problems/minimum-distance-between-bst-nodes/solutions/595171/er-cha-sou-suo-shu-jie-dian-zui-xiao-ju-8u87w/)

<details><summary>Description</summary>

```text
Given the root of a Binary Search Tree (BST),
return the minimum difference between the values of any two different nodes in the tree.

Example 1:
Input: root = [4,2,6,1,3]
Output: 1

Example 2:
Input: root = [1,0,48,null,null,12,49]
Output: 1

Constraints:
The number of nodes in the tree is in the range [2, 100].
0 <= Node.val <= 10^5

Note: This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
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
void inorderTraversal(struct TreeNode* root, int* previous, int* miniDiff) {
    if (root == NULL) {
        return ;
    }
    inorderTraversal(root->left, previous, miniDiff);
    if ((*previous) != -1) {
        (*miniDiff) = fmin((*miniDiff), root->val-(*previous));
    }
    (*previous) = root->val;
    inorderTraversal(root->right, previous, miniDiff);
}
int minDiffInBST(struct TreeNode* root){
    int retVal = INT_MAX;

    // 0 <= Node.val <= 10^5
    int previous = -1;
    inorderTraversal(root, &previous, &retVal);

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
    void inorderTraversal(struct TreeNode *root, int *previous, int *miniDiff) {
        if (root == NULL) {
            return;
        }
        inorderTraversal(root->left, previous, miniDiff);
        if ((*previous) != -1) {
            (*miniDiff) = min((*miniDiff), root->val - (*previous));
        }
        (*previous) = root->val;
        inorderTraversal(root->right, previous, miniDiff);
    }
    int minDiffInBST(TreeNode *root) {
        int retVal = numeric_limits<int>::max();

        // 0 <= Node.val <= 10^5
        int previous = -1;
        inorderTraversal(root, &previous, &retVal);

        return retVal;
    }
};
```

</details>

## [863. All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)  1663

- [Official](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/all-nodes-distance-k-in-binary-tree/solutions/900027/er-cha-shu-zhong-suo-you-ju-chi-wei-k-de-qbla/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, the value of a target node target, and an integer k,
return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

Example 1:
     3
   /   \
  5     1
 / \   / \
6   2 0   8
   / \
  7   4
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

Example 2:
Input: root = [1], target = 1, k = 3
Output: []

Constraints:
The number of nodes in the tree is in the range [1, 500].
0 <= Node.val <= 500
All the values Node.val are unique.
target is the value of one of the nodes in the tree.
0 <= k <= 1000
```

</details>

<details><summary>C</summary>

```c
#define MAX_NODE (500 + 4)  // The number of nodes in the tree is in the range [1, 500].
struct GraphNode {
    int adjacent[4];  // the adjacent of binary tree would not exceed 3
    int adjacentSize;
};
void binaryTreeToGraph(struct TreeNode* root, struct GraphNode* graph) {
    if (root == NULL) {
        return;
    }

    int graphIdx, adjacentIdx;
    if (root->left != NULL) {
        graphIdx = root->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->left->val;
        graph[graphIdx].adjacentSize += 1;

        graphIdx = root->left->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->val;
        graph[graphIdx].adjacentSize += 1;

        binaryTreeToGraph(root->left, graph);
    }
    if (root->right != NULL) {
        graphIdx = root->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->right->val;
        graph[graphIdx].adjacentSize += 1;

        graphIdx = root->right->val;
        adjacentIdx = graph[graphIdx].adjacentSize;
        graph[graphIdx].adjacent[adjacentIdx] = root->val;
        graph[graphIdx].adjacentSize += 1;

        binaryTreeToGraph(root->right, graph);
    }
}
#define MAX_QUEUE_SIZE ((MAX_NODE)*2)
struct QueueNode {
    int vertex;
    int distance;
};
int* bfs(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize, struct GraphNode* graph) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int*)malloc((MAX_NODE) * sizeof(int));  // The number of nodes in the tree is in the range [1, 500].
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_NODE) * sizeof(int)));

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct QueueNode bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail].vertex = target->val;
    bfsQueue[bfsQueueTail].distance = 0;
    ++bfsQueueTail;

    // The number of nodes in the tree is in the range [1, 500].
    // 0 <= Node.val <= 500; All the values Node.val are unique.
    bool visited[(MAX_NODE)];
    memset(visited, false, sizeof(visited));
    visited[target->val] = true;

    int neighbor;
    int vertex, distance;
    int i;
    while (bfsQueueHead < bfsQueueTail) {
        vertex = bfsQueue[bfsQueueHead].vertex;
        distance = bfsQueue[bfsQueueHead].distance;
        ++bfsQueueHead;

        if (distance == k) {
            pRetVal[(*returnSize)++] = vertex;
        }

        for (i = 0; i < graph[vertex].adjacentSize; ++i) {
            neighbor = graph[vertex].adjacent[i];
            if (visited[neighbor] == true) {
                continue;
            }
            bfsQueue[bfsQueueTail].vertex = neighbor;
            bfsQueue[bfsQueueTail].distance = distance + 1;
            ++bfsQueueTail;
            visited[neighbor] = true;
        }
    }

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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distanceK(struct TreeNode* root, struct TreeNode* target, int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    // 0 <= Node.val <= 500; All the values Node.val are unique.
    struct GraphNode* pGraph = (struct GraphNode*)malloc((MAX_NODE) * sizeof(struct GraphNode));
    if (pGraph == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pGraph, 0, ((MAX_NODE) * sizeof(struct GraphNode)));
    binaryTreeToGraph(root, pGraph);
#if (0)
    for (int i = 0; i < (MAX_NODE); ++i) {
        printf("%d: [", i);
        for (int j = 0; j < pGraph[i].adjacentSize; ++j) {
            printf("%d ", pGraph[i].adjacent[j]);
        }
        printf("]\n");
    }
#endif

    pRetVal = bfs(root, target, k, returnSize, pGraph);

    //
    free(pGraph);
    pGraph = NULL;

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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    void binaryTreeToGraph(TreeNode* root, unordered_map<int, vector<int>>& graph) {
        if (root == nullptr) {
            return;
        }

        if (root->left != nullptr) {
            graph[root->val].emplace_back(root->left->val);
            graph[root->left->val].emplace_back(root->val);
            binaryTreeToGraph(root->left, graph);
        }
        if (root->right != nullptr) {
            graph[root->val].emplace_back(root->right->val);
            graph[root->right->val].emplace_back(root->val);
            binaryTreeToGraph(root->right, graph);
        }
    }
    vector<int> bfs(TreeNode* root, TreeNode* target, int k, unordered_map<int, vector<int>>& graph) {
        vector<int> retVal;

        queue<pair<int, int>> bfsQueue;
        bfsQueue.emplace(target->val, 0);

        vector<int> visited;
        visited.emplace_back(target->val);

        while (bfsQueue.empty() == false) {
            auto [current, distance] = bfsQueue.front();
            bfsQueue.pop();
            if (distance == k) {
                retVal.emplace_back(current);
            }

            for (auto neighbor : graph[current]) {
                if (find(visited.begin(), visited.end(), neighbor) != visited.end()) {
                    continue;
                }
                bfsQueue.emplace(neighbor, distance + 1);
                visited.emplace_back(neighbor);
            }
        }

        return retVal;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> retVal;

        unordered_map<int, vector<int>> graph;
        binaryTreeToGraph(root, graph);
        retVal = bfs(root, target, k, graph);

        return retVal;
    }
};
```

</details>

<details><summary>Python3</summary>

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def binaryTreeToGraph(self, root: TreeNode, graph: defaultdict[list]):
        if root is None:
            return

        if root.left:
            graph[root.val].append(root.left.val)
            graph[root.left.val].append(root.val)
            self.binaryTreeToGraph(root.left, graph)

        if root.right:
            graph[root.val].append(root.right.val)
            graph[root.right.val].append(root.val)
            self.binaryTreeToGraph(root.right, graph)

    def bfs(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        retVal = []

        graph = defaultdict(list)
        self.binaryTreeToGraph(root, graph)
        graph = dict(graph)
        if not graph:
            return retVal

        bfsQueue = deque()
        bfsQueue.append([target.val, 0])
        visited = [target.val]
        while bfsQueue:
            current, distance = bfsQueue.popleft()
            if distance == k:
                retVal.append(current)

            for neighbor in graph[current]:
                if neighbor in visited:
                    continue
                bfsQueue.append([neighbor, distance+1])
                visited.append(neighbor)

        return retVal

    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        retVal = []

        if root == None:
            return retVal

        retVal = self.bfs(root, target, k)

        return retVal
```

</details>

## [872. Leaf-Similar Trees](https://leetcode.com/problems/leaf-similar-trees/description/)  1287

- [Official](https://leetcode.com/problems/leaf-similar-trees/editorial/)
- [Official](https://leetcode.cn/problems/leaf-similar-trees/solutions/755642/xie-zi-xiang-si-de-shu-by-leetcode-solut-z0w6/)

<details><summary>Description</summary>

```text
Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a leaf value sequence.
      3
   /     \
  5       1
 / \     / \
6   2   9   8
   / \
  7   4
For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

Example 1:
      3               3
   /     \         /     \
  5       1       5       1
 / \     / \     / \     / \
6   2   9   8   6   7   4   2
   / \                     / \
  7   4                   9   8
Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
Output: true

Example 2:
  1       1
 / \     / \
2   3   3   2
Input: root1 = [1,2,3], root2 = [1,3,2]
Output: false

Constraints:
The number of nodes in each tree will be in the range [1, 200].
Both of the given trees will have values in the range [0, 200].
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
void dfs(struct TreeNode* pRoot, int* pArr, int* pArrSize) {
    if (pRoot == NULL) {
        return;
    }

    if ((pRoot->left == NULL) && (pRoot->right == NULL)) {
        pArr[(*pArrSize)] = pRoot->val;
        ++(*pArrSize);
        return;
    }
    dfs(pRoot->left, pArr, pArrSize);
    dfs(pRoot->right, pArr, pArrSize);
}
bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2) {
    bool retVal = false;

    // The number of nodes in each tree will be in the range [1, 200].
    int arr1[200];
    memset(arr1, 0, sizeof(arr1));
    int arr1Size = 0;
    dfs(root1, arr1, &arr1Size);

    // The number of nodes in each tree will be in the range [1, 200].
    int arr2[200];
    memset(arr2, 0, sizeof(arr2));
    int arr2Size = 0;
    dfs(root2, arr2, &arr2Size);

    // compare the number of leafs
    if (arr1Size != arr2Size) {
        return retVal;
    }

    // compare leaf's value
    int i;
    for (i = 0; i < arr1Size; ++i) {
        if (arr1[i] != arr2[i]) {
            return retVal;
        }
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
    void dfs(TreeNode* root, vector<int>& sequence) {
        if (root == nullptr) {
            return;
        }

        if ((root->left == nullptr) && (root->right == nullptr)) {
            sequence.emplace_back(root->val);
            return;
        }
        dfs(root->left, sequence);
        dfs(root->right, sequence);
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        bool retVal = false;

        vector<int> sequence1;
        dfs(root1, sequence1);

        vector<int> sequence2;
        dfs(root2, sequence2);

        if (sequence1 == sequence2) {
            retVal = true;
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
    def dfs(self, root: Optional[TreeNode], sequence: List[int]) -> None:
        if root is None:
            return

        if (root.left is None) and (root.right is None):
            sequence.append(root.val)
            return
        self.dfs(root.left, sequence)
        self.dfs(root.right, sequence)

    def leafSimilar(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        retVal = False

        sequence1 = []
        self.dfs(root1, sequence1)

        sequence2 = []
        self.dfs(root2, sequence2)

        if sequence1 == sequence2:
            retVal = True

        return retVal
```

</details>

## [889. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)  1731

- [Official](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/solutions/3550/gen-ju-qian-xu-he-hou-xu-bian-li-gou-zao-er-cha-sh/)

<details><summary>Description</summary>

```text
Given two integer arrays,
preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values
and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.

If there exist multiple answers, you can return any of them.

Example 1:
     1
   /   \
  2     3
 / \   / \
4   5 6   7
Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Example 2:
Input: preorder = [1], postorder = [1]
Output: [1]

Constraints:
1 <= preorder.length <= 30
1 <= preorder[i] <= preorder.length
All the values of preorder are unique.
postorder.length == preorder.length
1 <= postorder[i] <= postorder.length
All the values of postorder are unique.
It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal of the same binary tree.
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
struct TreeNode* constructFromPrePost(int* preorder, int preorderSize, int* postorder, int postorderSize) {
    struct TreeNode* pRetVal = NULL;

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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {

    }
};
```

</details>

## [894. All Possible Full Binary Trees](https://leetcode.com/problems/all-possible-full-binary-trees/)  1784

- [Official](https://leetcode.com/problems/all-possible-full-binary-trees/editorial/)
- [Official](https://leetcode.cn/problems/all-possible-full-binary-trees/solutions/3558/suo-you-ke-neng-de-man-er-cha-shu-by-leetcode/)

<details><summary>Description</summary>

```text
Given an integer n, return a list of all possible full binary trees with n nodes.
Each node of each tree in the answer must have Node.val == 0.

Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Example 1:
Input: n = 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],
[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

Example 2:
Input: n = 3
Output: [[0,0,0]]

Constraints:
1 <= n <= 20
```

</details>

<details><summary>C</summary>

```c
// https://leetcode.cn/problems/all-possible-full-binary-trees/solutions/320161/c-di-gui-by-cjzswang5/
int calculateReturnSize(int n) {
    int retVal = 0;

    if ((n == 1) || (n == 3)) {
        retVal = 1;
        return retVal;
    }

    int i;
    for (i = 1; i < n; i += 2) {
        retVal += calculateReturnSize(i) * calculateReturnSize(n - i - 1);
    }

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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    struct TreeNode** pRetVal = NULL;

    if ((n % 2) == 0) {
        (*returnSize) = 0;
        return pRetVal;
    }

    if (n == 1) {
        (*returnSize) = 1;

        pRetVal = (struct TreeNode**)calloc(1, sizeof(struct TreeNode*));
        if (pRetVal == NULL) {
            perror("calloc");
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[0] = (struct TreeNode*)calloc(1, sizeof(struct TreeNode));
        if (pRetVal[0] == NULL) {
            perror("calloc");
            (*returnSize) = 0;
            return pRetVal;
        }
        pRetVal[0][0].val = 0;
        pRetVal[0][0].left = NULL;
        pRetVal[0][0].right = NULL;

        return pRetVal;
    }

    (*returnSize) = 0;
    pRetVal = (struct TreeNode**)calloc(calculateReturnSize(n), sizeof(struct TreeNode*));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    struct TreeNode** tmpLeft;
    int tmpLeftSize = 0;
    int tmpLeftSizeIdx = 0;
    struct TreeNode** tmpRight;
    int tmpRightSize = 0;
    int tmpRightSizeIdx = 0;
    int i;
    for (i = 1; i < n; i += 2) {
        tmpLeft = allPossibleFBT(i, &tmpLeftSize);
        tmpRight = allPossibleFBT(n - i - 1, &tmpRightSize);
        for (tmpLeftSizeIdx = 0; tmpLeftSizeIdx < tmpLeftSize; ++tmpLeftSizeIdx) {
            for (tmpRightSizeIdx = 0; tmpRightSizeIdx < tmpRightSize; ++tmpRightSizeIdx) {
                pRetVal[(*returnSize)] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                if (pRetVal[(*returnSize)] == NULL) {
                    perror("calloc");
                    (*returnSize) = 0;
                    return pRetVal;
                }
                pRetVal[(*returnSize)]->val = 0;
                pRetVal[(*returnSize)]->left = tmpLeft[tmpLeftSizeIdx];
                pRetVal[(*returnSize)]->right = tmpRight[tmpRightSizeIdx];
                ++(*returnSize);
            }
        }
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
#define RECURSION (0)
#define ITERATIVE (1)
   public:
    unordered_map<int, vector<TreeNode*>> memo;

    Solution() {
#if (RECURSION)
        cout << "Recursion\n\n";
#elif (ITERATIVE)
        cout << "Iterative\n\n";
#endif
    }
    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> retVal;

        if ((n % 2) == 0) {
            return retVal;
        }

#if (RECURSION)
        if (n == 1) {
            retVal.emplace_back(new TreeNode(0));
            return retVal;
        }

        if (memo.find(n) != memo.end()) {
            retVal = memo[n];
            return retVal;
        }

        for (int i = 1; i < n; i += 2) {
            vector<TreeNode*> left = allPossibleFBT(i);
            vector<TreeNode*> right = allPossibleFBT(n - i - 1);
            for (auto l : left) {
                for (auto r : right) {
                    TreeNode* root = new TreeNode(0, l, r);
                    retVal.emplace_back(root);
                }
            }
        }
        memo[n] = retVal;
#elif (ITERATIVE)
        vector<vector<TreeNode*>> dp(n + 1);

        dp[1].push_back(new TreeNode(0));
        for (int count = 3; count <= n; count += 2) {
            for (int i = 1; i < count - 1; i += 2) {
                int j = count - 1 - i;
                for (auto left : dp[i]) {
                    for (auto right : dp[j]) {
                        TreeNode* root = new TreeNode(0, left, right);
                        dp[count].push_back(root);
                    }
                }
            }
        }

        retVal = dp[n];
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
    def __init__(self) -> None:
        self.method = 1
        if self.method == 1:
            print("Recursion")
        elif self.method == 2:
            print("Iterative")
        print()

    def allPossibleFBT(self, n: int) -> List[Optional[TreeNode]]:
        retVal = []

        if n % 2 == 0:
            return retVal

        if self.method == 1:
            if n == 1:
                return [TreeNode()]

            for i in range(1, n, 2):
                left = self.allPossibleFBT(i)
                right = self.allPossibleFBT(n - i - 1)
                for l in left:
                    for r in right:
                        root = TreeNode(0, l, r)
                        retVal.append(root)
        elif self.method == 2:
            dp = [[] for _ in range(n + 1)]
            dp[1].append(TreeNode(0))
            for count in range(3, n + 1, 2):
                for i in range(1, count - 1, 2):
                    j = count - 1 - i
                    for left in dp[i]:
                        for right in dp[j]:
                            root = TreeNode(0, left, right)
                            dp[count].append(root)
            retVal = dp[n]

        return retVal
```

</details>

## [938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/description/)  1335

- [Official](https://leetcode.cn/problems/range-sum-of-bst/solutions/746069/er-cha-sou-suo-shu-de-fan-wei-he-by-leet-rpq7/)

<details><summary>Description</summary>

```text
Given the root node of a binary search tree and two integers low and high,
return the sum of values of all nodes with a value in the inclusive range [low, high].

Example 1:
    10
   /  \
  5    15
 / \     \
3   7     18
Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

Example 2:
       10
     /    \
    5      15
   / \    /  \
  3   7 13    18
 /   /
1   6
Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.

Constraints:
The number of nodes in the tree is in the range [1, 2 * 10^4].
1 <= Node.val <= 10^5
1 <= low <= high <= 10^5
All Node.val are unique.
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
void inorder(struct TreeNode* root, int low, int high, int* sum) {
    if (root == NULL) {
        return;
    }

    inorder(root->left, low, high, sum);
    if ((root->val >= low) && (root->val <= high)) {
        (*sum) += root->val;
    }
    inorder(root->right, low, high, sum);
}
int rangeSumBST(struct TreeNode* root, int low, int high) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }

    inorder(root, low, high, &retVal);

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
    int sum = 0;

   public:
    void inorder(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return;
        }
        inorder(root->left, low, high);
        if ((low <= root->val) && (root->val <= high)) {
            sum += root->val;
        }
        inorder(root->right, low, high);
    }
    int rangeSumBST(TreeNode* root, int low, int high) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }

        sum = 0;
        inorder(root, low, high);
        retVal = sum;

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
        self.sum = 0

    def inorder(self, root: Optional[TreeNode], low: int, high: int) -> None:
        if root is None:
            return

        self.inorder(root.left, low, high)
        if low <= root.val <= high:
            self.sum += root.val
        self.inorder(root.right, low, high)

    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        self.sum = retVal
        self.inorder(root, low, high)
        retVal = self.sum

        return retVal
```

</details>

## [958. Check Completeness of a Binary Tree](https://leetcode.com/problems/check-completeness-of-a-binary-tree/)  1702

- [Official](https://leetcode.cn/problems/check-completeness-of-a-binary-tree/solutions/18187/er-cha-shu-de-wan-quan-xing-jian-yan-by-leetcode/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, determine if it is a complete binary tree.

In a complete binary tree, every level, except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

Example 1:
     1
   /   \
  2     3
 / \   /
4   5 6
Input: root = [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}),
and all nodes in the last level ({4, 5, 6}) are as far left as possible.

Example 2:
    1
   / \
  2   3
 / \   \
4   5   7
Input: root = [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.

Constraints:
The number of nodes in the tree is in the range [1, 100].
1 <= Node.val <= 1000
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
bool isCompleteTree(struct TreeNode* root) {
    bool retVal = false;

#define MAX_QUEUE_SIZE (100 * 2)  // The number of nodes in the tree is in the range [1, 100].
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_QUEUE_SIZE];
    bfsQueue[bfsQueueTail] = root;
    ++bfsQueueTail;

    struct TreeNode* pCurrent;
    while (bfsQueueHead < bfsQueueTail) {
        pCurrent = bfsQueue[bfsQueueHead];
        ++bfsQueueHead;

        if (pCurrent == NULL) {
            retVal = true;
            continue;
        }

        if (retVal == true) {
            retVal = false;
            break;
        }

        bfsQueue[bfsQueueTail] = pCurrent->left;
        ++bfsQueueTail;
        bfsQueue[bfsQueueTail] = pCurrent->right;
        ++bfsQueueTail;
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
    bool isCompleteTree(TreeNode* root) {
        bool retVal = false;

        queue<TreeNode*> bfsQueue;
        bfsQueue.push(root);
        while (bfsQueue.empty() == false) {
            TreeNode* pCurrent = bfsQueue.front();
            bfsQueue.pop();

            if (pCurrent == nullptr) {
                retVal = true;
                continue;
            }

            if (retVal == true) {
                retVal = false;
                break;
            }

            bfsQueue.push(pCurrent->left);
            bfsQueue.push(pCurrent->right);
        }

        return retVal;
    }
};
```

</details>
