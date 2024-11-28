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
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    def isValid(self, gridSize: int, gridColSize: int, row: int, col: int) -> bool:
        retVal = False

        if (0 <= row < gridSize) and (0 <= col < gridColSize):
            retVal = True

        return retVal

    def minimumObstacles(self, grid: List[List[int]]) -> int:
        retVal = 0

        gridSize = len(grid)
        gridColSize = len(grid[0])

        minObstacles = [[float("inf")] * gridColSize for _ in range(gridSize)]
        minObstacles[0][0] = grid[0][0]

        priorityQueue = [(minObstacles[0][0], 0, 0)]
        while priorityQueue:
            obstacles, row, col = heappop(priorityQueue)
            if (row == gridSize - 1) and (col == gridColSize - 1):
                retVal = obstacles
                return retVal

            for x, y in self.directions:
                newRow = row + x
                newCol = col + y
                if self.isValid(gridSize, gridColSize, newRow, newCol) == False:
                    continue

                newObstacles = obstacles + grid[newRow][newCol]
                if newObstacles < minObstacles[newRow][newCol]:
                    minObstacles[newRow][newCol] = newObstacles
                    heappush(priorityQueue, (newObstacles, newRow, newCol))

        retVal = minObstacles[gridSize - 1][gridColSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for grid in [[[0, 1, 1], [1, 1, 0], [1, 1, 0]], [[0, 1, 0, 0, 0], [0, 1, 0, 1, 0], [0, 0, 0, 1, 0]]]:
            # /* Example
            #  *  Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
            #  *  Output: 2
            #  *
            #  *  Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
            #  *  Output: 0
            #  */
            logging.info("Input: grid = %s", grid)

            retVal = pSolution.minimumObstacles(grid)
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
