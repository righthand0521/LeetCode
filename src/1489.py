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


class UnionFind:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.size = [1] * n
        self.n = n
        self.setCount = n

    def findset(self, x: int) -> int:
        retVal = x

        if self.parent[x] == x:
            return retVal

        self.parent[x] = self.findset(self.parent[x])
        retVal = self.parent[x]

        return retVal

    def unite(self, x: int, y: int) -> bool:
        retVal = False

        x = self.findset(x)
        y = self.findset(y)
        if x == y:
            return retVal

        if self.size[x] < self.size[y]:
            x, y = y, x
        self.parent[y] = x
        self.size[x] += self.size[y]
        self.setCount -= 1
        retVal = True

        return retVal

    def connected(self, x: int, y: int) -> bool:
        retVal = False

        x = self.findset(x)
        y = self.findset(y)
        retVal = (x == y)

        return retVal


class Solution:
    def findCriticalAndPseudoCriticalEdges(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        retVal = [list(), list()]

        edgesSize = len(edges)

        for i, edge in enumerate(edges):
            edge.append(i)
        edges.sort(key=lambda x: x[2])

        uf_std = UnionFind(n)
        value = 0
        for i in range(edgesSize):
            if uf_std.unite(edges[i][0], edges[i][1]):
                value += edges[i][2]

        for i in range(edgesSize):
            uf = UnionFind(n)
            v = 0

            for j in range(edgesSize):
                if (i != j) and (uf.unite(edges[j][0], edges[j][1]) == True):
                    v += edges[j][2]

            if (uf.setCount != 1) or ((uf.setCount == 1) and (v > value)):
                retVal[0].append(edges[i][3])
                continue

            uf = UnionFind(n)
            uf.unite(edges[i][0], edges[i][1])
            v = edges[i][2]

            for j in range(edgesSize):
                if (i != j) and (uf.unite(edges[j][0], edges[j][1]) == True):
                    v += edges[j][2]

            if v == value:
                retVal[1].append(edges[i][3])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([5, 4],
                            [[[0, 1, 1], [1, 2, 1], [2, 3, 2], [0, 3, 2], [0, 4, 3], [3, 4, 3], [1, 4, 6]],
                             [[0, 1, 1], [1, 2, 1], [2, 3, 1], [0, 3, 1]]]):
            # /* Example
            #  *  Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
            #  *  Output: [[0,1],[2,3,4,5]]
            #  *
            #  *  Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
            #  *  Output: [[],[0,1,2,3]]
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.findCriticalAndPseudoCriticalEdges(n, edges)
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
