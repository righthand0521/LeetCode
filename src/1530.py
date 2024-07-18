import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

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
    def traverseTree(self, currNode: TreeNode, prevNode: TreeNode, graph: dict, leafNodes: set) -> None:
        if currNode is None:
            return

        if (currNode.left is None) and (currNode.right is None):
            leafNodes.add(currNode)

        if prevNode is not None:
            if prevNode not in graph:
                graph[prevNode] = []
            graph[prevNode].append(currNode)

            if currNode not in graph:
                graph[currNode] = []
            graph[currNode].append(prevNode)

        self.traverseTree(currNode.left, currNode, graph, leafNodes)
        self.traverseTree(currNode.right, currNode, graph, leafNodes)

    def countPairs(self, root: TreeNode, distance: int) -> int:
        retVal = 0

        graph = {}
        leafNodes = set()
        self.traverseTree(root, None, graph, leafNodes)

        for leaf in leafNodes:
            bfsQueue = []
            bfsQueue.append(leaf)
            seen = set()
            seen.add(leaf)

            for _ in range(distance + 1):
                # Clear all nodes in the queue (distance i away from leaf node)
                # Add the nodes' neighbors (distance i+1 away from leaf node)
                bfsQueueSize = len(bfsQueue)
                for _ in range(bfsQueueSize):
                    currNode = bfsQueue.pop(0)
                    if (currNode in leafNodes) and (currNode != leaf):
                        retVal += 1
                    if currNode in graph:
                        for neighbor in graph.get(currNode):
                            if neighbor not in seen:
                                bfsQueue.append(neighbor)
                                seen.add(neighbor)

        retVal //= 2

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root, distance in zip([[1, 2, 3, None, 4],
                                   [1, 2, 3, 4, 5, 6, 7],
                                   [7, 1, 4, 6, None, 5, 3, None, None, None, None, None, 2]],
                                  [3, 3, 3]):
            # /* Example
            #  *  Input: root = [1,2,3,null,4], distance = 3
            #  *  Output: 1
            #  *
            #  *  Input: root = [1,2,3,4,5,6,7], distance = 3
            #  *  Output: 2
            #  *
            #  *  Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3
            #  *  Output: 1
            #  */
            logging.info("Input: root = %s, distance = %s", root, distance)

            retVal = pSolution.countPairs(TreeNode().buildTree(root), distance)
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
