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
        self.prevNode = None
        self.minDistance = float('inf')

    def inorderTraversal(self, root: Optional[TreeNode]):
        if root == None:
            return

        self.inorderTraversal(root.left)
        if self.prevNode != None:
            self.minDistance = min(self.minDistance, root.val - self.prevNode)
        self.prevNode = root.val
        self.inorderTraversal(root.right)

    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        self.inorderTraversal(root)
        retVal = self.minDistance

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[4, 2, 6, 1, 3], [1, 0, 48, None, None, 12, 49]]:
            # /* Example
            #  *  Input: root = [4,2,6,1,3]
            #  *  Output: 1
            #  *
            #  *  Input: root = [1,0,48,null,null,12,49]
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s", root)

            # retVal = pSolution.getMinimumDifference(TreeNode().buildTree(root))
            # logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
