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
    def removeLeafNodes(self, root: Optional[TreeNode], target: int) -> Optional[TreeNode]:
        retVal = root

        if retVal is None:
            return retVal

        retVal.left = self.removeLeafNodes(retVal.left, target)
        retVal.right = self.removeLeafNodes(retVal.right, target)
        if (retVal.left is None) and (retVal.right is None) and (retVal.val == target):
            retVal = None

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, target in zip([[1, 2, 3, 2, None, 2, 4], [1, 3, 3, 3, 2], [1, 2, None, 2, None, 2]], [2, 3, 2]):
            # /* Example
            #  *  Input: root = [1,2,3,2,null,2,4], target = 2
            #  *  Output: [1,null,3,null,4]
            #  *
            #  *  Input: root = [1,3,3,3,2], target = 3
            #  *  Output: [1,3,null,null,2]
            #  *
            #  *  Input: root = [1,2,null,2,null,2], target = 2
            #  *  Output: [1]
            #  */
            logging.info("Input: root = %s, target = %s", root, target)

            root = TreeNode().buildTree(root)
            retVal = pSolution.removeLeafNodes(root, target)
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
