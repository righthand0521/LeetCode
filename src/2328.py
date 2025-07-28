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


class Solution:
    def __init__(self):
        self.MODULO = 10 ** 9 + 7
        self.directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]

    def dfs(self, grid: List[List[int]], dp: List[List[int]], i, j):
        retVal = 1

        if dp[i][j] != 0:
            retVal = dp[i][j]
            return retVal

        gridSize = len(grid)
        gridColSize = len(grid[0])  # 1 <= m, n <= 1000
        for di, dj in self.directions:
            prev_i = i + di
            prev_j = j + dj
            if (0 <= prev_i < gridSize) and (0 <= prev_j < gridColSize) and (grid[prev_i][prev_j] < grid[i][j]):
                retVal += self.dfs(grid, dp, prev_i, prev_j) % self.MODULO

        dp[i][j] = retVal

        return retVal

    def countPaths(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])  # 1 <= m, n <= 1000
        dp = [[0] * gridColSize for _ in range(gridSize)]
        retVal = sum(self.dfs(grid, dp, i, j) for i in range(gridSize)
                     for j in range(gridColSize)) % self.MODULO

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 1], [3, 4]], [[1], [2]]]:
            # /* Example
            #  *  Input: grid = [[1,1],[3,4]]
            #  *  Output: 8
            #  *
            #  *  Input: grid = [[1],[2]]
            #  *  Output: 3
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.countPaths(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
