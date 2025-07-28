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
        self.answer = ""

    def dfs(self, root: Optional[TreeNode], currentStr: str) -> None:
        if root is None:
            return

        currentStr = chr(root.val + ord('a')) + currentStr

        if (root.left is None) and (root.right is None):
            if (not self.answer) or (self.answer > currentStr):
                self.answer = currentStr

        if root.left:
            self.dfs(root.left, currentStr)

        if root.right:
            self.dfs(root.right, currentStr)

    def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
        retVal = ""

        self.answer = ""
        self.dfs(root, "")
        retVal = self.answer

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[0, 1, 2, 3, 4, 3, 4], [25, 1, 3, 1, 3, 0, 2], [2, 2, 1, None, 1, 0, None, 0]]:
            # /* Example
            #  *  Input: root = [0,1,2,3,4,3,4]
            #  *  Output: "dba"
            #  *
            #  *  Input: root = [25,1,3,1,3,0,2]
            #  *  Output: "adz"
            #  *
            #  *  Input: root = [2,2,1,null,1,0,null,0]
            #  *  Output: "abc"
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.smallestFromLeaf(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
