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
        self.method = 2
        if self.method == 1:
            print("Recursion")
        elif self.method == 2:
            print("Iterative")
        print()

    def allPossibleFBT(self, n: int) -> List[Optional[TreeNode]]:
        retVal = []

        if n % 2 == 0:
            return retVal

        if self.method == 1:
            if n == 1:
                return [TreeNode()]

            for i in range(1, n, 2):
                left = self.allPossibleFBT(i)
                right = self.allPossibleFBT(n - i - 1)
                for l in left:
                    for r in right:
                        root = TreeNode(0, l, r)
                        retVal.append(root)
        elif self.method == 2:
            dp = [[] for _ in range(n + 1)]
            dp[1].append(TreeNode(0))
            for count in range(3, n + 1, 2):
                for i in range(1, count - 1, 2):
                    j = count - 1 - i
                    for left in dp[i]:
                        for right in dp[j]:
                            root = TreeNode(0, left, right)
                            dp[count].append(root)
            retVal = dp[n]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n in [7, 3]:
            # /* Example
            #  *  Input: n = 7
            #  *  Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],
            #  *  [0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
            #  *
            #  *  Input: n = 3
            #  *  Output: [[0,0,0]]
            #  */
            logging.info("Input: n = %s", n)

            retVal = pSolution.allPossibleFBT(n)
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
