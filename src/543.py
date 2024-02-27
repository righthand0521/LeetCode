import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3, 4, 5], [1, 2]]:
            # /* Example
            #  *  Input: root = [1,2,3,4,5]
            #  *  Output: 3
            #  *
            #  *  Input: root = [1,2]
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.diameterOfBinaryTree(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
