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
    def __init__(self) -> None:
        self.retVal = 0
        self.k = 0

    def inorder(self, root: Optional[TreeNode]) -> None:
        if root is None:
            return

        self.inorder(root.left)
        self.k -= 1
        if self.k == 0:
            self.retVal = root.val
        self.inorder(root.right)

    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        retVal = 0

        self.retVal = 0
        self.k = k
        self.inorder(root)
        retVal = self.retVal

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, k in zip([[3, 1, 4, None, 2], [5, 3, 6, 2, 4, None, None, 1]], [1, 3]):
            # /* Example
            #  *  Input: root = [3,1,4,null,2], k = 1
            #  *  Output: 1
            #  *
            #  *  Input: root = [5,3,6,2,4,null,null,1], k = 3
            #  *  Output: 3
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.kthSmallest(TreeNode().buildTree(root), k)
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
