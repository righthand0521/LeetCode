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
        self.method = 2

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, root: Optional[TreeNode], level: int, sum: List[int]):
        if level == len(sum):
            sum.append(root.val)
        else:
            sum[level] += root.val

        if root.left:
            self.dfs(root.left, level + 1, sum)
        if root.right:
            self.dfs(root.right, level + 1, sum)

    def bfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        maxSum = float('-inf')
        level = 0
        bfsQueue = deque()
        bfsQueue.append(root)
        while bfsQueue:
            level += 1
            sum = 0
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()
                sum += node.val

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            if maxSum < sum:
                maxSum = sum
                retVal = level

        return retVal

    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if self.method == 1:
            sum = []
            self.dfs(root, 0, sum)
            retVal = sum.index(max(sum)) + 1
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 7, 0, 7, -8, None, None], [989, None, 10250, 98693, -89388, None, None, None, -32127]]:
            # /* Example
            #  *  Input: root = [1,7,0,7,-8,null,null]
            #  *  Output: 2
            #  *
            #  *  Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
            #  *  Output: 2
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.maxLevelSum(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
