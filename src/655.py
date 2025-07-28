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

    def dfsDepth(self, node: Optional[TreeNode]) -> int:
        retVal = 0

        leftDepth = self.dfsDepth(node.left) + 1 if node.left else 0
        rightDepth = self.dfsDepth(node.right) + 1 if node.right else 0
        retVal = max(leftDepth, rightDepth)

        return retVal

    def dfs(self, node: Optional[TreeNode], height: int, row: int, col: int, retVal: List[List[str]]) -> None:
        retVal[row][col] = str(node.val)
        if node.left:
            self.dfs(node.left, height, row + 1, col -
                     2 ** (height - row - 1), retVal)
        if node.right:
            self.dfs(node.right, height, row + 1, col +
                     2 ** (height - row - 1), retVal)

    def bfsDepth(self, root: Optional[TreeNode]) -> int:
        retVal = -1

        record = [root]
        while record:
            retVal += 1
            tmp = record
            record = []
            for node in tmp:
                if node.left:
                    record.append(node.left)
                if node.right:
                    record.append(node.right)

        return retVal

    def bfs(self, root: Optional[TreeNode], height: int, n: int, retVal: List[List[str]]) -> None:
        bfsQueue = deque([(root, 0, (n - 1) // 2)])
        while bfsQueue:
            node, row, col = bfsQueue.popleft()
            retVal[row][col] = str(node.val)
            if node.left:
                bfsQueue.append(
                    (node.left, row + 1, col - 2 ** (height - row - 1)))
            if node.right:
                bfsQueue.append(
                    (node.right, row + 1, col + 2 ** (height - row - 1)))

    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        retVal = []

        if self.method == 1:
            height = self.dfsDepth(root)
            m = height + 1
            n = 2 ** m - 1
            retVal = [[''] * n for _ in range(m)]
            self.dfs(root, height, 0, (n - 1) // 2, retVal)
        elif self.method == 2:
            height = self.bfsDepth(root)
            m = height + 1
            n = 2 ** m - 1
            retVal = [[''] * n for _ in range(m)]
            self.bfs(root, height, n, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2], [1, 2, 3, None, 4]]:
            # /* Example
            #  *  Input: root = [1,2]
            #  *  Output:
            #  *  [["","1",""],
            #  *   ["2","",""]]
            #  *
            #  *  Input: root = [1,2,3,null,4]
            #  *  Output:
            #  *  [["","","","1","","",""],
            #  *   ["","2","","","","3",""],
            #  *   ["","","4","","","",""]]
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.printTree(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
