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
    def topoSort(self, edges: List[List[int]], n: int) -> List[int]:
        retVal = []

        adjacency = [[] for _ in range(n + 1)]
        degree = [0] * (n + 1)
        for edge in edges:
            adjacency[edge[0]].append(edge[1])
            degree[edge[1]] += 1

        degreeQueue = deque()
        for i in range(1, n + 1):
            if degree[i] == 0:
                degreeQueue.append(i)
        while degreeQueue:
            order = degreeQueue.popleft()
            retVal.append(order)
            for neighbor in adjacency[order]:
                degree[neighbor] -= 1
                if degree[neighbor] == 0:
                    degreeQueue.append(neighbor)
            n -= 1

        if n != 0:
            retVal = []

        return retVal

    def buildMatrix(self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]) -> List[List[int]]:
        retVal = []

        orderRows = self.topoSort(rowConditions, k)
        orderColumns = self.topoSort(colConditions, k)
        if (not orderRows) or (not orderColumns):
            return retVal

        retVal = [[0] * k for _ in range(k)]
        for i in range(k):
            for j in range(k):
                if orderRows[i] == orderColumns[j]:
                    retVal[i][j] = orderRows[i]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, rowConditions, colConditions in zip(
            [3, 3],
            [[[1, 2], [3, 2]], [[1, 2], [2, 3], [3, 1], [2, 3]]],
            [[[2, 1], [3, 2]], [[2, 1]]]
        ):
            # /* Example
            #  *  Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
            #  *  Output: [[3,0,0],[0,0,1],[0,2,0]]
            #  *
            #  *  Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]], colConditions = [[2,1]]
            #  *  Output: []
            #  */
            logging.info("Input: k = %s, rowConditions = %s, colConditions = %s",
                         k, rowConditions, colConditions)

            retVal = pSolution.buildMatrix(k, rowConditions, colConditions)
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
