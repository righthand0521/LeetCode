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
        self.currentMaxHeight = 0
        self.maxHeightAfterRemoval = []

    def traverseLeftToRight(self, node, currentHeight):
        if not node:
            return

        # Store the maximum height if this node were removed
        self.maxHeightAfterRemoval[node.val] = self.currentMaxHeight

        # Update the current maximum height
        self.currentMaxHeight = max(self.currentMaxHeight, currentHeight)

        # Traverse left subtree first, then right
        self.traverseLeftToRight(node.left, currentHeight + 1)
        self.traverseLeftToRight(node.right, currentHeight + 1)

    def traverseRightToLeft(self, node, currentHeight):
        if not node:
            return

        # Update the maximum height if this node were removed
        self.maxHeightAfterRemoval[node.val] = max(self.maxHeightAfterRemoval[node.val], self.currentMaxHeight)

        # Update the current maximum height
        self.currentMaxHeight = max(currentHeight, self.currentMaxHeight)

        # Traverse right subtree first, then left
        self.traverseRightToLeft(node.right, currentHeight + 1)
        self.traverseRightToLeft(node.left, currentHeight + 1)

    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        retVal = []

        self.maxHeightAfterRemoval = [0] * 100001
        self.currentMaxHeight = 0
        self.traverseLeftToRight(root, 0)
        self.currentMaxHeight = 0
        self.traverseRightToLeft(root, 0)

        for querie in queries:
            retVal.append(self.maxHeightAfterRemoval[querie])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, queries in zip(
            [[1, 3, 4, 2, None, 6, 5, None, None, None, None, None, 7],
             [5, 8, 9, 2, 1, 3, 7, 4, 6]],
            [[4],
             [3, 2, 4, 8]]
        ):
            # /* Example
            #  *  Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
            #  *  Output: [2]
            #  *
            #  *  Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
            #  *  Output: [3,2,3,2]
            #  */
            logging.info("Input: root = %s, queries = %s", root, queries)

            retVal = pSolution.treeQueries(TreeNode().buildTree(root), queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
