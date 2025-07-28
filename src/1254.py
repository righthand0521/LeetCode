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
    def dfs(self, grid, x, y) -> bool:
        retVal = False

        row = len(grid)
        col = len(grid[0])

        if x < 0 or x >= row or y < 0 or y >= col:
            return retVal

        if grid[x][y] == 1:
            retVal = True
            return retVal

        grid[x][y] = 1

        up = self.dfs(grid, x-1, y)
        down = self.dfs(grid, x+1, y)
        left = self.dfs(grid, x, y-1)
        right = self.dfs(grid, x, y+1)
        retVal = up and down and left and right

        return retVal

    def closedIsland(self, grid: List[List[int]]) -> int:
        retVal = 0

        row = len(grid)
        col = len(grid[0])

        for x in range(1, row):
            for y in range(1, col):
                if grid[x][y] != 0:
                    continue
                if self.dfs(grid, x, y) == True:
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 1, 1, 1, 1, 1, 1, 0],
                      [1, 0, 0, 0, 0, 1, 1, 0],
                      [1, 0, 1, 0, 1, 1, 1, 0],
                      [1, 0, 0, 0, 0, 1, 0, 1],
                      [1, 1, 1, 1, 1, 1, 1, 0]],
                     [[0, 0, 1, 0, 0],
                      [0, 1, 0, 1, 0],
                      [0, 1, 1, 1, 0]],
                     [[1, 1, 1, 1, 1, 1, 1],
                      [1, 0, 0, 0, 0, 0, 1],
                      [1, 0, 1, 1, 1, 0, 1],
                      [1, 0, 1, 0, 1, 0, 1],
                      [1, 0, 1, 1, 1, 0, 1],
                      [1, 0, 0, 0, 0, 0, 1],
                      [1, 1, 1, 1, 1, 1, 1]]]:
            # /* Example
            #  *  Input: grid = [[1,1,1,1,1,1,1,0],
            #  *                 [1,0,0,0,0,1,1,0],
            #  *                 [1,0,1,0,1,1,1,0],
            #  *                 [1,0,0,0,0,1,0,1],
            #  *                 [1,1,1,1,1,1,1,0]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[0,0,1,0,0],
            #  *                 [0,1,0,1,0],
            #  *                 [0,1,1,1,0]]
            #  *  Output: 1
            #  *
            #  *  Input: grid = [[1,1,1,1,1,1,1],
            #  *                 [1,0,0,0,0,0,1],
            #  *                 [1,0,1,1,1,0,1],
            #  *                 [1,0,1,0,1,0,1],
            #  *                 [1,0,1,1,1,0,1],
            #  *                 [1,0,0,0,0,0,1],
            #  *                 [1,1,1,1,1,1,1]]
            #  *  Output: 2
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.closedIsland(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
