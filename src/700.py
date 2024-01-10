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
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        retVal = None

        if (root == None):
            return retVal

        if root.val == val:
            retVal = root
        elif root.val > val:
            retVal = self.searchBST(root.left, val)
        elif root.val < val:
            retVal = self.searchBST(root.right, val)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, val in zip([[4, 2, 7, 1, 3], [4, 2, 7, 1, 3]], [2, 5]):
            # /* Example
            #  *  Input: root = [4,2,7,1,3], val = 2
            #  *  Output: [2,1,3]
            #  *
            #  *  Input: root = [4,2,7,1,3], val = 5
            #  *  Output: []
            #  */
            logging.info("Input: root = %s, val = %s", root, val)

            root = TreeNode().buildTree(root)
            retVal = pSolution.searchBST(root, val)
            retVal = TreeNode().printLevelOrder(retVal)
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
