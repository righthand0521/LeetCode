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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, low, high in zip([[10, 5, 15, 3, 7, None, 18], [10, 5, 15, 3, 7, 13, 18, 1, None, 6]],
                                   [7, 6],
                                   [15, 10]):
            # /* Example
            #  *  Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
            #  *  Output: 32
            #  *
            #  *  Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
            #  *  Output: 23
            #  */
            logging.info("Input: root = %s, low = %s, high = %s",
                         root, low, high)

            root = TreeNode().buildTree(root)

            retVal = pSolution.rangeSumBST(root, low, high)
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
