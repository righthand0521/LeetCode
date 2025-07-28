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
    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        retVal = root

        if depth == 1:
            retVal = TreeNode(val, root, None)
            return retVal

        currentLevel = [root]
        for _ in range(1, depth-1):
            tmp = []
            for node in currentLevel:
                if node.left != None:
                    tmp.append(node.left)
                if node.right != None:
                    tmp.append(node.right)
            currentLevel = tmp

        for node in currentLevel:
            node.left = TreeNode(val, node.left, None)
            node.right = TreeNode(val, None, node.right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, val, depth in zip([[4, 2, 6, 3, 1, 5], [4, 2, None, 3, 1]], [1, 1], [2, 3]):
            # /* Example
            #  *  Input: root = [4,2,6,3,1,5], val = 1, depth = 2
            #  *  Output: [4,1,1,2,null,null,6,3,1,5]
            #  *
            #  *  Input: root = [4,2,null,3,1], val = 1, depth = 3
            #  *  Output: [4,2,null,1,1,3,null,null,1]
            #  */
            logging.info("Input: root = %s, val = %s, depth = %s", root, val, depth)

            root = TreeNode().buildTree(root)
            retVal = pSolution.addOneRow(root, val, depth)
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
