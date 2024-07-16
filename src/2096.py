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
    def findPath(self, node: TreeNode, target: int, path: List[str]) -> bool:
        retVal = False

        if node is None:
            return retVal

        if node.val == target:
            retVal = True
            return retVal

        # Try left subtree
        path.append("L")
        if self.findPath(node.left, target, path):
            retVal = True
            return retVal

        # Remove last character
        path.pop()

        # Try right subtree
        path.append("R")
        if self.findPath(node.right, target, path):
            retVal = True
            return retVal

        # Remove last character
        path.pop()

        return retVal

    def getDirections(self, root: Optional[TreeNode], startValue: int, destValue: int) -> str:
        retVal = ""

        # Find paths from root to start and destination nodes
        startPath = []
        self.findPath(root, startValue, startPath)
        startPathSize = len(startPath)
        destPath = []
        self.findPath(root, destValue, destPath)
        destPathSize = len(destPath)

        # Find the length of the common path
        commonPathLength = 0
        while ((commonPathLength < startPathSize) and (commonPathLength < destPathSize)
               and (startPath[commonPathLength] == destPath[commonPathLength])):
            commonPathLength += 1

        directions = []
        # Add "U" for each step to go up from start to common ancestor
        directions.extend("U" * (startPathSize - commonPathLength))
        # Add directions from common ancestor to destination
        directions.extend(destPath[commonPathLength:])

        retVal = "".join(directions)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, startValue, destValue in zip([[5, 1, 2, 3, None, 6, 4], [2, 1]], [3, 2], [6, 1]):
            # /* Example
            #  *  Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
            #  *  Output: "UURL"
            #  *
            #  *  Input: root = [2,1], startValue = 2, destValue = 1
            #  *  Output: "L"
            #  */
            logging.info(
                "Input: root = %s, startValue = %s, destValue = %s", root, startValue, destValue)

            retVal = pSolution.getDirections(
                TreeNode().buildTree(root), startValue, destValue)
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
