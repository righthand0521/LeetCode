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
        self.minVal = 0

    def inOrder(self, root: Optional[TreeNode]) -> bool:
        retVal = True

        if root is None:
            return retVal

        left = self.inOrder(root.left)
        if root.val <= self.minVal:
            retVal = False
            return retVal
        self.minVal = root.val
        right = self.inOrder(root.right)

        retVal = left and right

        return retVal

    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        self.minVal = float('-inf')
        retVal = self.inOrder(root)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[2, 1, 3], [5, 1, 4, None, None, 3, 6], [1, 1]]:
            # /* Example
            #  *  Input: root = [2,1,3]
            #  *  Output: true
            #  *
            #  *  Input: root = [5,1,4,null,null,3,6]
            #  *  Output: false
            #  *
            #  *  Input: root = [1,1]
            #  *  Output: false
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.isValidBST(root)
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
