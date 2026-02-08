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
    def height(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        retVal = -1

        leftHeight = self.height(root.left)
        if leftHeight == -1:
            return retVal

        rightHeight = self.height(root.right)
        if rightHeight == -1:
            return retVal

        if abs(leftHeight - rightHeight) > 1:
            return retVal

        retVal = max(leftHeight, rightHeight) + 1

        return retVal

    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        retVal = True

        if root == None:
            return retVal

        retVal = (self.height(root) != -1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 9, 20, None, None, 15, 7], [1, 2, 2, 3, 3, None, None, 4, 4], []]:
            # /* Example
            #  *  Input: root = [3,9,20,null,null,15,7]
            #  *  Output: true
            #  *
            #  *  Input: root = [1,2,2,3,3,null,null,4,4]
            #  *  Output: false
            #  *
            #  *  Input: root = []
            #  *  Output: true
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.isBalanced(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
