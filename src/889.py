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
    def __init__(self):
        self.preIndex = 0
        self.postIndex = 0

    def constructTree(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        # Create a new node with the value at the current preorder index
        root = TreeNode(preorder[self.preIndex])
        # Mark this node as created
        self.preIndex += 1
        # Recursively construct the left subtree if the root is not the last of its subtree
        if root.val != postorder[self.postIndex]:
            root.left = self.constructTree(preorder, postorder)
        # Recursively construct the right subtree if the root is not the last of its subtree
        if root.val != postorder[self.postIndex]:
            root.right = self.constructTree(preorder, postorder)
        # Mark this node and its subtree as fully processed
        self.postIndex += 1

        return root

    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        retVal = None

        self.preIndex = 0
        self.postIndex = 0
        retVal = self.constructTree(preorder, postorder)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for preorder, postorder in zip([[1, 2, 4, 5, 3, 6, 7], [1]], [[4, 5, 2, 6, 7, 3, 1], [1]]):
            # /* Example
            #  *  Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
            #  *  Output: [1,2,3,4,5,6,7]
            #  *
            #  *  Input: preorder = [1], postorder = [1]
            #  *  Output: [1]
            #  */
            logging.info("Input: preorder = %s, postorder = %s", preorder, postorder)

            retVal = pSolution.constructFromPrePost(preorder, postorder)
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
