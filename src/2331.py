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
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def evaluateTree(self, root: Optional[TreeNode]) -> bool:
        retVal = False

        if (root.left is None) and (root.right is None):
            if root.val == 0:
                retVal = False
            elif root.val == 1:
                retVal = True
            return retVal

        if root.val == 2:
            retVal = self.evaluateTree(root.left) or self.evaluateTree(root.right)
        elif root.val == 3:
            retVal = self.evaluateTree(root.left) and self.evaluateTree(root.right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[2, 1, 3, None, None, 0, 1], [0]]:
            # /* Example
            #  *  Input: root = [2,1,3,null,null,0,1]
            #  *  Output: true
            #  *
            #  *  Input: root = [0]
            #  *  Output: false
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.evaluateTree(TreeNode().buildTree(root))
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
