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
    def __init__(self) -> None:
        self.Directions = [(0, 1), (0, -1), (1, 0), (-1, 0),]

    def floodFill(self, expandedGrid: List[str], x: int, y: int) -> None:
        expandedGridSize = len(expandedGrid)
        expandedGrid[x][y] = 1

        queue = [(x, y)]
        while queue:
            currentCell = queue.pop(0)

            for direction in self.Directions:
                row = direction[0] + currentCell[0]
                col = direction[1] + currentCell[1]

                if (row < 0) or (row >= expandedGridSize):
                    continue
                elif (col < 0) or (col >= expandedGridSize):
                    continue
                elif expandedGrid[row][col] != 0:
                    continue

                expandedGrid[row][col] = 1
                queue.append((row, col))

    def regionsBySlashes(self, grid: List[str]) -> int:
        retVal = 0

        gridSize = len(grid)
        expandedGridSize = gridSize * 3

        expandedGrid = [[0] * expandedGridSize for _ in range(expandedGridSize)]
        for x in range(gridSize):
            for y in range(gridSize):
                row = x * 3
                col = y * 3
                if grid[x][y] == "\\":
                    expandedGrid[row][col] = 1
                    expandedGrid[row + 1][col + 1] = 1
                    expandedGrid[row + 2][col + 2] = 1
                elif grid[x][y] == "/":
                    expandedGrid[row][col + 2] = 1
                    expandedGrid[row + 1][col + 1] = 1
                    expandedGrid[row + 2][col] = 1

        for x in range(expandedGridSize):
            for y in range(expandedGridSize):
                if expandedGrid[x][y] == 0:
                    self.floodFill(expandedGrid, x, y)
                    retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[" /", "/ "], [" /", "  "], ["/\\", "\\/"]]:
            # /* Example
            #  *  Input: grid = [" /","/ "]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [" /","  "]
            #  *  Output: 1
            #  *
            #  *  Input: grid = ["/\\","\\/"]
            #  *  Output: 5
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.regionsBySlashes(grid)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
