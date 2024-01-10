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

    def dfs(self, root: Optional[TreeNode], targetSum: int, path: List[int], retVal: List[List[int]]) -> None:
        if root is None:
            return

        path.append(root.val)

        targetSum -= root.val
        if (root.left is None) and (root.right is None) and (targetSum == 0):
            retVal.append(path[:])
        self.dfs(root.left, targetSum, path, retVal)
        self.dfs(root.right, targetSum, path, retVal)

        path.pop()

    def bfs(self, root: Optional[TreeNode], targetSum: int, retVal: List[List[int]]) -> None:
        if root is None:
            return

        parent = defaultdict(lambda: None)
        targetSumQueue = deque([0])

        bfsQueue = deque([root])
        while bfsQueue:
            node = bfsQueue.popleft()
            sum = targetSumQueue.popleft() + node.val

            if (node.left is None) and (node.right is None):
                if sum == targetSum:
                    tmp = []
                    while node:
                        tmp.append(node.val)
                        node = parent[node]
                    retVal.append(tmp[::-1])
            else:
                if node.left:
                    parent[node.left] = node
                    bfsQueue.append(node.left)
                    targetSumQueue.append(sum)
                if node.right:
                    parent[node.right] = node
                    bfsQueue.append(node.right)
                    targetSumQueue.append(sum)

    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:
        retVal = []

        if self.method == 1:
            path = []
            self.dfs(root, targetSum, path, retVal)
        elif self.method == 2:
            self.bfs(root, targetSum, retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, targetSum in zip([[5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1], [1, 2, 3], [1, 2]], [22, 5, 0]):
            # /* Example
            #  *  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
            #  *  Output: [[5,4,11,2],[5,8,4,5]]
            #  *
            #  *  Input: root = [1,2,3], targetSum = 5
            #  *  Output: []
            #  *
            #  *  Input: root = [1,2], targetSum = 0
            #  *  Output: []
            #  */
            logging.info("Input: root = %s, targetSum = %s", root, targetSum)

            root = TreeNode().buildTree(root)
            retVal = pSolution.pathSum(root, targetSum)
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
