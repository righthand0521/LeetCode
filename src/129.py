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
    def dfs(self, root: Optional[TreeNode], sum: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        retVal = 10 * sum + root.val
        if (root.left is None) and (root.right is None):
            return retVal
        retVal = self.dfs(root.left, retVal) + self.dfs(root.right, retVal)

        return retVal

    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        retVal = self.dfs(root, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3], [4, 9, 0, 5, 1]]:
            # /* Example
            #  *  Input: root = [1,2,3]
            #  *  Output: 25
            #  *
            #  *  Input: root = [4,9,0,5,1]
            #  *  Output: 1026
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.sumNumbers(TreeNode().buildTree(root))
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
