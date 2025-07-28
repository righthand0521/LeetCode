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
        self.method = 1

        if self.method == 1:
            print("Depth-First Search")
        elif self.method == 2:
            print("Breadth-First Search")
        print()

    def dfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if (root.left == None) and (root.right == None):
            retVal += 1
            return retVal

        if root.left == None:
            retVal = 1 + self.dfs(root.right)
        elif root.right == None:
            retVal = 1 + self.dfs(root.left)
        else:
            retVal = 1 + min(self.dfs(root.left), self.dfs(root.right))

        return retVal

    def bfs(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        bfsQueue = deque()
        bfsQueue.append(root)
        retVal = 1
        while bfsQueue:
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()

                if (node.left == None) and (node.right == None):
                    return retVal

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            retVal += 1

        return retVal

    def minDepth(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        if root == None:
            return retVal

        if self.method == 1:
            retVal = self.dfs(root)
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[3, 9, 20, None, None, 15, 7], [2, None, 3, None, 4, None, 5, None, 6]]:
            # /* Example
            #  *  Input: root = [3,9,20,null,null,15,7]
            #  *  Output: 2
            #  *
            #  *  Input: root = [2,null,3,null,4,null,5,null,6]
            #  *  Output: 5
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.minDepth(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
