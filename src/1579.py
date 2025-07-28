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
        retVal = 0

        if self.parent[x] != x:
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
        if x == y:
            retVal = True

        return retVal


class Solution:
    def maxNumEdgesToRemove(self, n: int, edges: List[List[int]]) -> int:
        retVal = 0

        ufa = UnionFind(n)
        ufb = UnionFind(n)

        for edge in edges:
            edge[1] -= 1
            edge[2] -= 1

        for t, u, v in edges:
            if t == 3:
                if not ufa.unite(u, v):
                    retVal += 1
                else:
                    ufb.unite(u, v)

        for t, u, v in edges:
            if t == 1:
                if not ufa.unite(u, v):
                    retVal += 1
            elif t == 2:
                if not ufb.unite(u, v):
                    retVal += 1

        if ufa.setCount != 1 or ufb.setCount != 1:
            retVal = -1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, edges in zip([4, 4, 4],
                            [[[3, 1, 2], [3, 2, 3], [1, 1, 3], [1, 2, 4], [1, 1, 2], [2, 3, 4]],
                             [[3, 1, 2], [3, 2, 3], [1, 1, 4], [2, 1, 4]],
                             [[3, 2, 3], [1, 1, 2], [2, 3, 4]]]):
            # /* Example
            #  *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
            #  *  Output: 2
            #  *
            #  *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
            #  *  Output: 0
            #  *
            #  *  Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
            #  *  Output: -1
            #  */
            logging.info("Input: n = %s, edges = %s", n, edges)

            retVal = pSolution.maxNumEdgesToRemove(n, edges)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
