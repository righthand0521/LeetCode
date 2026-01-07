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

## [1028. Recover a Tree From Preorder Traversal](https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/)  1797

- [Official](https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/editorial/)
- [Official](https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/solutions/292136/cong-xian-xu-bian-li-huan-yuan-er-cha-shu-by-leetc/)

<details><summary>Description</summary>

```text
We run a preorder depth-first search (DFS) on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node),
then we output the value of this node.
If the depth of a node is D, the depth of its immediate child is D + 1.
The depth of the root node is 0.

If a node has only one child, that child is guaranteed to be the left child.

Given the output traversal of this traversal, recover the tree and return its root.

Example 1:
    1
   / \
  2   3
 /\   /\
4  5 6  7
Input: traversal = "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

Example 2:
      1
     / \
    2   5
   /   /
  3   6
 /   /
4   7
Input: traversal = "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]

Example 3:
          1
         /
      401
      / \
   349   88
  /
90
Input: traversal = "1-401--349---90--88"
Output: [1,401,null,349,88,90]

Constraints:
The number of nodes in the original tree is in the range [1, 1000].
1 <= Node.val <= 10^9
```

<details><summary>Hint</summary>

```text
1. Do an iterative depth first search, parsing dashes from the string to inform you how to link the nodes together.
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
struct TreeNode* recoverFromPreorder(char* traversal) {
    struct TreeNode* pRetVal = NULL;

    int traversalSize = strlen(traversal);

    struct TreeNode* stack[traversalSize + 1];
    int stackTop = -1;

    struct TreeNode* node;
    int depth, value;
    int index = 0;
    while (index < traversalSize) {
        // Count the number of dashes
        depth = 0;
        while ((index < traversalSize) && (traversal[index] == '-')) {
            depth++;
            index++;
        }

        // Extract the node value
        value = 0;
        while ((index < traversalSize) && (isdigit(traversal[index]))) {
            value = value * 10 + (traversal[index] - '0');
            index++;
        }

        // Create the current node
        node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        if (node == NULL) {
            perror("malloc");
            return pRetVal;
        }
        node->val = value;
        node->left = NULL;
        node->right = NULL;

        // Adjust the stack to the correct depth
        while ((stackTop + 1) > depth) {
            stack[stackTop--] = NULL;
        }

        // Attach the node to the parent
        if (stackTop > -1) {
            if (stack[stackTop]->left == NULL) {
                stack[stackTop]->left = node;
            } else {
                stack[stackTop]->right = node;
            }
        }

        // Push the current node onto the stack
        stack[++stackTop] = node;
    }

    // The root is the first node in the stack
    pRetVal = stack[0];

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
    TreeNode* recoverFromPreorder(string traversal) {
        TreeNode* pRetVal = nullptr;

        int traversalSize = traversal.size();
        stack<TreeNode*> stack;
        int index = 0;
        while (index < traversalSize) {
            // Count the number of dashes
            int depth = 0;
            while ((index < traversalSize) && (traversal[index] == '-')) {
                depth++;
                index++;
            }

            // Extract the node value
            int value = 0;
            while ((index < traversalSize) && (isdigit(traversal[index]))) {
                value = value * 10 + (traversal[index] - '0');
                index++;
            }

            // Create the current node
            TreeNode* node = new TreeNode(value);

            // Adjust the stack to the correct depth
            int stackSize = stack.size();
            while (stackSize > depth) {
                stack.pop();
                stackSize = stack.size();
            }

            // Attach the node to the parent
            if (stack.empty() == false) {
                if (stack.top()->left == nullptr) {
                    stack.top()->left = node;
                } else {
                    stack.top()->right = node;
                }
            }

            // Push the current node onto the stack
            stack.push(node);
        }

        // The root is the first node in the stack
        while (stack.size() > 1) {
            stack.pop();
        }
        pRetVal = stack.top();

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
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        retVal = None

        traversalSize = len(traversal)
        stack = []
        index = 0
        while index < traversalSize:
            # Count the number of dashes
            depth = 0
            while (index < traversalSize) and (traversal[index] == "-"):
                depth += 1
                index += 1

            # Extract the node value
            value = 0
            while (index < traversalSize) and (traversal[index].isdigit()):
                value = value * 10 + int(traversal[index])
                index += 1

            # Create the current node
            node = TreeNode(value)

            # Adjust the stack to the correct depth
            while len(stack) > depth:
                stack.pop()

            # Attach the node to the parent
            if stack:
                if stack[-1].left is None:
                    stack[-1].left = node
                else:
                    stack[-1].right = node

            # Push the current node onto the stack
            stack.append(node)

        retVal = stack[0]

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

## [1123. Lowest Common Ancestor of Deepest Leaves](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/)  1607

- [Official](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/editorial/)
- [Official](https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/solutions/2421007/zui-shen-xie-jie-dian-de-zui-jin-gong-go-cjzv/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:
- The node of a binary tree is a leaf if and only if it has no children
- The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its children is d + 1.
- The lowest common ancestor of a set S of nodes,
  is the node A with the largest depth such that every node in S is in the subtree with root A.

Example 1:
      3
   /     \
  5       1
 / \     / \
6   2   0   8
   / \
  7   4
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest leaf-nodes of the tree.
Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.

Example 2:
Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree, and it's the lca of itself.

Example 3:
   0
  / \
 1   3
  \
   2
Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.

Constraints:
The number of nodes in the tree will be in the range [1, 1000].
0 <= Node.val <= 1000
The values of the nodes in the tree are unique.

Note: This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
```

