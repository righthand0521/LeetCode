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
    def dfs(self, root) -> tuple[int, Optional[TreeNode]]:
        retVal = [0, None]

        if not root:
            return retVal

        left = self.dfs(root.left)
        right = self.dfs(root.right)
        if left[0] > right[0]:
            retVal = [left[0] + 1, left[1]]
        elif left[0] < right[0]:
            retVal = [right[0] + 1, right[1]]
        else:
            retVal = [left[0] + 1, root]

        return retVal

    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = None

        retVal = self.dfs(root)[1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 5, 1, 6, 2, 0, 8, None, None, 7, 4], [1], [0, 1, 3, None, 2]]:
            # /* Example
            #  *  Input: root = [3,5,1,6,2,0,8,null,null,7,4]
            #  *  Output: [2,7,4]
            #  *
            #  *  Input: root = [1]
            #  *  Output: [1]
            #  *
            #  *  Input: root = [0,1,3,null,2]
            #  *  Output: [2]
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.subtreeWithAllDeepest(root)
            retVal = TreeNode().printLevelOrder(retVal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
