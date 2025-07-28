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
    def preorder(self, root: Optional[TreeNode], isLeft: bool) -> int:
        retVal = 0

        if root == None:
            return retVal

        if (root.left is None) and (root.right is None) and (isLeft is True):
            retVal += root.val
        retVal += self.preorder(root.left, True)
        retVal += self.preorder(root.right, False)

        return retVal

    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root is None:
            return retVal
        retVal = self.preorder(root, False)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 9, 20, None, None, 15, 7], [1]]:
            # /* Example
            #  *  Input: root = [3,9,20,null,null,15,7]
            #  *  Output: 24
            #  *
            #  *  Input: root = [1]
            #  *  Output: 0
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.sumOfLeftLeaves(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
