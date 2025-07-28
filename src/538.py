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
    def __init__(self) -> None:
        self.addValue = 0

    def plusTraversal(self, root: TreeNode) -> None:
        if root is None:
            return

        self.plusTraversal(root.right)
        root.val += self.addValue
        self.addValue = root.val
        self.plusTraversal(root.left)

    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if retVal is None:
            return retVal

        self.addValue = 0
        self.plusTraversal(retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[4, 1, 6, 0, 2, 5, 7, None, None, None, 3, None, None, None, 8], [0, None, 1]]:
            # /* Example
            #  *  Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
            #  *  Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
            #  *
            #  *  Input: root = [0,null,1]
            #  *  Output: [1,null,1]
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.convertBST(root)
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
