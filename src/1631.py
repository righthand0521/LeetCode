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
    def minimumEffortPath(self, heights: List[List[int]]) -> int:
        retVal = 0

        rows = len(heights)
        columns = len(heights[0])  # 1 <= rows, columns <= 100

        edges = list()
        for x in range(rows):
            for y in range(columns):
                idx = x * columns + y
                if x > 0:
                    edges.append(
                        (idx-columns, idx, abs(heights[x][y]-heights[x-1][y])))
                if y > 0:
                    edges.append(
                        (idx-1, idx, abs(heights[x][y]-heights[x][y-1])))
        edges.sort(key=lambda e: e[2])

        uf = UnionFind(rows * columns)
        for x, y, v in edges:
            uf.unite(x, y)
            if uf.connected(0, rows * columns - 1):
                retVal = v
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for heights in [[[1, 2, 2], [3, 8, 2], [5, 3, 5]],
                        [[1, 2, 3], [3, 8, 4], [5, 3, 5]],
                        [[1, 2, 1, 1, 1], [1, 2, 1, 2, 1], [1, 2, 1, 2, 1], [1, 2, 1, 2, 1], [1, 1, 1, 2, 1]]]:
            # /* Example
            #  *  Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
            #  *  Output: 2
            #  *
            #  *  Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
            #  *  Output: 1
            #  *
            #  *  Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
            #  *  Output: 0
            #  */
            logging.info("Input: points = %s", heights)

            retVal = pSolution.minimumEffortPath(heights)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
