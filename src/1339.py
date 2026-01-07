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
        self.MODULO = 10 ** 9 + 7

    def postOrder(self, root: Optional[TreeNode], subTreeSum: List[int]) -> int:
        retVal = 0

        if root is None:
            return retVal
        retVal = self.postOrder(root.left, subTreeSum) + self.postOrder(root.right, subTreeSum) + root.val
        subTreeSum.append(retVal)

        return retVal

    def maxProduct(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        subTreeSum = []
        treeSum = self.postOrder(root, subTreeSum)
        subTreeSumSize = len(subTreeSum)

        maxValue = 0
        for i in range(subTreeSumSize):
            maxValue = max(maxValue, (subTreeSum[i] * (treeSum - subTreeSum[i])))
        retVal = maxValue % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3, 4, 5, 6], [1, None, 2, 3, 4, None,  None, 5, 6]]:
            # /* Example
            #  *  Input: root = [1,2,3,4,5,6]
            #  *  Output: 110
            #  *
            #  *  Input: root = [1,null,2,3,4,null,null,5,6]
            #  *  Output: 90
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.maxProduct(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
