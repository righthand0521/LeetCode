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
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def binaryTreeToGraph(self, root: TreeNode, graph: defaultdict[list]):
        if root is None:
            return

        if root.left:
            graph[root.val].append(root.left.val)
            graph[root.left.val].append(root.val)
            self.binaryTreeToGraph(root.left, graph)

        if root.right:
            graph[root.val].append(root.right.val)
            graph[root.right.val].append(root.val)
            self.binaryTreeToGraph(root.right, graph)

    def bfs(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        retVal = []

        graph = defaultdict(list)
        self.binaryTreeToGraph(root, graph)
        graph = dict(graph)
        if not graph:
            return retVal

        bfsQueue = deque()
        bfsQueue.append([target.val, 0])
        visited = [target.val]
        while bfsQueue:
            current, distance = bfsQueue.popleft()
            if distance == k:
                retVal.append(current)

            for neighbor in graph[current]:
                if neighbor in visited:
                    continue
                bfsQueue.append([neighbor, distance+1])
                visited.append(neighbor)

        return retVal

    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        retVal = []

        if root == None:
            return retVal

        retVal = self.bfs(root, target, k)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, target, k in zip([[3, 5, 1, 6, 2, 0, 8, None, None, 7, 4], [1]], [5, 1], [2, 3]):
            # /* Example
            #  *  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
            #  *  Output: [7,4,1]
            #  *
            #  *  Input: root = [1], target = 1, k = 3
            #  *  Output: []
            #  */
            logging.info("Input: root = %s, target = %s, k = %s", root, target, k)

            root = TreeNode().buildTree(root)
            if target == 5:
                target = root.left
            else:
                target = root
            retVal = pSolution.distanceK(root, target, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
