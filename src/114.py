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
    def flatten(self, root: Optional[TreeNode]) -> None:
        """
        Do not return anything, modify root in-place instead.
        """
        current = root
        while current:
            if current.left:
                next = current.left
                previous = current.left
                while previous.right:
                    previous = previous.right
                previous.right = current.right
                current.left = None
                current.right = next
            current = current.right


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 5, 3, 4, None, 6], [], [0]]:
            # /* Example
            #  *  Input: root = [1,2,5,3,4,null,6]
            #  *  Output: [1,null,2,null,3,null,4,null,5,null,6]
            #  *
            #  *  Input: root = []
            #  *  Output: []
            #  *
            #  *  Input: root = [0]
            #  *  Output: [0]
            #  */
            logging.info("Input: root = %s", root)

            retVal = TreeNode().buildTree(root)
            pSolution.flatten(retVal)
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
