import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop
from copy import deepcopy


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# Definition for a Node.
class Node:
    def __init__(self, val=0, neighbors=None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []


class Solution:
    def __init__(self):
        self.method = 1
        if self.method == 1:    # 1: Depth-First Search
            print("Depth-First Search")
        elif self.method == 2:  # 2: Breadth-First Search
            print("Breadth-First Search")
        elif self.method == 3:  # 3: https://docs.python.org/3/library/copy.html
            print("https://docs.python.org/3/library/copy.html")

        self.visited = {}

    def cloneGraph(self, node: 'Node') -> 'Node':
        retVal = node

        if not node:
            return retVal

        if self.method == 1:    # 1: Depth-First Search
            if node in self.visited:
                return self.visited[node]

            cloneNode = Node(node.val, [])
            self.visited[node] = cloneNode
            if node.neighbors:
                cloneNode.neighbors = [self.cloneGraph(
                    neighbors) for neighbors in node.neighbors]

            retVal = cloneNode
        elif self.method == 2:  # 2: Breadth-First Search
            queue = deque([node])
            self.visited[node] = Node(node.val, [])

            while queue:
                n = queue.popleft()
                for neighbor in n.neighbors:
                    if neighbor not in self.visited:
                        self.visited[neighbor] = Node(neighbor.val, [])
                        queue.append(neighbor)
                    self.visited[n].neighbors.append(self.visited[neighbor])

            retVal = self.visited[node]
        elif self.method == 3:  # 3: https://docs.python.org/3/library/copy.html
            retVal = deepcopy(node)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for adjList in [[[2, 4], [1, 3], [2, 4], [1, 3]], [[]], [[]]]:
            # /* Example
            #  *  Input: adjList = [[2, 4], [1, 3], [2, 4], [1, 3]]
            #  *  Output: [[2, 4], [1, 3], [2, 4], [1, 3]]
            #  *
            #  *  Input: adjList = [[]]
            #  *  Output: [[]]
            #  *
            #  *  Input: adjList = []
            #  *  Output: []
            #  */
            logging.info("Input: adjList = %s", adjList)

            # retVal = pSolution.cloneGraph(adjList)
            # logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
