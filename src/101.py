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


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 2, 3, 4, 4, 3], [1, 2, 2, None, 3, None, 3]]:
            # /* Example
            #  *  Input: root = [1,2,2,3,4,4,3]
            #  *  Output: true
            #  *
            #  *  Input: root = [1,2,2,null,3,null,3]
            #  *  Output: false
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.isSymmetric(root)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
