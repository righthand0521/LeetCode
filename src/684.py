import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Solution:
    def __init__(self):
        self.cycleStart = -1

    def dfs(self, src, visited, adjList, parent) -> None:
        visited[src] = True
        for adj in adjList[src]:
            if visited[adj] == False:
                parent[adj] = src
                self.dfs(adj, visited, adjList, parent)
            elif (adj != parent[src]) and (self.cycleStart == -1):
                # If the node is visited and the parent is different then the node is part of the cycle.
                self.cycleStart = adj
                parent[adj] = src

    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        retVal = []  # This line should theoretically never be reached

        self.cycleStart = -1

        edgesSize = len(edges)

        adjList = [[] for _ in range(edgesSize)]
        for edge in edges:
            adjList[edge[0] - 1].append(edge[1] - 1)
            adjList[edge[1] - 1].append(edge[0] - 1)

        visited = [False] * edgesSize
        parent = [-1] * edgesSize
        self.dfs(0, visited, adjList, parent)  # Perform the DFS and store a node in the cycle as cycleStart.

        # Start from the cycleStart node and backtrack to get all the nodes in the cycle. Mark them all in the map.
        cycleNodes = {}
        node = self.cycleStart
        while True:
            cycleNodes[node] = 1
            node = parent[node]
            if node == self.cycleStart:
                break

        # If both nodes of the edge were marked as cycle nodes then this edge can be removed.
        for i in range(edgesSize - 1, -1, -1):
            if ((edges[i][0] - 1) in cycleNodes) and ((edges[i][1] - 1) in cycleNodes):
                retVal = edges[i]
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for edges in [[[1, 2], [1, 3], [2, 3]], [[1, 2], [2, 3], [3, 4], [1, 4], [1, 5]]]:
            # /* Example
            #  *  Input: edges = [[1,2],[1,3],[2,3]]
            #  *  Output: [2,3]
            #  *
            #  *  Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
            #  *  Output: [1,4]
            #  */
            logging.info("Input: edges = %s", edges)

            retVal = pSolution.findRedundantConnection(edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
