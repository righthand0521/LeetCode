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
        if self.parent[x] == x:
            return x
        self.parent[x] = self.findset(self.parent[x])
        return self.parent[x]

    def unite(self, x: int, y: int) -> bool:
        x, y = self.findset(x), self.findset(y)
        if x == y:
            return False
        if self.size[x] < self.size[y]:
            x, y = y, x
        self.parent[y] = x
        self.size[x] += self.size[y]
        self.setCount -= 1
        return True

    def connected(self, x: int, y: int) -> bool:
        x, y = self.findset(x), self.findset(y)
        return x == y


class Solution:
    def makeConnected(self, n: int, connections: List[List[int]]) -> int:
        retVal = -1

        if len(connections) < n - 1:
            return retVal

        uf = UnionFind(n)
        for x, y in connections:
            uf.unite(x, y)
        retVal = uf.setCount - 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, connections in zip([4, 6, 6],
                                  [[[0, 1], [0, 2], [1, 2]],
                                  [[0, 1], [0, 2], [0, 3], [1, 2], [1, 3]],
                                  [[0, 1], [0, 2], [0, 3], [1, 2]]]):
            # /* Example
            #  *  Input: n = 4, connections = [[0,1],[0,2],[1,2]]
            #  *  Output: 1
            #  *
            #  *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
            #  *  Output: 2
            #  *
            #  *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
            #  *  Output: -1
            #  */
            logging.info("Input: n = %d, connections = %s", n, connections)

            retVal = pSolution.makeConnected(n, connections)
            logging.info("Output: %d", retVal)

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
