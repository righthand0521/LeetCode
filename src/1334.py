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
    def dijkstra(self, n: int, adjacencyList: List[List[tuple]], shortestPathDistances: List[int], source: int) -> None:
        priorityQueue = [(0, source)]
        shortestPathDistances[:] = [float("inf")] * n
        shortestPathDistances[source] = 0
        while priorityQueue:
            currentDistance, currentCity = heappop(priorityQueue)
            if currentDistance > shortestPathDistances[currentCity]:
                continue

            for neighborCity, edgeWeight in adjacencyList[currentCity]:
                if (shortestPathDistances[neighborCity] > currentDistance + edgeWeight):
                    shortestPathDistances[neighborCity] = currentDistance + edgeWeight
                    heappush(priorityQueue, (shortestPathDistances[neighborCity], neighborCity))

    def getCityWithFewestReachable(self, n: int, shortestPathMatrix: List[List[int]], distanceThreshold: int) -> int:
        retVal = 0

        cityWithFewestReachable = -1
        fewestReachableCount = n
        for i in range(n):
            reachableCount = 0
            for j in range(n):
                if (i != j) and (shortestPathMatrix[i][j] <= distanceThreshold):
                    reachableCount += 1

            if reachableCount <= fewestReachableCount:
                fewestReachableCount = reachableCount
                cityWithFewestReachable = i

        retVal= cityWithFewestReachable

        return retVal

    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        retVal = 0

        adjacencyList = [[] for _ in range(n)]

        shortestPathMatrix = [[float("inf")] * n for _ in range(n)]
        for i in range(n):
            shortestPathMatrix[i][i] = 0

        for start, end, weight in edges:
            adjacencyList[start].append((end, weight))
            adjacencyList[end].append((start, weight))

        for i in range(n):
            self.dijkstra(n, adjacencyList, shortestPathMatrix[i], i)

        retVal = self.getCityWithFewestReachable(n, shortestPathMatrix, distanceThreshold)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges, distanceThreshold in zip([4, 5],
                                               [[[0, 1, 3], [1, 2, 1], [1, 3, 4], [2, 3, 1]],
                                                [[0, 1, 2], [0, 4, 8], [1, 2, 3], [1, 4, 2], [2, 3, 1], [3, 4, 1]]],
                                               [4, 2]):
            # /* Example
            #  *  Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
            #  *  Output: 3
            #  *
            #  *  Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
            #  *  Output: 0
            #  */
            logging.info("Input: n = %s, edges = %s, distanceThreshold = %s", n, edges, distanceThreshold)

            retVal = pSolution.findTheCity(n, edges, distanceThreshold)
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
