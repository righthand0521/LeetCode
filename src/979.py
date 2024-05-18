import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

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
        self.moves = 0

    def dfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        left_coins = self.dfs(root.left)
        right_coins = self.dfs(root.right)
        self.moves += (abs(left_coins) + abs(right_coins))
        retVal = (root.val - 1) + left_coins + right_coins

        return retVal

    def distributeCoins(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        self.moves = 0
        self.dfs(root)
        retVal = self.moves

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 0, 0], [0, 3, 0]]:
            # /* Example
            #  *  Input: root = [3,0,0]
            #  *  Output: 2
            #  *
            #  *  Input: root = [0,3,0]
            #  *  Output: 3
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.distributeCoins(TreeNode().buildTree(root))
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
