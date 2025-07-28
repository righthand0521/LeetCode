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
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        retVal = False

        if (p is None) and (q is None):
            retVal = True
            return retVal
        elif (p is None) and (q is not None):
            return retVal
        elif (p is not None) and (q is None):
            return retVal

        if self.isSameTree(p.left, q.left) == False:
            return retVal
        if p.val != q.val:
            return retVal
        if self.isSameTree(p.right, q.right) == False:
            return retVal
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for p, q in zip([[1, 2, 3], [1, 2], [1, 2, 1]], [[1, 2, 3], [1, None, 2], [1, 1, 2]]):
            # /* Example
            #  *  Input: p = [1,2,3], q = [1,2,3]
            #  *  Output: true
            #  *
            #  *  Input: p = [1,2], q = [1,null,2]
            #  *  Output: false
            #  *
            #  *  Input: p = [1,2,1], q = [1,1,2]
            #  *  Output: false
            #  */
            logging.info("Input: p = %s, q = %s", p, q)

            pRoot = TreeNode().buildTree(p)
            qpRoot = TreeNode().buildTree(q)
            retVal = pSolution.isSameTree(pRoot, qpRoot)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
