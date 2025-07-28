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
        self.adjacency = None

    def toUndirectedGraph(self, root: Optional[TreeNode]) -> None:
        if root.left:
            self.adjacency[root.val].append(root.left.val)
            self.adjacency[root.left.val].append(root.val)
            self.toUndirectedGraph(root.left)

        if root.right:
            self.adjacency[root.val].append(root.right.val)
            self.adjacency[root.right.val].append(root.val)
            self.toUndirectedGraph(root.right)

    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        retVal = 0

        self.adjacency = defaultdict(list)
        self.toUndirectedGraph(root)

        bfsQueue = deque([start])
        visited = set()
        visited.add(start)

        retVal = -1
        while bfsQueue:
            bfsQueueSize = len(bfsQueue)
            for _ in range(bfsQueueSize):
                leaf = bfsQueue.popleft()
                for neighbor in self.adjacency[leaf]:
                    if neighbor in visited:
                        continue
                    visited.add(neighbor)
                    bfsQueue.append(neighbor)
            retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, start in zip([[1, 5, 3, None, 4, 10, 6, 9, 2], [1]], [3, 1]):
            # /* Example
            #  *  Input: root = [1,5,3,null,4,10,6,9,2], start = 3
            #  *  Output: 4
            #  *
            #  *  Input: root = [1], start = 1
            #  *  Output: 0
            #  */
            logging.info("Input: root = %s, start = %s", root, start)

            retVal = pSolution.amountOfTime(TreeNode().buildTree(root), start)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
