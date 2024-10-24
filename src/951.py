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
    def flipEquiv(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        retVal = False

        if (not root1) and (not root2):  # Both trees are empty
            retVal = True
            return retVal
        elif (not root1) or (not root2):  # Just one of the trees is empty
            return retVal
        elif root1.val != root2.val:  # Corresponding values differ
            return retVal

        # Check if corresponding subtrees are flip equivalent
        noSwap = self.flipEquiv(root1.left, root2.left)
        noSwap &= self.flipEquiv(root1.right, root2.right)

        # Check if opposite subtrees are flip equivalent
        swap = self.flipEquiv(root1.left, root2.right)
        swap &= self.flipEquiv(root1.right, root2.left)

        retVal = noSwap or swap

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root1, root2 in zip([[1, 2, 3, 4, 5, 6, None, None, None, 7, 8], [], []],
                                [[1, 3, 2, None, 6, 4, 5, None, None, None, None, 8, 7], [], [1]]):
            # /* Example
            #  *  Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
            #  *  Output: true
            #  *
            #  *  Input: root1 = [], root2 = []
            #  *  Output: true
            #  *
            #  *  Input: root1 = [], root2 = [1]
            #  *  Output: false
            #  */
            logging.info("Input: root1 = %s, root2 = %s", root1, root2)

            pRoot1 = TreeNode().buildTree(root1)
            pRoot2 = TreeNode().buildTree(root2)
            retVal = pSolution.flipEquiv(pRoot1, pRoot2)
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
