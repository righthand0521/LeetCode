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
    def __init__(self):
        self.maxLength = 0

    def dfs(self, root: Optional[TreeNode], dir: bool, len: int):
        self.maxLength = max(self.maxLength, len)

        # bool dir: left is false, right is true.
        if dir == False:
            if root.left != None:
                self.dfs(root.left, True, len + 1)
            if root.right != None:
                self.dfs(root.right, False, 1)
        else:
            if root.right != None:
                self.dfs(root.right, False, len + 1)
            if root.left != None:
                self.dfs(root.left, True, 1)

    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        # bool dir: left is false, right is true.
        self.maxLength = 0
        self.dfs(root, False, 0)
        self.dfs(root, True, 0)
        retVal = self.maxLength

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, None, 1, 1, 1, None, None, 1, 1, None, 1, None, None, None, 1, None, 1],
                     [1, 1, 1, None, 1, None, None, 1, 1, None, 1],
                     [1]]:
            # /* Example
            #  *  Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
            #  *  Output: 3
            #  *
            #  *  Input: root = [1,1,1,null,1,null,null,1,1,null,1]
            #  *  Output: 4
            #  *
            #  *  Input: root = [1]
            #  *  Output: 0
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.longestZigZag(TreeNode().buildTree(root))
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
