import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

from tree import TreeNode


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, None, 2, None, 3, None, 4, None, None], [2, 1, 3]]:
            # /* Example
            #  *  Input: root = [1,null,2,null,3,null,4,null,null]
            #  *  Output: [2,1,3,null,null,null,4]
            #  *
            #  *  Input: root = [2,1,3]
            #  *  Output: [2,1,3]
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.balanceBST(root)
            retVal = TreeNode().printLevelOrder(retVal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
