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
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        retVal = root

        current = root
        currentParent = None
        while current and current.val != key:
            currentParent = current
            if current.val > key:
                current = current.left
            else:
                current = current.right

        if current is None:
            return retVal
        if current.left is None and current.right is None:
            current = None
        elif current.right is None:
            current = current.left
        elif current.left is None:
            current = current.right
        else:
            successor = current.right
            successorParent = current
            while successor.left:
                successorParent = successor
                successor = successor.left

            if successorParent.val == current.val:
                successorParent.right = successor.right
            else:
                successorParent.left = successor.right
            successor.right = current.right
            successor.left = current.left
            current = successor

        if currentParent is None:
            retVal = current
            return retVal

        if currentParent.left and currentParent.left.val == key:
            currentParent.left = current
        else:
            currentParent.right = current

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, key in zip([[5, 3, 6, 2, 4, None, 7], [5, 3, 6, 2, 4, None, 7], []], [3, 0, 0]):
            # /* Example
            #  *  Input: root = [5,3,6,2,4,null,7], key = 3
            #  *  Output: [5,4,6,2,null,null,7]
            #  *
            #  *  Input: root = [5,3,6,2,4,null,7], key = 0
            #  *  Output: [5,3,6,2,4,null,7]
            #  *
            #  *  Input: root = [], key = 0
            #  *  Output: []
            #  */
            logging.info("Input: root = %s, key = %s", root, key)

            root = TreeNode().buildTree(root)
            retVal = pSolution.deleteNode(root, key)
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
