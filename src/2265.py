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
    def __init__(self) -> None:
        self.answer = 0

    def postorder(self, root: Optional[TreeNode]) -> List[int]:
        if root == None:
            return [0, 0]

        leftSum, leftNode = self.postorder(root.left)
        rightSum, rightNode = self.postorder(root.right)

        subtreeSum = leftSum + rightSum + root.val
        subtreeNode = leftNode + rightNode + 1
        if root.val == subtreeSum // subtreeNode:
            self.answer += 1

        return [subtreeSum, subtreeNode]

    def averageOfSubtree(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        self.answer = 0
        self.postorder(root)
        retVal = self.answer

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[4, 8, 5, 0, 1, None, 6], [1]]:
            # /* Example
            #  *  Input: root = [4,8,5,0,1,null,6]
            #  *  Output: 5
            #  *
            #  *  Input: root = [1]
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.averageOfSubtree(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
