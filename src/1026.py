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
    def dfs(self, root: Optional[TreeNode], maxAncestor: int, minAncestor: int) -> int:
        retVal = maxAncestor - minAncestor

        if root is None:
            return retVal

        maxAncestor = max(root.val, maxAncestor)
        minAncestor = min(root.val, minAncestor)
        left = self.dfs(root.left, maxAncestor, minAncestor)
        right = self.dfs(root.right, maxAncestor, minAncestor)
        retVal = max(left, right)

        return retVal

    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root is None:
            return retVal
        retVal = self.dfs(root, root.val, root.val)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[8, 3, 10, 1, 6, None, 14, None, None, 4, 7, 13], [1, None, 2, None, 0, 3]]:
            # /* Example
            #  *  Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
            #  *  Output: 7
            #  *
            #  *  Input: root = [1,null,2,null,0,3]
            #  *  Output: 3
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.maxAncestorDiff(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