<details><summary>Hint</summary>

```text
1. Do a postorder traversal.
2. Then, if both subtrees contain a deepest leaf, you can mark this node as the answer (so far).
3. The final node marked will be the correct answer.
```

</details>

</details>

<details><summary>C</summary>

```c
struct Pair {
    struct TreeNode* node;
    int depth;
};
struct Pair dfs(struct TreeNode* root) {
    struct Pair pRetVal = {NULL, 0};

    if (root == NULL) {
        return pRetVal;
    }

    struct Pair left = dfs(root->left);
    struct Pair right = dfs(root->right);
    if (left.depth > right.depth) {
        pRetVal = (struct Pair){left.node, left.depth + 1};
    } else if (left.depth < right.depth) {
        pRetVal = (struct Pair){right.node, right.depth + 1};
    } else {
        pRetVal = (struct Pair){root, left.depth + 1};
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
struct TreeNode* lcaDeepestLeaves(struct TreeNode* root) {
    struct TreeNode* pRetVal = NULL;

    pRetVal = dfs(root).node;

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
    pair<TreeNode*, int> dfs(TreeNode* root) {
        pair<TreeNode*, int> retVal = {nullptr, 0};

        if (root == nullptr) {
            return retVal;
        }

        pair<TreeNode*, int> left = dfs(root->left);
        pair<TreeNode*, int> right = dfs(root->right);
        if (left.second > right.second) {
            retVal = {left.first, left.second + 1};
        } else if (left.second < right.second) {
            retVal = {right.first, right.second + 1};
        } else {
            retVal = {root, left.second + 1};
        }

        return retVal;
    }

   public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        TreeNode* pRetVal = nullptr;

        pRetVal = dfs(root).first;

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
    def dfs(self, root) -> tuple[int, Optional[TreeNode]]:
        retVal = [0, None]

        if not root:
            return retVal

        left = self.dfs(root.left)
        right = self.dfs(root.right)
        if left[0] > right[0]:
            retVal = [left[0] + 1, left[1]]
        elif left[0] < right[0]:
            retVal = [right[0] + 1, right[1]]
        else:
            retVal = [left[0] + 1, root]

        return retVal

    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = None

        retVal = self.dfs(root)[1]

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

## [1261. Find Elements in a Contaminated Binary Tree](https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/)  1439

- [Official](https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/editorial/)
- [Official](https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/solutions/2674238/zai-shou-wu-ran-de-er-cha-shu-zhong-cha-5l56x/)

<details><summary>Description</summary>

```text
Given a binary tree with the following rules:
1. root.val == 0
2. For any treeNode:
   1. If treeNode.val has a value x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
   2. If treeNode.val has a value x and treeNode.right != null, then treeNode.right.val == 2 * x + 2

Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.

Implement the FindElements class:
- FindElements(TreeNode* root)
  Initializes the object with a contaminated binary tree and recovers it.
- bool find(int target)
  Returns true if the target value exists in the recovered binary tree.

Example 1:
Input
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
Output
[null,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1]);
findElements.find(1); // return False
findElements.find(2); // return True

Example 2:
Input
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
Output
[null,true,true,false]
Explanation
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False

