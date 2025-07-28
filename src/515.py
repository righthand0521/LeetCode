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

    def dfs(self, root: Optional[TreeNode], level: int, answer: List[int]) -> None:
        if root is None:
            return

        if level == len(answer):
            answer.append(root.val)
        else:
            answer[level] = max(answer[level], root.val)

        self.dfs(root.left, level + 1, answer)
        self.dfs(root.right, level + 1, answer)

    def bfs(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        bfsQueue = deque([])
        bfsQueue.append(root)

        while bfsQueue:
            maxValue = float('-inf')    # -2^31 <= Node.val <= 2^31 - 1
            for _ in range(len(bfsQueue)):
                node = bfsQueue.popleft()

                maxValue = max(maxValue, node.val)

                if node.left != None:
                    bfsQueue.append(node.left)
                if node.right != None:
                    bfsQueue.append(node.right)

            retVal.append(maxValue)

        return retVal

    def largestValues(self, root: Optional[TreeNode]) -> List[int]:
        retVal = []

        if root is None:
            return retVal

        if self.method == 1:
            self.dfs(root, 0, retVal)
        elif self.method == 2:
            retVal = self.bfs(root)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 3, 2, 5, 3, None, 9], [1, 2, 3]]:
            # /* Example
            #  *  Input: root = [1,3,2,5,3,null,9]
            #  *  Output: [1,3,9]
            #  *
            #  *  Input: root = [1,2,3]
            #  *  Output: [1,3]
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.largestValues(TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
