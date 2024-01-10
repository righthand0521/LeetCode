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
    def dfs(self, root: TreeNode, maxValue: int) -> int:
        retVal = 0

        if root is None:
            return retVal

        if root.val >= maxValue:
            retVal += 1
            maxValue = root.val

        left = self.dfs(root.left, maxValue)
        right = self.dfs(root.right, maxValue)
        retVal += (left + right)

        return retVal

    def goodNodes(self, root: TreeNode) -> int:
        retVal = 0

        maxValue = float('-inf')  # Each node's value is between [-10^4, 10^4].
        retVal += self.dfs(root, maxValue)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 1, 4, 3, None, None, 1, 5], [3, 3, None, 4, 2], [1]]:
            # /* Example
            #  *  Input: root = [3,1,4,3,null,1,5]
            #  *  Output: 4
            #  *
            #  *  Input: root = [3,3,null,4,2]
            #  *  Output: 3
            #  *
            #  *  Input: root = [1]
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.goodNodes(TreeNode().buildTree(root))
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