Example 3:
Input
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
Output
[null,true,false,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True

Constraints:
TreeNode.val == -1
The height of the binary tree is less than or equal to 20
The total number of nodes is between [1, 10^4]
Total calls of find() is between [1, 10^4]
0 <= target <= 10^6
```

<details><summary>Hint</summary>

```text
1. Use DFS to traverse the binary tree and recover it.
2. Use a hashset to store TreeNode.val for finding.
```

</details>

</details>

<details><summary>C</summary>

```c
struct hashTable {
    int key;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
void dfs(struct TreeNode* currentNode, int currentValue, struct hashTable** seen) {
    if (currentNode == NULL) {
        return;
    }

    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(*seen, &currentValue, pTemp);
    if (pTemp == NULL) {
        pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTemp == NULL) {
            perror("malloc");
            return;
        }
        pTemp->key = currentValue;
        HASH_ADD_INT(*seen, key, pTemp);
    }
    dfs(currentNode->left, currentValue * 2 + 1, seen);
    dfs(currentNode->right, currentValue * 2 + 2, seen);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct {
    struct hashTable* seen;
} FindElements;
FindElements* findElementsCreate(struct TreeNode* root) {
    FindElements* pRetVal = NULL;

    pRetVal = (FindElements*)malloc(sizeof(FindElements));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->seen = NULL;
    dfs(root, 0, &pRetVal->seen);

    return pRetVal;
}
bool findElementsFind(FindElements* obj, int target) {
    bool retVal = false;

    struct hashTable* pTemp = NULL;
    HASH_FIND_INT(obj->seen, &target, pTemp);
    if (pTemp != NULL) {
        retVal = true;
    }

    return retVal;
}
void findElementsFree(FindElements* obj) {
    freeAll(obj->seen);
    free(obj);
}
/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);
 * findElementsFree(obj);
 */
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
class FindElements {
   private:
    unordered_set<int> seen;
    void dfs(TreeNode* currentNode, int currentValue) {
        if (currentNode == nullptr) {
            return;
        }

        // visit current node by adding its value to seen
        seen.insert(currentValue);
        dfs(currentNode->left, currentValue * 2 + 1);
        dfs(currentNode->right, currentValue * 2 + 2);
    }

   public:
    FindElements(TreeNode* root) {
        //
        dfs(root, 0);
    }
    bool find(int target) {
        bool retVal = (seen.count(target) > 0);

        return retVal;
    }
};
/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
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
class FindElements:
    def __init__(self, root: Optional[TreeNode]):
        self.seen = set()
        self.dfs(root, 0)

    def dfs(self, currentNode, currentValue):
        if currentNode is None:
            return

        # visit current node by adding its value to seen
        self.seen.add(currentValue)
        self.dfs(currentNode.left, currentValue * 2 + 1)
        self.dfs(currentNode.right, currentValue * 2 + 2)

    def find(self, target: int) -> bool:
        retVal = target in self.seen

        return retVal

# Your FindElements object will be instantiated and called as such:
# obj = FindElements(root)
# param_1 = obj.find(target)
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

- [Official](https://leetcode.cn/problems/maximum-product-of-splitted-binary-tree/solutions/130598/fen-lie-er-cha-shu-de-zui-da-cheng-ji-by-leetcode/)

<details><summary>Description</summary>

```text
Given the root of a binary tree, split the binary tree into two subtrees by removing one edge
such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 10^9 + 7.

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
The number of nodes in the tree is in the range [2, 5 * 10^4].
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
int postOrder(struct TreeNode* root, int* pSubTreeSum, int* returnSubTreeSumCount) {
    int retVal = 0;

    if (root == NULL) {
        return retVal;
    }
    retVal = postOrder(root->left, pSubTreeSum, returnSubTreeSumCount) +
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
    long long maxValue = 0;
    for (int i = 0; i < subTreeSumCount; ++i) {
        maxValue = fmax(maxValue, ((long long)subTreeSum[i] * (long long)(treeSum - subTreeSum[i])));
    }
    retVal = maxValue % MODULO;

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
    static constexpr int MODULO = 1e9 + 7;

    int postOrder(TreeNode* root, vector<int>& subTreeSum) {
        int retVal = 0;

        if (root == nullptr) {
            return retVal;
        }
        retVal = postOrder(root->left, subTreeSum) + postOrder(root->right, subTreeSum) + root->val;
        subTreeSum.emplace_back(retVal);

        return retVal;
    }

   public:
    int maxProduct(TreeNode* root) {
        int retVal = 0;

        vector<int> subTreeSum;
        int treeSum = postOrder(root, subTreeSum);
        int subTreeSumSize = subTreeSum.size();

        long long maxValue = 0;
        for (int i = 0; i < subTreeSumSize; ++i) {
            maxValue = max(maxValue, ((long long)subTreeSum[i] * (long long)(treeSum - subTreeSum[i])));
        }
        retVal = maxValue % MODULO;

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
        self.MODULO = 10 ** 9 + 7

    def postOrder(self, root: Optional[TreeNode], subTreeSum: List[int]) -> int:
        retVal = 0

        if root is None:
            return retVal
        retVal = self.postOrder(root.left, subTreeSum) + self.postOrder(root.right, subTreeSum) + root.val
        subTreeSum.append(retVal)

        return retVal

    def maxProduct(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        subTreeSum = []
        treeSum = self.postOrder(root, subTreeSum)
        subTreeSumSize = len(subTreeSum)

        maxValue = 0
        for i in range(subTreeSumSize):
            maxValue = max(maxValue, (subTreeSum[i] * (treeSum - subTreeSum[i])))
        retVal = maxValue % self.MODULO

        return retVal
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
