import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class DisjointSetUnion:
    def __init__(self, n):
        self.n = n
        self.rank = [1] * n
        self.f = list(range(n))

    def find(self, x: int) -> int:
        if self.f[x] == x:
            return x
        self.f[x] = self.find(self.f[x])
        return self.f[x]

    def unionSet(self, x: int, y: int) -> bool:
        fx, fy = self.find(x), self.find(y)
        if fx == fy:
            return False

        if self.rank[fx] < self.rank[fy]:
            fx, fy = fy, fx

        self.rank[fx] += self.rank[fy]
        self.f[fy] = fx
        return True


class Solution:
    def distance(self, points: List[List[int]], x: int, y: int) -> int:
        retVal = 0

        diff_0 = abs(points[x][0] - points[y][0])
        diff_1 = abs(points[x][1] - points[y][1])
        retVal = diff_0 + diff_1

        return retVal

    def minCostConnectPoints(self, points: List[List[int]]) -> int:
        retVal = 0

        pointsSize = len(points)

        # Kruskal's algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
        dsu = DisjointSetUnion(pointsSize)
        edges = list()
        for i in range(pointsSize):
            for j in range(i + 1, pointsSize):
                edges.append((self.distance(points, i, j), i, j))
        edges.sort()

        num = 1
        for length, x, y in edges:
            if dsu.unionSet(x, y):
                retVal += length
                num += 1
                if num == pointsSize:
                    break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for points in [[[0, 0], [2, 2], [3, 10], [5, 2], [7, 0]], [[3, 12], [-2, 5], [-4, 1]]]:
            # /* Example
            #  *  Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
            #  *  Output: 20
            #  *
            #  *  Input: points = [[3,12],[-2,5],[-4,1]]
            #  *  Output: 18
            #  */
            logging.info("Input: points = %s", points)

            retVal = pSolution.minCostConnectPoints(points)
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
