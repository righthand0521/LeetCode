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
    def __init__(self) -> None:
        self.fromDestination = None
        self.target = 0

    def dijkstra(self, option: int, source: int, n: int, edges: List[List[int]], adjacency: List[List[int]]) -> List[int]:
        retVal = []

        distance = [float("inf")] * n
        distance[source] = 0

        visited = [False] * n

        for _ in range(n - 1):
            u = -1
            for i in range(n):
                if visited[i] == True:
                    continue
                if ((u == -1) or (distance[i] < distance[u])):
                    u = i
            visited[u] = True

            for v in range(n):
                if visited[v] == True:
                    continue
                elif adjacency[u][v] == -1:
                    continue

                if edges[adjacency[u][v]][2] != -1:
                    distance[v] = min(distance[v], distance[u] + edges[adjacency[u][v]][2])
                    continue

                if option == 0:
                    distance[v] = min(distance[v], distance[u] + 1)
                else:
                    modify = self.target - distance[u] - self.fromDestination[v]
                    if modify > 0:
                        distance[v] = min(distance[v], distance[u] + modify)
                        edges[adjacency[u][v]][2] = modify
                    else:
                        edges[adjacency[u][v]][2] = self.target

        retVal = distance

        return retVal

    def modifiedGraphEdges(self, n: int, edges: List[List[int]], source: int, destination: int, target: int) -> List[List[int]]:
        retVal = []

        self.fromDestination = []
        self.target = target

        adjacency = [[-1] * n for _ in range(n)]
        for i, (u, v, w) in enumerate(edges):
            adjacency[u][v] = adjacency[v][u] = i

        self.fromDestination = self.dijkstra(0, destination, n, edges, adjacency)
        if self.fromDestination[source] > target:
            return retVal

        fromSource = self.dijkstra(1, source, n, edges, adjacency)
        if fromSource[destination] != target:
            return retVal

        retVal = edges

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, source, destination, target in zip(
            [5, 3, 4],
            [[[4, 1, -1], [2, 0, -1], [0, 3, -1], [4, 3, -1]],
             [[0, 1, -1], [0, 2, 5]],
             [[1, 0, 4], [1, 2, 3], [2, 3, 5], [0, 3, -1]]],
            [0, 0, 0],
            [1, 2, 2],
            [5, 6, 6]
        ):
            # /* Example
            #  *  Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
            #  *  Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
            #  *
            #  *  Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
            #  *  Output: []
            #  *
            #  *  Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
            #  *  Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
            #  */
            logging.info("Input: n = %s, edges = %s, source = %s, destination = %s, target = %s",
                         n, edges, source, destination, target)

            retVal = pSolution.modifiedGraphEdges(n, edges, source, destination, target)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
