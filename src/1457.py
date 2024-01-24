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
    def __init__(self):
        self.count = 0

    def preorder(self, root: Optional[TreeNode], mask: int) -> None:
        if root == None:
            return

        mask = mask ^ (1 << root.val)   # 1 <= Node.val <= 9
        if (root.left == None) and (root.right == None):
            if (mask & (mask - 1)) == 0:
                self.count += 1
            return
        self.preorder(root.left, mask)
        self.preorder(root.right, mask)

    def pseudoPalindromicPaths(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        self.count = 0
        self.preorder(root, 0)
        retVal = self.count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[2, 3, 1, 3, 1, None, 1], [2, 1, 1, 1, 3, None, None, None, None, None, 1], [9]]:
            # /* Example
            #  *  Input: root = [2,3,1,3,1,null,1]
            #  *  Output: 2
            #  *
            #  *  Input: root = [2,1,1,1,3,null,null,null,null,null,1]
            #  *  Output: 1
            #  *
            #  *  Input: root = [9]
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.pseudoPalindromicPaths(
                TreeNode().buildTree(root))
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
