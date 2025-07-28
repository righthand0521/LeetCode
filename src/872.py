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
    def dfs(self, root: Optional[TreeNode], sequence: List[int]) -> None:
        if root is None:
            return

        if (root.left is None) and (root.right is None):
            sequence.append(root.val)
            return
        self.dfs(root.left, sequence)
        self.dfs(root.right, sequence)

    def leafSimilar(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        retVal = False

        sequence1 = []
        self.dfs(root1, sequence1)

        sequence2 = []
        self.dfs(root2, sequence2)

        if sequence1 == sequence2:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root1, root2 in zip([[3, 5, 1, 6, 2, 9, 8, None, None, 7, 4], [1, 2, 3]],
                                [[3, 5, 1, 6, 7, 4, 2, None, None, None, None, None, None, 9, 8], [1, 3, 2]]):
            # /* Example
            #  *  Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
            #  *  Output: true
            #  *
            #  *  Input: root1 = [1,2,3], root2 = [1,3,2]
            #  *  Output: false
            #  */
            logging.info("Input: root1 = %s, root2 = %s", root1, root2)

            root1 = TreeNode().buildTree(root1)
            root2 = TreeNode().buildTree(root2)

            retVal = pSolution.leafSimilar(root1, root2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
