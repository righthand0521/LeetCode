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
    def minimumSum2(self, grid: List[List[int]], u: int, d: int, l: int, r: int) -> int:
        retVal = 0

        minRow = len(grid)
        maxRow = 0
        minCol = len(grid[0])
        maxCol = 0
        for i in range(u, d + 1):
            for j in range(l, r + 1):
                if grid[i][j] == 1:
                    minRow = min(minRow, i)
                    minCol = min(minCol, j)
                    maxRow = max(maxRow, i)
                    maxCol = max(maxCol, j)

        retVal = ((maxRow - minRow + 1) * (maxCol - minCol + 1) if minRow <= maxRow else sys.maxsize // 3)

        return retVal

    def rotate(self, grid: List[List[int]]) -> List[List[int]]:
        retVal = []

        gridSize = len(grid)
        gridColSize = len(grid[0]) if gridSize > 0 else 0

        retVal = [[0] * gridSize for _ in range(gridColSize)]
        for i in range(gridSize):
            for j in range(gridColSize):
                retVal[gridColSize - j - 1][i] = grid[i][j]

        return retVal

    def solve(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0]) if gridSize > 0 else 0
        retVal = gridSize * gridColSize

        for i in range(gridSize - 1):
            for j in range(gridColSize - 1):
                x = self.minimumSum2(grid, 0, i, 0, gridColSize - 1)
                y = self.minimumSum2(grid, i + 1, gridSize - 1, 0, j)
                z = self.minimumSum2(grid, i + 1, gridSize - 1, j + 1, gridColSize - 1)
                retVal = min(retVal, x + y + z)

                x = self.minimumSum2(grid, 0, i, 0, j)
                y = self.minimumSum2(grid, 0, i, j + 1, gridColSize - 1)
                z = self.minimumSum2(grid, i + 1, gridSize - 1, 0, gridColSize - 1)
                retVal = min(retVal, x + y + z)

        for i in range(gridSize - 2):
            for j in range(i + 1, gridSize - 1):
                x = self.minimumSum2(grid, 0, i, 0, gridColSize - 1)
                y = self.minimumSum2(grid, i + 1, j, 0, gridColSize - 1)
                z = self.minimumSum2(grid, j + 1, gridSize - 1, 0, gridColSize - 1)
                retVal = min(retVal, x + y + z)

        return retVal

    def minimumSum(self, grid: List[List[int]]) -> int:
        retVal = 0

        rotateGrid = self.rotate(grid)
        retVal = min(self.solve(grid), self.solve(rotateGrid))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[1, 0, 1], [1, 1, 1]], [[1, 0, 1, 0], [0, 1, 0, 1]]]:
            # /* Example
            #  *  Input: grid = [[1,0,1],[1,1,1]]
            #  *  Output: 5
            #  *
            #  *  Input: grid = [[1,0,1,0],[0,1,0,1]]
            #  *  Output: 5
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minimumSum(grid)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
