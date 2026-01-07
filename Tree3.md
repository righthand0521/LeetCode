# Tree

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

## [2471. Minimum Number of Operations to Sort a Binary Tree by Level](https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/)  1635

- [Official](https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/editorial/)

<details><summary>Description</summary>

```text
You are given the root of a binary tree with unique values.

In one operation, you can choose any two nodes at the same level and swap their values.

Return the minimum number of operations needed to make the values at each level sorted in a strictly increasing order.

The level of a node is the number of edges along the path between it and the root node.

Example 1:
      1
   /     \
  4       3
 / \     / \
7   6   8   5
       /   /
      9  10
Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
Output: 3
Explanation:
- Swap 4 and 3. The 2nd level becomes [3,4].
- Swap 7 and 5. The 3rd level becomes [5,6,8,7].
- Swap 8 and 7. The 3rd level becomes [5,6,7,8].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.

Example 2:
     1
   /   \
  2     3
 / \   / \
7   6 5   4
Input: root = [1,3,2,7,6,5,4]
Output: 3
Explanation:
- Swap 3 and 2. The 2nd level becomes [2,3].
- Swap 7 and 4. The 3rd level becomes [4,6,5,7].
- Swap 6 and 5. The 3rd level becomes [4,5,6,7].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.

Example 3:
     1
   /   \
  2     3
 / \   /
4   5 6
Input: root = [1,2,3,4,5,6]
Output: 0
Explanation: Each level is already sorted in increasing order so return 0.

Constraints:
The number of nodes in the tree is in the range [1, 10^5].
1 <= Node.val <= 10^5
All the values of the tree are unique.
```

<details><summary>Hint</summary>

```text
1. We can group the values level by level and solve each group independently.
2. Do BFS to group the value level by level.
3. Find the minimum number of swaps to sort the array of each level.
4. While iterating over the array, check the current element, and if not in the correct index,
   replace that element with the index of the element which should have come.
```

</details>

</details>

<details><summary>C</summary>

```c
int compareLongLong(const void* n1, const void* n2) {
    // ascending order
    return (*(long long*)n1 > *(long long*)n2);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minimumOperations(struct TreeNode* root) {
    int retVal = 0;

    const int MAX_NODE_SIZE = (1e5);  // The number of nodes in the tree is in the range [1, 10^5].
    const int SHIFT = 20;
    const int MASK = 0xFFFFF;

    // Process tree level by level using BFS
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    struct TreeNode* bfsQueue[MAX_NODE_SIZE];
    bfsQueue[bfsQueueTail++] = root;

    int tmp;
    int origPos;
    struct TreeNode* pTmp;
    long long* pNodes = NULL;
    int levelSize;
    while (bfsQueueTail > bfsQueueHead) {
        levelSize = bfsQueueTail - bfsQueueHead;
        pNodes = (long long*)calloc(levelSize, sizeof(long long));
        if (pNodes == NULL) {
            perror("calloc");
            return retVal;
        }

        // Store node values with encoded positions
        for (int i = 0; i < levelSize; i++) {
            pTmp = bfsQueue[bfsQueueHead++];

            // Encode value and index: high 20 bits = value, low 20 bits = index
            pNodes[i] = ((long long)(pTmp->val) << SHIFT) + i;

            if (pTmp->left != NULL) {
                bfsQueue[bfsQueueTail++] = pTmp->left;
            }
            if (pTmp->right != NULL) {
                bfsQueue[bfsQueueTail++] = pTmp->right;
            }
        }

        // Sort nodes by their values (high 20 bits)
        qsort(pNodes, levelSize, sizeof(long long), compareLongLong);

        // Count swaps needed to match indices with original positions
        for (int i = 0; i < levelSize; i++) {
            origPos = (int)(pNodes[i] & MASK);
            if (origPos != i) {
                // Swap nodes and decrement i to recheck current position
                tmp = pNodes[i];
                pNodes[i] = pNodes[origPos];
                pNodes[origPos] = tmp;

                retVal++;
                i--;
            }
        }

        //
        free(pNodes);
        pNodes = NULL;
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
   private:
    const int SHIFT = 20;
    const int MASK = 0xFFFFF;

   public:
    int minimumOperations(TreeNode* root) {
        int retVal = 0;

        // Process tree level by level using BFS
        queue<TreeNode*> queue;
        queue.push(root);
        while (queue.empty() == false) {
            int levelSize = queue.size();
            vector<long long> nodes(levelSize);

            // Store node values with encoded positions
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = queue.front();
                queue.pop();
                // Encode value and index: high 20 bits = value, low 20 bits = index
                nodes[i] = (static_cast<long long>(node->val) << SHIFT) + i;

                if (node->left != nullptr) {
                    queue.push(node->left);
                }
                if (node->right != nullptr) {
                    queue.push(node->right);
                }
            }

            // Sort nodes by their values (high 20 bits)
            sort(nodes.begin(), nodes.end());

            // Count swaps needed to match indices with original positions
            for (int i = 0; i < levelSize; i++) {
                int origPos = static_cast<int>(nodes[i] & MASK);
                if (origPos != i) {
                    // Swap nodes and decrement i to recheck current position
                    swap(nodes[i], nodes[origPos]);
                    retVal++;
                    i--;
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
    def __init__(self) -> None:
        self.shift = 20
        self.mask = 0xFFFFF

    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        # Process tree level by level using BFS
        queue = deque([root])
        while queue:
            level_size = len(queue)
            nodes = []

            # Store node values with encoded positions
            for i in range(level_size):
                node = queue.popleft()
                # Encode value and index: high 20 bits = value, low 20 bits = index
                nodes.append((node.val << self.shift) + i)

                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            # Sort nodes by their values (high 20 bits)
            nodes.sort()

            # Count swaps needed to match indices with original positions
            i = 0
            while i < level_size:
                origPos = nodes[i] & self.mask
                if origPos != i:
                    # Swap nodes and decrement i to recheck current position
                    nodes[i], nodes[origPos] = nodes[origPos], nodes[i]
                    retVal += 1
                    i -= 1
                i += 1

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
