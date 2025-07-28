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
    def dfs(self, root: Optional[TreeNode], targetSum: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        if root.val == targetSum:
            retVal += 1
        retVal += self.dfs(root.left, targetSum - root.val)
        retVal += self.dfs(root.right, targetSum - root.val)

        return retVal

    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        retVal = self.dfs(root, targetSum)
        retVal += self.pathSum(root.left, targetSum)
        retVal += self.pathSum(root.right, targetSum)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, targetSum in zip([[10, 5, -3, 3, 2, None, 11, 3, -2, None, 1],
                                    [5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1]],
                                   [8, 22]):
            # /* Example
            #  *  Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
            #  *  Output: 3
            #  *
            #  *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
            #  *  Output: 3
            #  */
            logging.info("Input: root = %s, targetSum = %s", root, targetSum)

            retVal = pSolution.pathSum(TreeNode().buildTree(root), targetSum)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
